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
cShadow::cShadow()noexcept
: coreFullscreen ()
{
    this->DefineProgram("shadow_layer_program");
}


// ****************************************************************
void cShadow::Apply()
{
    this->SetPosition(coreVector2(0.0f,0.0f));
    this->SetSize    (coreVector2(1.0f,1.0f) * SQRT2 * Core::System->GetResolution().AspectRatio());
    this->Move();

    glDisable(GL_CULL_FACE);
    {
        glColorMask(false, false, false, false);
        glDepthMask(false);
        {
            Core::Graphics->WriteStencilTest(GL_KEEP, GL_INCR_WRAP, GL_KEEP, GL_DECR_WRAP);
            g_pGame->RenderShadow();
        }
        glColorMask(true, true, true, true);
        glDepthMask(true);

        glDisable(GL_DEPTH_TEST);
        {
            Core::Graphics->ReadStencilTest(GL_NOTEQUAL, 0u, 0xFFu);
            this->Render();
        }
        glEnable(GL_DEPTH_TEST);
    }
    glEnable(GL_CULL_FACE);

    Core::Graphics->EndStencilTest();
}