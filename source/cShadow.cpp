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

    glStencilMask(0xFFu);
    glClearStencil(128);
}


// ****************************************************************
void cShadow::Apply()
{
    this->SetPosition(coreVector2(0.0f,0.0f));
    this->SetSize    (coreVector2(1.0f,1.0f) * SQRT2 * Core::System->GetResolution().AspectRatio());
    this->Move();

    glDisable(GL_CULL_FACE);
    glEnable (GL_STENCIL_TEST);
    {
        glColorMask(false, false, false, false);
        glDepthMask(false);
        {
            glStencilOpSeparate(GL_BACK,  GL_KEEP, GL_KEEP, GL_INCR);
            glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_DECR);
            glStencilFunc(GL_ALWAYS, 0, 0xFFu);

            g_pGame->RenderShadow();
        }
        glColorMask(true, true, true, true);
        glDepthMask(true);

        glDisable(GL_DEPTH_TEST);
        {
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
            glStencilFunc(GL_NOTEQUAL, 128, 0xFFu);

            this->Render();
        }
        glEnable(GL_DEPTH_TEST);
    }
    glEnable (GL_CULL_FACE);
    glDisable(GL_STENCIL_TEST);
}