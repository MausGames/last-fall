/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////


varying float v_v1Length;
varying vec3  v_v3Normal;
varying vec3  v_v3Relative;


void VertexMain()
{
    gl_Position      = coreObject3DPositionRaw();
    v_av2TexCoord[0] = coreObject3DTexCoordRaw();

    //v_v1Length   = 0.25;//4.6 - 4.2 * length(a_v3RawPosition);
    v_v1Length   = 1.5 - 1.0 * length(a_v3RawPosition);
    v_v3Normal   = coreQuatApply(u_v4Rotation, a_v3RawNormal);//a_v3RawPosition;
    v_v3Relative = (u_m4Camera * vec4(coreObject3DTransformRaw(), 1.0)).xyz;
}