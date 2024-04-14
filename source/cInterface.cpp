/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
cInterface::cInterface()noexcept
: m_Title       ()
, m_Name        ()
, m_Message     ()
, m_aBack       {}
, m_bIntro      (false)
, m_fIntroValue (1.0f)
{
    m_Title.Construct("sadanasquare.ttf", 180u, 6u);
    m_Title.SetCenter(coreVector2(0.0f,0.2f));
    m_Title.SetColor3(INTERFACE_COLOR);
    m_Title.SetText  ("LAST FALL");

    m_Name.Construct  ("sadanasquare.ttf", 80u, 4u);
    m_Name.SetCenter  (coreVector2(0.0f,-0.2f));
    m_Name.SetColor3  (INTERFACE_COLOR);
    m_Name.SetText    ("A GAME BY MARTIN MAUERSICS");

    m_Message.Construct("sadanasquare.ttf", 80u, 4u);
    m_Message.SetColor3(INTERFACE_COLOR);
    m_Message.SetAlpha (0.0f);
    m_Message.SetText  ("THANK YOU FOR PLAYING");

    for(coreUintW i = 0u; i < ARRAY_SIZE(m_aBack); ++i)
    {
        m_aBack[i].DefineTexture(0u, "point.webp");
        m_aBack[i].DefineProgram("point_program");
        m_aBack[i].SetColor3    (coreVector3(0.0f,0.0f,0.0f));
    }

    m_aBack[0].SetPosition(m_Title.GetPosition());
    m_aBack[0].SetSize    (coreVector2(1.0f,0.12f));
    m_aBack[0].SetCenter  (m_Title.GetCenter());

    m_aBack[1].SetPosition(m_Name.GetPosition());
    m_aBack[1].SetSize    (coreVector2(1.1f,0.06f));
    m_aBack[1].SetCenter  (m_Name.GetCenter());

    m_aBack[2].SetPosition(m_Message.GetPosition());
    m_aBack[2].SetSize    (coreVector2(1.0f,0.06f));
    m_aBack[2].SetCenter  (m_Message.GetCenter());
}


// ****************************************************************
void cInterface::Render()
{
    glDisable(GL_DEPTH_TEST);
    {
        for(coreUintW i = 0u; i < ARRAY_SIZE(m_aBack); ++i)
        {
            m_aBack[i].Render();
        }

        m_Title  .Render();
        m_Name   .Render();
        m_Message.Render();
    }
    glEnable(GL_DEPTH_TEST);
}


// ****************************************************************
void cInterface::Move()
{
    if(!g_pGame->GetPlayer()->GetPosition().xy().IsNull())
        m_bIntro = true;

    if(m_bIntro) m_fIntroValue.UpdateMax(-0.4f, 0.0f);

    const auto nSetAlphaFunc = [](coreObject2D* OUTPUT pObject, const coreFloat fAlpha)
    {
        pObject->SetAlpha  (fAlpha);
        pObject->SetEnabled(fAlpha ? CORE_OBJECT_ENABLE_ALL : CORE_OBJECT_ENABLE_NOTHING);
    };

    const coreFloat fAlpha = BLENDH3(m_fIntroValue);
    const coreFloat fOutro = BLENDH3(CLAMP01((g_pGame->GetOutro() - 4.0f) * 0.5f));

    nSetAlphaFunc(&m_Title,   fAlpha);
    nSetAlphaFunc(&m_Name,    fAlpha);
    nSetAlphaFunc(&m_Message, fOutro);

    m_Title  .Move();
    m_Name   .Move();
    m_Message.Move();

    nSetAlphaFunc(&m_aBack[0], fAlpha * 0.1f);
    nSetAlphaFunc(&m_aBack[1], fAlpha * 0.1f);
    nSetAlphaFunc(&m_aBack[2], fOutro * 0.1f);

    for(coreUintW i = 0u; i < ARRAY_SIZE(m_aBack); ++i)
    {
        m_aBack[i].Move();
    }
}