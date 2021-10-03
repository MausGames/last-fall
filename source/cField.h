/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _000_GUARD_FIELD_H_
#define _000_GUARD_FIELD_H_


// ****************************************************************
class cField final
{
private:
    coreList<cTile*> m_Tile;
    coreMemoryPool   m_aTileMemory;

    coreList<cEnemy*> m_Enemy;
    coreMemoryPool    m_aEnemyMemory;

    coreList<cDoor*> m_Door;
    coreMemoryPool   m_aDoorMemory;

    coreList<coreObject3D*> m_Shadow;
    coreMemoryPool          m_aShadowMemory;

    coreUintW m_iDoorMarker;

    coreFloat m_fAlpha;

    cTile  m_SaveTile;   // to load and hold all resources
    cEnemy m_SaveEnemy;
    cDoor  m_SaveDoor;

    coreInt32 m_iLastX;
    coreInt32 m_iLastY;


public:
    cField()noexcept;
    ~cField();

    DISABLE_COPY(cField)

    void Render();
    void Move();

    void RenderShadow();

    void Load(const coreUint8 iCheckpoint);
    void Unload();

    inline void SetAlpha(const coreFloat fAlpha) {m_fAlpha = fAlpha;}

    inline coreList<cTile*>*  GetTileList () {return &m_Tile;}
    inline coreList<cEnemy*>* GetEnemyList() {return &m_Enemy;}
    inline coreList<cDoor*>*  GetDoorList () {return &m_Door;}


private:
    RETURN_RESTRICT cTile*  __CreateTile ();
    RETURN_RESTRICT cEnemy* __CreateEnemy();
    RETURN_RESTRICT cDoor*  __CreateDoor ();

    void __CreateTileExt (const coreInt32 iX, const coreInt32 iY, const coreUint8 iValue, const coreUint8 iCheckpoint = 0u);
    void __CreateEnemyExt(const coreInt32 iX, const coreInt32 iY, const coreUint8 iType, const coreFloat fTimeOffset, const coreFloat fMoveOffset, const coreFloat fSpeed, const coreVector2 vPosOffset = coreVector2(0.0f,0.0f));
    void __CreateDoorExt (const coreInt32 iX, const coreInt32 iY);

    void __DoorMarker();

    void __Setup(const coreUint8 iCheckpoint);
    void __RetrieveLast(coreInt32* OUTPUT pX, coreInt32* OUTPUT pY);
};


#endif // _000_GUARD_FIELD_H_