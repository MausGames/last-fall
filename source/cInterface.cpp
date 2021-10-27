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
: m_Title       ()
, m_Name        ()
, m_Controls    ()
, m_Message     ()
, m_bIntro      (false)
, m_fIntroValue (1.0f)
{
    m_Title.Construct("sadanasquare.ttf", 180u, 6u);
    m_Title.SetCenter(coreVector2(0.0f,0.25f));
    m_Title.SetColor3(INTERFACE_COLOR);
    m_Title.SetText  ("LAST FALL");

    m_Name.Construct  ("sadanasquare.ttf", 80u, 4u);
    m_Name.SetPosition(coreVector2(0.0f, 0.04f));
    m_Name.SetCenter  (coreVector2(0.0f,-0.25f));
    m_Name.SetColor3  (INTERFACE_COLOR);
    m_Name.SetText    ("A GAME BY MARTIN MAUERSICS");

    m_Controls.Construct  ("sadanasquare.ttf", 80u, 4u);
    m_Controls.SetPosition(coreVector2(0.0f,-0.06f));
    m_Controls.SetCenter  (coreVector2(0.0f,-0.25f));
    m_Controls.SetColor3  (INTERFACE_COLOR);
    m_Controls.SetText    ("CONTROLS:  WASD / ARROWS / GAMEPAD");

    m_Message.Construct("sadanasquare.ttf", 80u, 4u);
    m_Message.SetColor3(INTERFACE_COLOR);
    m_Message.SetAlpha (0.0f);
    m_Message.SetText  ("THANK YOU FOR PLAYING");
}


// ****************************************************************
void cInterface::Render()
{
    glDisable(GL_DEPTH_TEST);
    {
        m_Title   .Render();
        m_Name    .Render();
        m_Controls.Render();
        m_Message .Render();
    }
    glEnable(GL_DEPTH_TEST);
}


// ****************************************************************
void cInterface::Move()
{
    if(!g_pGame->GetPlayer()->GetPosition().xy().IsNull())
        m_bIntro = true;

    if(m_bIntro) m_fIntroValue.UpdateMax(-0.5f, 0.0f);

    const auto nSetAlphaFunc = [](coreObject2D* OUTPUT pObject, const coreFloat fAlpha)
    {
        pObject->SetAlpha  (fAlpha);
        pObject->SetEnabled(fAlpha ? CORE_OBJECT_ENABLE_ALL : CORE_OBJECT_ENABLE_NOTHING);
    };

    const coreFloat fAlpha = LERPH3(0.0f, 1.0f, m_fIntroValue);
    const coreFloat fOutro = LERPH3(0.0f, 1.0f, CLAMP((g_pGame->GetOutro() - 4.0f) * 0.5f, 0.0f, 1.0f));

    nSetAlphaFunc(&m_Title,    fAlpha);
    nSetAlphaFunc(&m_Name,     fAlpha);
    nSetAlphaFunc(&m_Controls, fAlpha);
    nSetAlphaFunc(&m_Message,  fOutro);

    m_Title   .Move();
    m_Name    .Move();
    m_Controls.Move();
    m_Message .Move();
}