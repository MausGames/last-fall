/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _000_GUARD_GAME_H_
#define _000_GUARD_GAME_H_


// ****************************************************************
#define GAME_HEIGHT           (30.0f)
#define GAME_CHECKPOINT_FINAL (12u)
#define GAME_CHECKPOINT_END   (0xFFu)


// ****************************************************************
class cGame final
{
private:
    cPlayer m_Player;
    cField  m_Field;

    coreUint8 m_iLastCheckpoint;

    coreFlow m_fOutro;


public:
    cGame()noexcept;
    ~cGame();

    DISABLE_COPY(cGame)

    void Render();
    void Move();

    void RenderShadow();

    inline void SetLastCheckpoint(const coreUint8 ilastCheckpoint) {if(m_iLastCheckpoint < ilastCheckpoint) m_iLastCheckpoint = ilastCheckpoint;}

    inline cPlayer*         GetPlayer()      {return &m_Player;}
    inline cField*          GetField ()      {return &m_Field;}
    inline const coreFloat& GetOutro ()const {return m_fOutro;}
};


#endif // _000_GUARD_GAME_H_