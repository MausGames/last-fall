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
cGame::cGame()noexcept
: m_iLastCheckpoint (DEFINED(_CORE_DEBUG_) ? 2u : 0u)
{
    m_Player.SetPosition(coreVector3(0.0f,0.0f,0.0f));
}


// ****************************************************************
cGame::~cGame()
{
    
}


// ****************************************************************
void cGame::Render()
{
    m_Player.Render();
    m_Field .Render();
}


// ****************************************************************
void cGame::Move()
{
    m_Player.Move();

    coreBool bFalling = true;

    const coreList<cTile*>* pTileList = m_Field.GetTileList();
    FOR_EACH(it, *pTileList)
    {
        cTile* pTile = (*it);
        if(pTile->GetDisable()) continue;

        const coreVector2 vDiff = m_Player.GetPosition().xy() - pTile->GetPosition().xy();
        if((ABS(vDiff.x) < TILE_SCALE * 0.5f) && (ABS(vDiff.y) < TILE_SCALE * 0.5f))
        {
            if(!m_Player.GetFalling()) pTile->SetPressed(true);

            const coreFloat vDiff2 = m_Player.GetPosition().z - pTile->GetPosition().z;
            if(ABS(vDiff2) < PLAYER_SCALE * 3.0f)
            {
                if(m_Player.GetVelocityHeight() <= 0.0f) bFalling = false;
            }
        }
        else
        {
            pTile->SetPressed(false);
        }
    }

    const coreList<cEnemy*>* pEnemyList = m_Field.GetEnemyList();
    FOR_EACH(it, *pEnemyList)
    {
        cEnemy* pEnemy = (*it);
        if(pEnemy->GetDisable()) continue;
        if(pEnemy->GetAttackDelay()) continue;

        const coreVector3 vDiff = m_Player.GetPosition() - pEnemy->GetPosition();
        if((ABS(vDiff.x) < 1.3f) && (ABS(vDiff.y) < 1.3f) && (ABS(vDiff.z) < 1.3f))
        {
            m_Player.AddVelocity(vDiff.xy().Normalized() * 100.0f);
            m_Player.AddVelocityHeight(50.0f);
            m_Player.SetFalling(true);
            m_Player.SetLanding(true);
            bFalling = true;
            pEnemy->Bump();
            pEnemy->SetAttackDelay(0.5f);
            break;
        }
    }

    const coreList<cDoor*>* pDoorList = m_Field.GetDoorList();
    FOR_EACH(it, *pDoorList)
    {
        cDoor* pDoor = (*it);
        if(pDoor->GetDisable()) continue;

        const coreVector3 vDiff = m_Player.GetPosition() - pDoor->GetPosition();
        if((ABS(vDiff.x) < TILE_SCALE * 0.5f + 0.5f) && (ABS(vDiff.y) < TILE_SCALE * 0.5f + 0.5f) && (ABS(vDiff.z) < TILE_SCALE * 0.5f + 0.5f))
        {
            m_Player.SetVelocity(vDiff.xy().Normalized() * 20.0f);
            break;
        }
    }

    if(bFalling || m_Player.GetLanding())
    {
        m_Player.SetFalling(bFalling);
        if(!bFalling) m_Player.SetLanding(false);
    }
    m_Player.Land();

    if(m_Player.GetPosition().z < GAME_HEIGHT * -1.0f)
    {
        if(m_iLastCheckpoint == GAME_CHECKPOINT_END)
        {
            m_fOutro.Update(1.0f);

            const coreFloat fAlpha = LERPH3(1.0f, 0.0f, MIN(m_fOutro * 0.2f, 1.0f));
            m_Player.SetSize (coreVector3(1.0f,1.0f,1.0f) * PLAYER_SCALE * fAlpha);
            m_Player.SetAlpha(fAlpha);
        }
        else
        {
            m_Field.Load(m_iLastCheckpoint);

            const cTile* pFirst = m_Field.GetTileList()->front();

            m_Player.SetPosition(coreVector3(pFirst->GetPosition().xy(), m_Player.GetPosition().z + GAME_HEIGHT * 2.0f));
            //m_Player.SetVelocity(coreVector2(0.0f,0.0f));
            m_Player.SetLanding (true);
        }
    }

    const coreFloat fAlpha = 1.0f - STEPH3(0.0f, GAME_HEIGHT, ABS(m_Player.GetPosition().z));

    m_Field.SetAlpha(fAlpha);
    m_Field.Move();

    const coreVector3 vCamDir = CAMERA_DIRECTION;
    const coreVector3 vCamOri = CAMERA_ORIENTATION;
    const coreVector3 vCamPos = m_Player.GetPosition() - vCamDir * 50.0f;

    Core::Graphics->SetCamera(vCamPos, vCamDir, vCamOri);
}


// ****************************************************************
void cGame::RenderShadow()
{
    if(m_fOutro) return;

    m_Player.RenderShadow();
    m_Field .RenderShadow();
}