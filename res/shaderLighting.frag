#version 460 core
out vec4 color;

in vec2 texCoord;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gDiffuseShininess;
uniform sampler2D gAmbientSpecular;

uniform samplerCubeArray depthMap;

struct Sun
{
    vec3 direction;
    vec3 color;
    bool enabled;
};

struct LightData
{
    vec3 position;
    vec3 color;
    vec3 attenuation;
    vec4 direction_angle;
    mat4 vp[6];
};

struct Fog
{
    vec3 color;
    float density;
    bool enabled;
};

layout(std140, binding = 0) uniform Light
{
    LightData lightData[10];
} light_f;

uniform vec3 viewPos;

uniform int lightsCount;

uniform Sun sun;

uniform Fog fog;


void main()
{
    vec3 fragPos = texture(gPosition, texCoord).rgb;
    vec3 N = texture(gNormal, texCoord).rgb;
    vec3 kd = texture(gDiffuseShininess, texCoord).rgb;
    float p = texture(gDiffuseShininess, texCoord).a;
    vec3 ka = texture(gAmbientSpecular, texCoord).rgb;
    ka = ka*0.2;
    float ks = texture(gAmbientSpecular, texCoord).a;


    vec3 L_vertex;
    vec3 Cam_vertex = normalize(viewPos - fragPos);
    float diffuse;
    vec3 H;
    float specular;
    float L_distance;
    float attenuation;
    float acosA;
    float intensity;
    vec3 fragPosLightSpace;
    float shadowValue;
    float pcfDepth;
    float cubemap_offset = 0.05f;
    float cubemap_depth;

    color = vec4(ka, 1);
    if (sun.enabled){
        vec3 sunDir = normalize(-sun.direction);
        diffuse = max(dot(sunDir, N), 0.0);

        H = normalize(sunDir + Cam_vertex);
        specular = pow(max(dot(H, N), 0.0), p);

        color += vec4(sun.color*kd*diffuse, 1) + vec4(sun.color*ks*specular, 1);
    }


    int i;
    for (i = 0; i < lightsCount; i++)
    {
        shadowValue = 0;
        fragPosLightSpace = fragPos - light_f.lightData[i].position;
        cubemap_depth = length(fragPosLightSpace) / light_f.lightData[i].attenuation.r;

        pcfDepth = texture(depthMap, vec4(fragPosLightSpace, i)).r;
        if (cubemap_depth - 0.15/light_f.lightData[i].attenuation.r > pcfDepth)
        shadowValue = 1.0;


        L_vertex = light_f.lightData[i].position - fragPos;

        L_distance = length(L_vertex);

        if (L_distance < light_f.lightData[i].attenuation.r)
        {
            L_vertex = normalize(L_vertex);
            acosA = degrees(acos(dot(-L_vertex, normalize(light_f.lightData[i].direction_angle.xyz))));
            if (acosA <= light_f.lightData[i].direction_angle.a/2)
            {
                diffuse = max(dot(L_vertex, N), 0.0);

                H = normalize(L_vertex + Cam_vertex);
                specular = pow(max(dot(H, N), 0.0), p);

                attenuation = 1 / (1 + light_f.lightData[i].attenuation[1] * L_distance + light_f.lightData[i].attenuation[2] * L_distance * L_distance);

                if (light_f.lightData[i].direction_angle.a/2 < 180)
                {
                    intensity = clamp((light_f.lightData[i].direction_angle.a/2 - acosA) / 5, 0.0, 1.0);
                    diffuse  *= intensity;
                    specular *= intensity;
                }

                vec3 diffColor = light_f.lightData[i].color*kd*diffuse;
                vec3 specColor = light_f.lightData[i].color*ks*specular;
                if (fog.enabled){
                    float distance = length(viewPos - fragPos);

                    float fogFactor = 1.0 - exp(-fog.density * distance);

                    fogFactor = clamp(fogFactor, 0.0, 1.0);

                    diffColor = mix(light_f.lightData[i].color*kd*diffuse, light_f.lightData[i].color, fogFactor);
                    specColor = mix(light_f.lightData[i].color*ks*specular, light_f.lightData[i].color, fogFactor);
                }

                color += (vec4(diffColor * attenuation, 1)
                + vec4(specColor * attenuation, 1))  * (1.0 - shadowValue);

            }

        }
    }
    if(fog.enabled){
        float distance = length(viewPos - fragPos);

        float fogFactor = 1.0 - exp(-fog.density/4 * distance);

        fogFactor = clamp(fogFactor, 0.0, 1.0);
        vec3 fogColor = fog.color;
        if(!sun.enabled){
            fogColor = vec3(0.0);
        }
        color = vec4(mix(color.rgb, fogColor, fogFactor), 1.0);
    }


}