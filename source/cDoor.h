/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _LAF_GUARD_DOOR_H_
#define _LAF_GUARD_DOOR_H_


// ****************************************************************
#define DOOR_SCALE (2.0f)


// ****************************************************************
class cDoor final : public coreObject3D
{
private:
    coreUintW m_iCheckFrom;
    coreUintW m_iCheckTo;

    coreBool m_bDisable;
    coreFlow m_fDisableTime;


public:
    cDoor()noexcept;

    DISABLE_COPY(cDoor)

    void Move()final;

    inline void SetCheck(const coreUintW iFrom, const coreUintW iTo) {ASSERT(iFrom < iTo) m_iCheckFrom = iFrom; m_iCheckTo = iTo;}

    inline const coreBool& GetDisable()const {return m_bDisable;}
};


#endif // _LAF_GUARD_DOOR_H_