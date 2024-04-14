/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "shared.glsl"


varying vec2 v_v2Center;
varying vec3 v_v3Normal;
varying vec3 v_v3Relative;


void FragmentMain()
{
    vec4 v4Texture = coreTexture2D(0, v_av2TexCoord[0]);

    float v1Intensity  = dot(normalize(v_v3Normal),   vec3(0.0, 0.0, 1.0)) * 0.5 + 0.5;
          v1Intensity *= dot(normalize(v_v3Relative), c_v3Camera);
          v1Intensity *= min(inversesqrt(coreLengthSq(v_v3Relative)) * 50.0, 1.0);

    vec3 v3Color1 = u_v4Color.rgb * mix(1.0, 0.45, smoothstep(0.85, 0.89, max(abs(v_v2Center.x), abs(v_v2Center.y))));
    vec3 v3Color2 = mix(u_v4Color.rgb * 0.45, vec3(1.0), v4Texture.rgb);

    gl_FragColor = vec4(mix(v3Color1, v3Color2, v4Texture.a) * v1Intensity + vec3(coreDither() / 255.0), u_v4Color.a);
}