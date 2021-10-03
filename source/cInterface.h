/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _000_GUARD_INTERFACE_H_
#define _000_GUARD_INTERFACE_H_


// ****************************************************************
class cInterface final
{
private:
    coreLabel m_Title;
    coreLabel m_Controls1;
    coreLabel m_Controls2;
    coreLabel m_Message;

    coreBool m_bIntro;
    coreFlow m_fIntroValue;


public:
    cInterface()noexcept;

    DISABLE_COPY(cInterface)

    void Render();
    void Move();
};


#endif // _000_GUARD_INTERFACE_H_