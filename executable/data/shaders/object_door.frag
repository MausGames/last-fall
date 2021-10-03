/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////


varying vec2 v_v2Center;
varying vec3 v_v3Normal;
varying vec3 v_v3Normal2;
varying vec3 v_v3Relative;


void FragmentMain()
{
    //vec4  v4Texture = coreTexture2D(0, v_av2TexCoord[0]).rgba;
    //vec3  v3Number  = v4Texture.rgb;//vec3(0.15 + 0.85*v2Texture.r);
    //float v1Alpha   = v4Texture.a;//max(v2Texture.r, v2Texture.g);
    //float v1Dark = smoothstep(0.85, 0.89, max(abs(v_v2Center.x), abs(v_v2Center.y)));

    const vec3 v3Camera = vec3(0.0, 1.0, -1.0);
    float fIntensity  = dot(normalize(v_v3Normal2),  -v3Camera) * 0.5 + 0.5;
          fIntensity *= dot(normalize(v_v3Relative), v3Camera);
          fIntensity *= min(inversesqrt(coreLengthSq(v_v3Relative)) * 50.0, 1.0);

    //gl_FragColor = vec4(mix(u_v4Color.rgb, mix(u_v4Color.rgb * 0.45, vec3(1.0), v3Number), v1Alpha) * fIntensity, u_v4Color.a);
    gl_FragColor = vec4(vec3(fIntensity), 1.0) * u_v4Color;
}