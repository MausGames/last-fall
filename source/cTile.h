/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _000_GUARD_TILE_H_
#define _000_GUARD_TILE_H_


// ****************************************************************
#define TILE_NUMERS (5u)
#define TILE_SCALE  (6.0f)

#define TILE_CHECKPOINT (0xFFu)


// ****************************************************************
class cTile final : public coreObject3D
{
private:
    coreUint8 m_iValue;
    coreUint8 m_iCheckpoint;

    coreBool  m_bPressed;
    coreBool  m_bPressedOld;
    coreFlow  m_fPressedShift;

    coreBool m_bDisable;
    coreFlow m_bDisableTime;


public:
    cTile()noexcept;
    ~cTile()final;

    DISABLE_COPY(cTile)

    void Render()final;
    void Move  ()final;

    inline void SetValue     (const coreUint8 iValue)      {m_iValue      = iValue; ASSERT((iValue <= TILE_NUMERS) || iValue == TILE_CHECKPOINT)}
    inline void SetCheckpoint(const coreUint8 iCheckpoint) {m_iCheckpoint = iCheckpoint;}
    inline void SetPressed   (const coreBool  bPressed)    {m_bPressed    = bPressed;}

    inline const coreUint8& GetValue  ()const {return m_iValue;}
    inline const coreBool&  GetDisable()const {return m_bDisable;}
};


#endif // _000_GUARD_TILE_H_