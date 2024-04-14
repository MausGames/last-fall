/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"

STATIC_MEMORY(cInterface,     g_pInterface)
STATIC_MEMORY(cGame,          g_pGame)
STATIC_MEMORY(cShadow,        g_pShadow)
STATIC_MEMORY(coreFullscreen, s_pFullscreen)

static coreMusicPlayer s_MusicPlayer = {};


// ****************************************************************
// init the application
void CoreApp::Init()
{
    Core::Graphics->SetCamera(CAMERA_POSITION, CAMERA_DIRECTION, CAMERA_ORIENTATION);
    Core::Graphics->SetView(Core::System->GetResolution(), DEG_TO_RAD(45.0f), 10.0f, 500.0f);

    STATIC_NEW(g_pInterface)
    STATIC_NEW(g_pGame)
    STATIC_NEW(g_pShadow)
    STATIC_NEW(s_pFullscreen)

    s_pFullscreen->DefineProgram("fullscreen_program");

    s_MusicPlayer.AddMusicFolder("data/music", "*.opus");
    s_MusicPlayer.StartThread();
    s_MusicPlayer.Play();

#if !defined(_CORE_EMSCRIPTEN_)
    Core::Input->ShowCursor(false);
#endif
}


// ****************************************************************
// exit the application
void CoreApp::Exit()
{
    s_MusicPlayer.KillThread();
    s_MusicPlayer.ClearMusic();

    STATIC_DELETE(s_pFullscreen)
    STATIC_DELETE(g_pShadow)
    STATIC_DELETE(g_pGame)
    STATIC_DELETE(g_pInterface)
}


// ****************************************************************
// render the application
void CoreApp::Render()
{
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    {
        s_pFullscreen->Render();
    }
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    g_pGame     ->Render();
    g_pInterface->Render();
}


// ****************************************************************
// move the application
void CoreApp::Move()
{
    if(Core::System->GetWinSizeChanged())
    {
        Core::Reshape();
    }

    if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(ESCAPE), CORE_INPUT_PRESS))
    {
        Core::System->Quit();
    }

    const coreVector2 vResolution = Core::System->GetResolution();
    s_pFullscreen->SetSize(vResolution / vResolution.Min());

    g_pGame      ->Move();
    g_pInterface ->Move();
    s_pFullscreen->Move();

    s_MusicPlayer.Update();
}