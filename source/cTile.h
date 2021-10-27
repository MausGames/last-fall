/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _LAF_GUARD_TILE_H_
#define _LAF_GUARD_TILE_H_


// ****************************************************************
#define TILE_SCALE      (6.0f)
#define TILE_TEXSIZE    (1.0f/3.0f)
#define TILE_NUMBERS    (5u)
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
    coreFlow m_fDisableTime;


public:
    cTile()noexcept;

    DISABLE_COPY(cTile)

    void Move()final;

    inline void SetValue     (const coreUint8 iValue)      {m_iValue      = iValue; ASSERT((iValue <= TILE_NUMBERS) || (iValue == TILE_CHECKPOINT))}
    inline void SetCheckpoint(const coreUint8 iCheckpoint) {m_iCheckpoint = iCheckpoint;}
    inline void SetPressed   (const coreBool  bPressed)    {m_bPressed    = bPressed;}

    inline const coreUint8& GetValue  ()const {return m_iValue;}
    inline const coreBool&  GetDisable()const {return m_bDisable;}
};


#endif // _LAF_GUARD_TILE_H_