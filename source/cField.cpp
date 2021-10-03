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
cField::cField()noexcept
: m_aTileMemory   (sizeof(cTile),        128u)
, m_aEnemyMemory  (sizeof(cEnemy),       64u)
, m_aDoorMemory   (sizeof(cDoor),        16u)
, m_aShadowMemory (sizeof(coreObject3D), 64u)
, m_iDoorMarker   (0u)
, m_fAlpha        (1.0f)
, m_iLastX        (0)
, m_iLastY        (0)
{
    this->Load(0u);
}


// ****************************************************************
cField::~cField()
{
    this->Unload();
}


// ****************************************************************
void cField::Render()
{
    FOR_EACH(it, m_Enemy) if(!(*it)->GetDisable()) (*it)->Render();
    FOR_EACH(it, m_Door)  if(!(*it)->GetDisable()) (*it)->Render();
    FOR_EACH(it, m_Tile)  if(!(*it)->GetDisable()) (*it)->Render();   // later, to improve object fade

    coreList<coreObject3D*> apSort;
    FOR_EACH(it, m_Door)  if( (*it)->GetDisable()) apSort.push_back(*it);   // TODO: ordering between all transparent objects important !
    FOR_EACH(it, m_Tile)  if( (*it)->GetDisable()) apSort.push_back(*it);
    FOR_EACH(it, m_Enemy) if( (*it)->GetDisable()) apSort.push_back(*it);

    std::sort(apSort.begin(), apSort.end(), [](const coreObject3D* a, const coreObject3D* b)
    {
        return (a->GetPosition().y > b->GetPosition().y);
    });

    FOR_EACH(it, apSort)
    {
        (*it)->Render();
    }

    g_pShadow->Apply();
}


// ****************************************************************
void cField::Move()
{
    FOR_EACH(it, m_Tile)
    {
        (*it)->SetAlpha(m_fAlpha);
        (*it)->Move();
    }

    FOR_EACH(it, m_Enemy)
    {
        (*it)->SetAlpha(m_fAlpha);
        (*it)->Move();
    }

    FOR_EACH(it, m_Door)
    {
        (*it)->SetAlpha(m_fAlpha);
        (*it)->Move();
    }

    FOR_EACH(it, m_Shadow)
    {
        const coreUintW iIndex = m_Shadow.index(it);

        (*it)->SetPosition(m_Enemy[iIndex]->GetPosition());
        (*it)->SetEnabled (m_Enemy[iIndex]->IsEnabled(CORE_OBJECT_ENABLE_ALL) ? CORE_OBJECT_ENABLE_ALL : CORE_OBJECT_ENABLE_NOTHING);
        (*it)->Move();
    }
}


// ****************************************************************
void cField::RenderShadow()
{
    FOR_EACH(it, m_Shadow)
    {
        (*it)->Render();
    }
}


// ****************************************************************
void cField::Load(const coreUint8 iCheckpoint)
{
    this->Unload();
    this->__Setup(iCheckpoint);
}


// ****************************************************************
void cField::Unload()
{
    FOR_EACH(it, m_Tile)   POOLED_DELETE(m_aTileMemory,   *it)
    FOR_EACH(it, m_Enemy)  POOLED_DELETE(m_aEnemyMemory,  *it)
    FOR_EACH(it, m_Door)   POOLED_DELETE(m_aDoorMemory,   *it)
    FOR_EACH(it, m_Shadow) POOLED_DELETE(m_aShadowMemory, *it)

    m_Tile  .clear();
    m_Enemy .clear();
    m_Door  .clear();
    m_Shadow.clear();
}


// ****************************************************************
RETURN_RESTRICT cTile* cField::__CreateTile()
{
    cTile* pTile = POOLED_NEW(m_aTileMemory, cTile);
    m_Tile.push_back(pTile);

    return pTile;
}


// ****************************************************************
RETURN_RESTRICT cEnemy* cField::__CreateEnemy()
{
    cEnemy* pEnemy = POOLED_NEW(m_aEnemyMemory, cEnemy);
    m_Enemy.push_back(pEnemy);

    coreObject3D* pShadow = POOLED_NEW(m_aShadowMemory, coreObject3D);
    m_Shadow.push_back(pShadow);

    pShadow->DefineModel  ("default_sphere.md3");
    pShadow->DefineProgram("shadow_object_program");
    pShadow->SetSize      (coreVector3(0.99f,0.99f,3.0f) * 0.95f * ENEMY_SCALE);

    return pEnemy;
}


// ****************************************************************
RETURN_RESTRICT cDoor* cField::__CreateDoor()
{
    cDoor* pDoor = POOLED_NEW(m_aDoorMemory, cDoor);
    m_Door.push_back(pDoor);

    return pDoor;
}


// ****************************************************************
void cField::__CreateTileExt(const coreInt32 iX, const coreInt32 iY, const coreUint8 iValue, const coreUint8 iCheckpoint)
{
    cTile* pTile = this->__CreateTile();

    pTile->SetPosition  (coreVector3(I_TO_F(iX) * TILE_SCALE, I_TO_F(iY) * TILE_SCALE, 0.0f));
    pTile->SetValue     (iValue);
    pTile->SetCheckpoint(iCheckpoint);

    m_iLastX = iX;
    m_iLastY = iY;
}


// ****************************************************************
void cField::__CreateEnemyExt(const coreInt32 iX, const coreInt32 iY, const coreUint8 iType, const coreFloat fTimeOffset, const coreFloat fMoveOffset, const coreFloat fSpeed, const coreVector2 vPosOffset)
{
    cEnemy* pEnemy = this->__CreateEnemy();

    pEnemy->SetPosition(coreVector3(I_TO_F(iX) * TILE_SCALE + vPosOffset.x, I_TO_F(iY) * TILE_SCALE + vPosOffset.y, 0.0f));
    pEnemy->Configure  (iType, fTimeOffset, fMoveOffset, fSpeed);

    m_iLastX = iX;
    m_iLastY = iY;
}


// ****************************************************************
void cField::__CreateDoorExt(const coreInt32 iX, const coreInt32 iY)
{
    if(m_iDoorMarker < m_Tile.size())
    {
        cDoor* pDoor = this->__CreateDoor();

        pDoor->SetPosition(coreVector3(I_TO_F(iX) * TILE_SCALE, I_TO_F(iY) * TILE_SCALE, 0.0f));
        pDoor->SetCheck   (m_iDoorMarker, m_Tile.size());
    }

    m_iDoorMarker = 0u;

    m_iLastX = iX;
    m_iLastY = iY;
}


// ****************************************************************
void cField::__DoorMarker()
{
    m_iDoorMarker = m_Tile.size();
}


// ****************************************************************
void cField::__RetrieveLast(coreInt32* OUTPUT pX, coreInt32* OUTPUT pY)
{
    ASSERT(pX && pY)
    (*pX) = m_iLastX;
    (*pY) = m_iLastY;
}