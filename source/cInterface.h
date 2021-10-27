/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _LAF_GUARD_INTERFACE_H_
#define _LAF_GUARD_INTERFACE_H_


// ****************************************************************
#define INTERFACE_COLOR (coreVector3(1.0f,1.0f,1.0f) * 0.97f)


// ****************************************************************
class cInterface final
{
private:
    coreLabel m_Title;
    coreLabel m_Name;
    coreLabel m_Controls;
    coreLabel m_Message;

    coreBool m_bIntro;
    coreFlow m_fIntroValue;


public:
    cInterface()noexcept;

    DISABLE_COPY(cInterface)

    void Render();
    void Move();
};


#endif // _LAF_GUARD_INTERFACE_H_