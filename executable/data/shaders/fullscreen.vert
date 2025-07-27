/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "engine/data_transform_2d.glsl"


smoothEx varying vec2 v_v2Relative;


void VertexMain()
{
    gl_Position      = coreObject2DPosition();
    v_av2TexCoord[0] = coreObject2DTexCoord();

    v_v2Relative = a_v2LowPosition;
}