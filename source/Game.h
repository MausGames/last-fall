/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _LAF_GUARD_GAME_H_
#define _LAF_GUARD_GAME_H_


// ****************************************************************
#define GAME_HEIGHT         (30.0f)
#define GAME_CHECKPOINT_END (0xFFu)


// ****************************************************************
class CGame final
{
private:
    CPlayer m_Player;
    CField  m_Field;

    coreUint8 m_iLastCheckpoint;
    coreFlow  m_fOutro;

    coreVector2 m_vSmoothCam;

    coreSoundPtr m_pKickSound;
    coreSoundPtr m_pUnlockSound;


public:
    CGame()noexcept;

    DISABLE_COPY(CGame)

    void Render();
    void Move();

    void RenderShadow();

    void PlayUnlockSound(const coreVector3 vPosition);

    inline void SetLastCheckpoint(const coreUint8 iLastCheckpoint) {if(m_iLastCheckpoint < iLastCheckpoint) m_iLastCheckpoint = iLastCheckpoint;}

    inline CPlayer*         GetPlayer()      {return &m_Player;}
    inline CField*          GetField ()      {return &m_Field;}
    inline const coreFloat& GetOutro ()const {return m_fOutro;}
};


#endif // _LAF_GUARD_GAME_H_