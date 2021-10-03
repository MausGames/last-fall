/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////


varying vec2 v_v2Relative;


void VertexMain()
{
    gl_Position      = coreObject2DPosition();
    v_av2TexCoord[0] = coreObject2DTexCoord();

    v_v2Relative = a_v2LowPosition;
}