/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////


smoothEx varying vec2 v_v2Relative;


void FragmentMain()
{
    float v1Intensity = (1.0 - 1.1 * coreLengthSq(v_v2Relative)) * 0.95;

    gl_FragColor = vec4(vec3(v1Intensity + coreDither() / 50.0), u_v4Color.a);
}