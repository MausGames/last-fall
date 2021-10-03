/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
cInterface::cInterface()noexcept
: m_bIntro      (false)
, m_fIntroValue (1.0f)
{
    m_Title.Construct   ("sadanasquare.ttf", 180u, 6u);
    m_Title.SetCenter   (coreVector2(0.0f,0.25f));
    m_Title.SetText     ("LAST FALL");

    m_Controls1.Construct  ("sadanasquare.ttf", 80u, 4u);
    m_Controls1.SetPosition(coreVector2(0.0f, 0.04f));
    m_Controls1.SetCenter  (coreVector2(0.0f,-0.25f));
    m_Controls1.SetText    ("KEYBOARD:  WASD / ARROWS");

    m_Controls2.Construct  ("sadanasquare.ttf", 80u, 4u);
    m_Controls2.SetPosition(coreVector2(0.0f,-0.06f));
    m_Controls2.SetCenter  (coreVector2(0.0f,-0.25f));
    m_Controls2.SetText    ("GAMEPAD:  STICK / D-PAD");

    m_Message.Construct("sadanasquare.ttf", 80u, 4u);
    m_Message.SetAlpha (0.0f);
    m_Message.SetText  ("THANK YOU FOR PLAYING");
}


// ****************************************************************
void cInterface::Render()
{
    glDisable(GL_DEPTH_TEST);
    {
        m_Title    .Render();
        m_Controls1.Render();
        m_Controls2.Render();
        m_Message  .Render();
    }
    glEnable(GL_DEPTH_TEST);
}


// ****************************************************************
void cInterface::Move()
{
    if(!g_pGame->GetPlayer()->GetPosition().xy().IsNull())
        m_bIntro = true;

    if(m_bIntro) m_fIntroValue.UpdateMax(-0.5f, 0.0f);

    const coreFloat fOutro = LERPH3(0.0f, 1.0f, CLAMP((g_pGame->GetOutro() - 4.0f) * 0.5f, 0.0f, 1.0f));
    m_Message.SetAlpha  (fOutro);
    m_Message.SetEnabled(fOutro ? CORE_OBJECT_ENABLE_ALL : CORE_OBJECT_ENABLE_NOTHING);

    const coreFloat fAlpha = LERPH3(0.0f, 1.0f, m_fIntroValue);

    m_Title    .SetAlpha(fAlpha);
    m_Controls1.SetAlpha(fAlpha);
    m_Controls2.SetAlpha(fAlpha);

    m_Title.SetPosition(coreVector2(0.0f,0.0f));

    m_Title    .Move();
    m_Controls1.Move();
    m_Controls2.Move();
    m_Message  .Move();
}
