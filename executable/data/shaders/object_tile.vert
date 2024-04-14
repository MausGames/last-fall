/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "engine/data_transform_3d.glsl"


varying vec2 v_v2Center;
varying vec3 v_v3Normal;
varying vec3 v_v3Relative;


void VertexMain()
{
    gl_Position      = coreObject3DPositionRaw();
    v_av2TexCoord[0] = coreObject3DTexCoordRaw();

    v_v2Center   = a_v2RawTexCoord * 2.0 - 1.0;
    v_v3Normal   = a_v3RawNormal;
    v_v3Relative = (u_m4Camera * vec4(coreObject3DTransformRaw(), 1.0)).xyz;
}