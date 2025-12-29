/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _LAF_GUARD_SHADOW_H_
#define _LAF_GUARD_SHADOW_H_


// ****************************************************************
class CShadow final : public coreFullscreen
{
public:
    CShadow()noexcept;

    DISABLE_COPY(CShadow)

    void Apply();
};


#endif // _LAF_GUARD_SHADOW_H_