/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
cEnemy::cEnemy()noexcept
: coreObject3D   ()
, m_fRotation    (0.0f)
, m_fBump        (0.0f)
, m_bDisable     (false)
, m_fDisableTime (0.0f)
, m_iType        (0u)
, m_fJobTime     (0.0f)
, m_fJobOffset   (0.0f)
, m_fJobSpeed    (0.0f)
, m_vJobPosition (coreVector2(0.0f,0.0f))
, m_vJobVelocity (coreVector2(0.0f,0.0f))
{
    this->DefineModel  ("object_enemy.md3z");
    this->DefineProgram("object_enemy_program");

    this->SetSize(coreVector3(1.0f,1.0f,1.0f) * ENEMY_SCALE);
}


// ****************************************************************
void cEnemy::Move()
{
    if(m_bDisable)
    {
        m_fDisableTime.Update(3.0f);

        this->SetAlpha(this->GetAlpha() * LERPH3(1.0f, 0.0f, m_fDisableTime));   // # base-value set by field class
        if(m_fDisableTime >= 1.0f) this->SetEnabled(CORE_OBJECT_ENABLE_NOTHING);
    }

    this->Execute();

    m_fRotation.UpdateMod( 2.0f, 2.0f*PI);
    m_fBump    .UpdateMax(-5.0f, 0.0f);

    const coreFloat   fScale = SIN(m_fBump * PI) + 1.0f;
    const coreVector2 vDir   = coreVector2::Direction(m_fRotation);

    this->SetPosition (coreVector3(this->GetPosition().xy(), ENEMY_SCALE));
    this->SetSize     (coreVector3(1.0f,1.0f,1.0f) * ENEMY_SCALE * fScale);
    this->SetDirection(coreVector3(vDir, 0.0f));

    this->coreObject3D::Move();
}


// ****************************************************************
void cEnemy::Configure(const coreUint8 iType, const coreFloat fTimeOffset, const coreFloat fMoveOffset, const coreFloat fSpeed)
{
    m_iType        = iType;
    m_fJobTime     = fTimeOffset;
    m_fJobOffset   = fMoveOffset;
    m_fJobSpeed    = fSpeed;
    m_vJobPosition = this->GetPosition().xy();
    m_vJobVelocity = coreVector2(0.0f,0.0f);
}


// ****************************************************************
void cEnemy::Execute()
{
    m_fJobTime.Update(m_fJobSpeed);

    switch(m_iType)
    {
    default: UNREACHABLE

    // do nothing
    case 0u:
        break;

    // move back and forth
    case 1u:
    case 2u:
        {
            const coreVector2 vFrom   = m_vJobPosition;
            const coreVector2 vTo     = vFrom + ((m_iType == 1u) ? coreVector2(m_fJobOffset, 0.0f) : coreVector2(0.0f, m_fJobOffset));
            const coreVector2 vNewPos = LERP(vFrom, vTo, 0.5f + 0.5f * SIN(m_fJobTime));

            this->SetPosition(coreVector3(vNewPos, this->GetPosition().z));
        }
        break;

    // move in a circle
    case 3u:
        {
            const coreVector2 vDir    = coreVector2::Direction(m_fJobTime);
            const coreVector2 vNewPos = m_vJobPosition + vDir * m_fJobOffset;

            this->SetPosition(coreVector3(vNewPos, this->GetPosition().z));
        }
        break;

    // follow the player
    case 4u:
        {
            const cPlayer*          pPlayer     = g_pGame->GetPlayer();
            const coreList<cTile*>* papTileList = g_pGame->GetField()->GetTileList();
            const coreUintW         iFinalIndex = g_pGame->GetField()->GetFinalCheckpointIndex();

            const coreUint32 iTotal = g_pGame->GetField()->CalculateTileValue(iFinalIndex + 1u, papTileList->size());

            if((iTotal <= 1u) && !pPlayer->GetFalling())
            {
                m_bDisable = true;
                g_pGame->SetLastCheckpoint(GAME_CHECKPOINT_END);
            }

            if((*papTileList)[iFinalIndex]->GetDisable())
            {
                const coreVector2 vDir = (pPlayer->GetPosition().xy() - this->GetPosition().xy()).Normalized();

                m_vJobVelocity += vDir * (90.0f * TIME);
                m_vJobVelocity *= POW(1.0f - 1.0f * (1.0f/60.0f), 60.0f * TIME);

                const coreVector2 vNewPos = this->GetPosition().xy() + m_vJobVelocity * TIME;

                this->SetPosition(coreVector3(vNewPos, this->GetPosition().z));
            }
        }
        break;
    }
}