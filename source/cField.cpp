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
cField::cField()noexcept
: m_apTile                {}
, m_apEnemy               {}
, m_apDoor                {}
, m_apShadow              {}
, m_TileList              (FIELD_RESERVE_TILES)
, m_EnemyList             (FIELD_RESERVE_ENEMIES)
, m_DoorList              (FIELD_RESERVE_DOORS)
, m_ShadowList            (FIELD_RESERVE_ENEMIES)
, m_TileMemory            (sizeof(cTile),        FIELD_RESERVE_TILES)
, m_EnemyMemory           (sizeof(cEnemy),       FIELD_RESERVE_ENEMIES)
, m_DoorMemory            (sizeof(cDoor),        FIELD_RESERVE_DOORS)
, m_ShadowMemory          (sizeof(coreObject3D), FIELD_RESERVE_ENEMIES)
, m_fAlpha                (1.0f)
, m_iFinalCheckpoint      (0u)
, m_iFinalCheckpointIndex (0u)
, m_iDoorMarker           (0u)
, m_iLastX                (0)
, m_iLastY                (0)
{
    m_apTile  .reserve(FIELD_RESERVE_TILES);
    m_apEnemy .reserve(FIELD_RESERVE_ENEMIES);
    m_apDoor  .reserve(FIELD_RESERVE_DOORS);
    m_apShadow.reserve(FIELD_RESERVE_ENEMIES);

    m_TileList  .DefineProgram("object_tile_inst_program");
    m_EnemyList .DefineProgram("object_enemy_inst_program");
    m_DoorList  .DefineProgram("object_door_inst_program");
    m_ShadowList.DefineProgram("shadow_object_inst_program");

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
    m_EnemyList.Render();
    m_DoorList .Render();
    m_TileList .Render();   // later, to improve object fade
}


// ****************************************************************
void cField::Move()
{
    FOR_EACH(it, m_apTile)  {(*it)->SetAlpha(m_fAlpha); if((*it)->GetDisable()) {m_TileList .UnbindObject(*it); (*it)->Move();}}
    FOR_EACH(it, m_apEnemy) {(*it)->SetAlpha(m_fAlpha); if((*it)->GetDisable()) {m_EnemyList.UnbindObject(*it); (*it)->Move();}}
    FOR_EACH(it, m_apDoor)  {(*it)->SetAlpha(m_fAlpha); if((*it)->GetDisable()) {m_DoorList .UnbindObject(*it); (*it)->Move();}}

    FOR_EACH(it, m_apShadow)
    {
        const coreUintW iIndex = m_apShadow.index(it);
        const cEnemy*   pEnemy = m_apEnemy[iIndex];

        (*it)->SetPosition(pEnemy->GetPosition() + coreVector3(0.0f, 0.0f, -ENEMY_SCALE));
        (*it)->SetEnabled (pEnemy->GetDisable() ? CORE_OBJECT_ENABLE_NOTHING : CORE_OBJECT_ENABLE_ALL);
    }

    m_TileList  .MoveNormal();
    m_EnemyList .MoveNormal();
    m_DoorList  .MoveNormal();
    m_ShadowList.MoveNormal();
}


// ****************************************************************
void cField::RenderTransparent()
{
    coreList<coreObject3D*> apSort;

    FOR_EACH(it, m_apTile)  if((*it)->GetDisable()) apSort.push_back(*it);
    FOR_EACH(it, m_apEnemy) if((*it)->GetDisable()) apSort.push_back(*it);
    FOR_EACH(it, m_apDoor)  if((*it)->GetDisable()) apSort.push_back(*it);

    std::sort(apSort.begin(), apSort.end(), [](const coreObject3D* a, const coreObject3D* b)
    {
        return (a->GetPosition().y > b->GetPosition().y);
    });

    FOR_EACH(it, apSort) (*it)->Render();
}


// ****************************************************************
void cField::RenderShadow()
{
    m_ShadowList.Render();
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
    FOR_EACH(it, m_apTile)   POOLED_DELETE(m_TileMemory,   *it)
    FOR_EACH(it, m_apEnemy)  POOLED_DELETE(m_EnemyMemory,  *it)
    FOR_EACH(it, m_apDoor)   POOLED_DELETE(m_DoorMemory,   *it)
    FOR_EACH(it, m_apShadow) POOLED_DELETE(m_ShadowMemory, *it)

    m_apTile  .clear();
    m_apEnemy .clear();
    m_apDoor  .clear();
    m_apShadow.clear();

    m_TileList  .Clear();
    m_EnemyList .Clear();
    m_DoorList  .Clear();
    m_ShadowList.Clear();
}


// ****************************************************************
coreUint32 cField::CalculateTileValue(const coreUintW iFrom, const coreUintW iTo)const
{
    coreUint32 iTotal = 0u;

    for(coreUintW i = iFrom; i < iTo; ++i)
    {
        const coreUint8 iValue = m_apTile[i]->GetValue();
        if(iValue != TILE_CHECKPOINT) iTotal += iValue;
    }

    return iTotal;
}


// ****************************************************************
RETURN_RESTRICT cTile* cField::__CreateTile()
{
    cTile* pTile = POOLED_NEW(m_TileMemory, cTile);

    m_apTile  .push_back (pTile);
    m_TileList.BindObject(pTile);

    return pTile;
}


// ****************************************************************
RETURN_RESTRICT cEnemy* cField::__CreateEnemy()
{
    cEnemy*       pEnemy  = POOLED_NEW(m_EnemyMemory,  cEnemy);
    coreObject3D* pShadow = POOLED_NEW(m_ShadowMemory, coreObject3D);

    pShadow->DefineModel  ("default_sphere.md3");
    pShadow->DefineProgram("shadow_object_program");
    pShadow->SetSize      (coreVector3(1.0f,1.0f,1.0f) * 0.95f * ENEMY_SCALE);

    m_apEnemy  .push_back (pEnemy);
    m_EnemyList.BindObject(pEnemy);

    m_apShadow  .push_back (pShadow);
    m_ShadowList.BindObject(pShadow);

    return pEnemy;
}


// ****************************************************************
RETURN_RESTRICT cDoor* cField::__CreateDoor()
{
    cDoor* pDoor = POOLED_NEW(m_DoorMemory, cDoor);

    m_apDoor  .push_back (pDoor);
    m_DoorList.BindObject(pDoor);

    return pDoor;
}


// ****************************************************************
void cField::__CreateTileExt(const coreInt32 iX, const coreInt32 iY, const coreUint8 iValue, const coreUint8 iCheckpoint)
{
    cTile* pTile = this->__CreateTile();

    pTile->SetPosition  (coreVector3(I_TO_F(iX), I_TO_F(iY), 0.0f) * TILE_SCALE);
    pTile->SetValue     (iValue);
    pTile->SetCheckpoint(iCheckpoint);

    m_iLastX = iX;
    m_iLastY = iY;

    if(iCheckpoint)
    {
        m_iFinalCheckpoint      = iCheckpoint;
        m_iFinalCheckpointIndex = m_apTile.size() - 1u;
    }
}


// ****************************************************************
void cField::__CreateEnemExt(const coreInt32 iX, const coreInt32 iY, const coreUint8 iType, const coreFloat fTimeOffset, const coreFloat fMoveOffset, const coreFloat fSpeed, const coreVector2 vPosOffset)
{
    cEnemy* pEnemy = this->__CreateEnemy();

    pEnemy->SetPosition(coreVector3(I_TO_F(iX) + vPosOffset.x, I_TO_F(iY) + vPosOffset.y, 0.0f) * TILE_SCALE);
    pEnemy->Configure  (iType, fTimeOffset, fMoveOffset * TILE_SCALE, fSpeed);

    m_iLastX = iX;
    m_iLastY = iY;
}


// ****************************************************************
void cField::__CreateDoorExt(const coreInt32 iX, const coreInt32 iY)
{
    if(m_iDoorMarker < m_apTile.size())   // do not create door on respawn position
    {
        cDoor* pDoor = this->__CreateDoor();

        pDoor->SetPosition(coreVector3(I_TO_F(iX), I_TO_F(iY), 0.0f) * TILE_SCALE);
        pDoor->SetCheck   (m_iDoorMarker, m_apTile.size());
    }

    m_iDoorMarker = 0u;

    m_iLastX = iX;
    m_iLastY = iY;
}


// ****************************************************************
void cField::__DoorMarker()
{
    m_iDoorMarker = m_apTile.size();
}


// ****************************************************************
void cField::__RetrieveLast(coreInt32* OUTPUT pX, coreInt32* OUTPUT pY)const
{
    ASSERT(pX && pY)

    (*pX) = m_iLastX;
    (*pY) = m_iLastY;
}