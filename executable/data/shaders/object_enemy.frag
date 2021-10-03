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


void FragmentMain()
{
    const vec3 v3Camera = vec3(0.0, 1.0, -1.0);
    float fIntensity  = dot(normalize(v_v3Normal), -v3Camera) * 0.5 + 0.5;
          fIntensity *= dot(normalize(v_v3Relative), v3Camera);
          fIntensity *= min(inversesqrt(coreLengthSq(v_v3Relative)) * 50.0, 1.0);
    fIntensity *= max(v_v1Length, 0.0);
   // fIntensity += 0.1;

    gl_FragColor = vec4(vec3(fIntensity * 1.0), 1.0) * u_v4Color;
}