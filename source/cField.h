/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _LAF_GUARD_FIELD_H_
#define _LAF_GUARD_FIELD_H_


// ****************************************************************
#define FIELD_RESERVE_TILES   (256u)
#define FIELD_RESERVE_ENEMIES (128u)
#define FIELD_RESERVE_DOORS   (8u)


// ****************************************************************
class cField final
{
private:
    coreList<cTile*>        m_apTile;
    coreList<cEnemy*>       m_apEnemy;
    coreList<cDoor*>        m_apDoor;
    coreList<coreObject3D*> m_apShadow;

    coreBatchList m_TileList;
    coreBatchList m_EnemyList;
    coreBatchList m_DoorList;
    coreBatchList m_ShadowList;

    coreMemoryPool m_TileMemory;
    coreMemoryPool m_EnemyMemory;
    coreMemoryPool m_DoorMemory;
    coreMemoryPool m_ShadowMemory;

    coreFloat m_fAlpha;

    coreUint8 m_iFinalCheckpoint;
    coreUintW m_iFinalCheckpointIndex;

    coreUintW m_iDoorMarker;

    coreInt32 m_iLastX;
    coreInt32 m_iLastY;

    UNUSED cTile  m_SaveTile;   // to load and hold all resources
    UNUSED cEnemy m_SaveEnemy;
    UNUSED cDoor  m_SaveDoor;


public:
    cField()noexcept;
    ~cField();

    DISABLE_COPY(cField)

    void Render();
    void Move();

    void RenderTransparent();
    void RenderShadow();

    void Load(const coreUint8 iCheckpoint);
    void Unload();

    coreUint32 CalculateTileValue(const coreUintW iFrom, const coreUintW iTo)const;

    inline void SetAlpha(const coreFloat fAlpha) {m_fAlpha = fAlpha;}

    inline coreList<cTile*>*  GetTileList            ()      {return &m_apTile;}
    inline coreList<cEnemy*>* GetEnemyList           ()      {return &m_apEnemy;}
    inline coreList<cDoor*>*  GetDoorList            ()      {return &m_apDoor;}
    inline const coreUint8&   GetFinalCheckpoint     ()const {return m_iFinalCheckpoint;}
    inline const coreUintW&   GetFinalCheckpointIndex()const {return m_iFinalCheckpointIndex;}


private:
    RETURN_RESTRICT cTile*  __CreateTile ();
    RETURN_RESTRICT cEnemy* __CreateEnemy();
    RETURN_RESTRICT cDoor*  __CreateDoor ();

    void __CreateTileExt(const coreInt32 iX, const coreInt32 iY, const coreUint8 iValue, const coreUint8 iCheckpoint = 0u);
    void __CreateEnemExt(const coreInt32 iX, const coreInt32 iY, const coreUint8 iType, const coreFloat fTimeOffset, const coreFloat fMoveOffset, const coreFloat fSpeed, const coreVector2 vPosOffset = coreVector2(0.0f,0.0f));
    void __CreateDoorExt(const coreInt32 iX, const coreInt32 iY);

    void __DoorMarker();

    void __Setup(const coreUint8 iCheckpoint);
    void __RetrieveLast(coreInt32* OUTPUT pX, coreInt32* OUTPUT pY)const;
};


#endif // _LAF_GUARD_FIELD_H_