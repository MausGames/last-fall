/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////


varying float v_v1Height;


void VertexMain()
{
    v_v1Height  = a_v3RawPosition.z;
    gl_Position = coreObject3DPositionRaw();
}