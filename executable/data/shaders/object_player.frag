/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////


varying vec3  v_v3Normal;
varying vec3  v_v3Relative;
varying float v_v1Length;


void FragmentMain()
{
    float v1Intensity  = dot(normalize(v_v3Normal),   c_v3Camera) * 0.5 + 0.5;
          v1Intensity *= dot(normalize(v_v3Relative), c_v3Camera);
          v1Intensity *= inversesqrt(coreLengthSq(v_v3Relative)) * 45.0;

    v1Intensity *= v_v1Length;

    gl_FragColor = vec4(vec3(v1Intensity), 1.0) * u_v4Color;
}