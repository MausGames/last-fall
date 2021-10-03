/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////


varying vec2 v_v2Relative;


void FragmentMain()
{
    float fIntensity = (1.0 - 1.1 * coreLengthSq(v_v2Relative)) * 0.95;

    gl_FragColor = vec4(vec3(fIntensity), u_v4Color.a);
}