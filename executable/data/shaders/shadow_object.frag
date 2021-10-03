/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////


varying float v_v1Height;


void FragmentMain()
{
    if(v_v1Height >= 0.05) discard;
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}