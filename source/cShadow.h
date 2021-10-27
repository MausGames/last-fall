/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _LAF_GUARD_SHADOW_H_
#define _LAF_GUARD_SHADOW_H_


// ****************************************************************
class cShadow final : public coreFullscreen
{
public:
    cShadow()noexcept;

    DISABLE_COPY(cShadow)

    void Apply();
};


#endif // _LAF_GUARD_SHADOW_H_