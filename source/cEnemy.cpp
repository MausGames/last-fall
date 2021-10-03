/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
cEnemy::cEnemy()noexcept
: m_fRotation    (0.0f)
, m_bDisable     (false)
, m_bDisableTime (0.0f)
, m_fAttackDelay (0.0f)
, m_iType        (0u)
, m_fTime        (0.0f)
, m_fOffset      (0.0f)
, m_fSpeed       (0.0f)
, m_vStart       (coreVector2(0.0f,0.0f))
, m_vVelocity    (coreVector2(0.0f,0.0f))
{
    this->DefineProgram("object_enemy_program");
    this->DefineModel  ("object_enemy.md3");

    this->SetSize  (coreVector3(1.0f,1.0f,1.0f) * ENEMY_SCALE);
    //this->SetColor3(coreVector3(0.2f,0.2f,0.2f));
}


// ****************************************************************
cEnemy::~cEnemy()
{
    
}


// ****************************************************************
void cEnemy::Render()
{
    this->coreObject3D::Render();
}


// ****************************************************************
void cEnemy::Move()
{
    if(m_bDisable)
    {
        m_bDisableTime.Update(3.0f);

        this->SetAlpha(this->GetAlpha() * LERPH3(1.0f, 0.0f, m_bDisableTime));
        if(m_bDisableTime >= 1.0f) this->SetEnabled(CORE_OBJECT_ENABLE_NOTHING);
    }

    m_fRotation.Update(2.0f);
    m_fAttackDelay.UpdateMax(-1.0f, 0.0f);

    this->Execute();

    const coreVector2 vDir = coreVector2::Direction(m_fRotation);

    this->SetPosition   (coreVector3(this->GetPosition().xy(), ENEMY_SCALE));
    this->SetDirection  (coreVector3(vDir, 0.0f));
    //this->SetOrientation(coreVector3(-vDir.x*vDir.y, vDir.x*vDir.x, vDir.y));

    this->coreObject3D::Move();
}


// ****************************************************************
void cEnemy::Configure(const coreUint8 iType, const coreFloat fTimeOffset, const coreFloat fMoveOffset, const coreFloat fSpeed)
{
    m_iType   = iType;
    m_fTime   = fTimeOffset;
    m_fOffset = fMoveOffset * TILE_SCALE;
    m_fSpeed  = fSpeed;
    m_vStart  = this->GetPosition().xy();
}


// ****************************************************************
void cEnemy::Execute()
{
    m_fTime.Update(m_fSpeed);

    if(m_iType == 1u || m_iType == 2u)   // move back and forth X Y
    {
        const coreVector2 vFrom   = m_vStart;
        const coreVector2 vTo     = vFrom + ((m_iType == 1u) ? coreVector2(m_fOffset, 0.0f) : coreVector2(0.0f, m_fOffset));
        const coreVector2 vNewPos = LERP(vFrom, vTo, 0.5f + 0.5f * SIN(m_fTime));

        this->SetPosition(coreVector3(vNewPos, this->GetPosition().z));
    }
    else if(m_iType == 3u)   // move in a circle
    {
        const coreVector2 vDir    = coreVector2::Direction(m_fTime);
        const coreVector2 vNewPos = m_vStart + vDir * m_fOffset;

        this->SetPosition(coreVector3(vNewPos, this->GetPosition().z));
    }
    else if(m_iType == 4u)   // follow the player
    {
        const coreList<cTile*>* pTileList = g_pGame->GetField()->GetTileList();   // TODO: hack
        const coreUintW iLastLevelIndex = pTileList->size() - 1u - 16u;

        coreUint32 iTotal = 0u;
        for(coreUintW i = iLastLevelIndex + 1u, ie = pTileList->size(); i < ie; ++i)
        {
            const coreUint8 iValue = (*pTileList)[i]->GetValue();

            iTotal += iValue;
        }

        if(iTotal <= 1u)
        {
            this->SetDisable(true);
            g_pGame->SetLastCheckpoint(GAME_CHECKPOINT_END);
        }

        const cTile* pLastCHeckpoint = (*pTileList)[iLastLevelIndex];
        if(pLastCHeckpoint->GetDisable())
        {
            const cPlayer* pPlayer = g_pGame->GetPlayer();

            const coreVector2 vMove = (pPlayer->GetPosition().xy() - this->GetPosition().xy()).Normalized();

            const coreFloat fBreak = POW(1.0f - 1.0f * (1.0f/60.0f), TIME * 60.0f);

            m_vVelocity = (m_vVelocity + vMove * (60.0f * TIME)) * fBreak;
            const coreVector2 vNewPos = this->GetPosition().xy() + m_vVelocity * TIME;

            this->SetPosition(coreVector3(vNewPos, this->GetPosition().z));
        }
    }
}