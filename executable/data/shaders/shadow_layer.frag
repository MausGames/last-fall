/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////


void FragmentMain()
{
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.4 * u_v4Color.a);
}