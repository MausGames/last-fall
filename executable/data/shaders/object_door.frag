/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "shared.glsl"


varying vec3 v_v3Normal;
varying vec3 v_v3Relative;


void FragmentMain()
{
    float v1Intensity  = dot(normalize(v_v3Normal),   c_v3Camera) * 0.5 + 0.5;
          v1Intensity *= dot(normalize(v_v3Relative), c_v3Camera);
          v1Intensity *= min(inversesqrt(coreLengthSq(v_v3Relative)) * 40.0, 1.0);

    gl_FragColor = vec4(vec3(v1Intensity + coreDither() / 255.0), 1.0) * u_v4Color;
}