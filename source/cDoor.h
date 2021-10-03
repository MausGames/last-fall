/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _000_GUARD_DOOR_H_
#define _000_GUARD_DOOR_H_


// ****************************************************************
#define DOOR_SCALE (2.0f)


// ****************************************************************
class cDoor final : public coreObject3D
{
private:
    coreUintW m_iCheckStart;
    coreUintW m_iCheckEnd;

    coreBool m_bDisable;
    coreFlow m_bDisableTime;


public:
    cDoor()noexcept;
    ~cDoor()final;

    DISABLE_COPY(cDoor)

    void Render()final;
    void Move  ()final;

    inline void SetCheck(const coreUintW iStart, const coreUintW iEnd) {ASSERT(iStart < iEnd) m_iCheckStart = iStart; m_iCheckEnd = iEnd;}

    inline const coreBool& GetDisable()const {return m_bDisable;}
};


#endif // _000_GUARD_DOOR_H_