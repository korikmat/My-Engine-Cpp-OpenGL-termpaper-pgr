#version 460 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gDiffuseShininess;
layout (location = 3) out vec4 gAmbientSpecular;

in vec3 FragPos;
in vec3 Normal;

struct Materials {
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform Materials material;

void main()
{
    gPosition = FragPos;

    gNormal = normalize(Normal);

    vec3 diffuse = material.diffuse.rgb;
    float shininess = material.shininess;
    vec3 specular = material.specular.rgb;
    vec3 ambient = material.diffuse.rgb;

    vec4 fragColor = vec4(106.0/255.0, 116.0/255.0, 166.0/255.0, 1.0);
    if(Normal.y > 0.55f){
        fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }

    gDiffuseShininess.rgb = fragColor.rgb;
    gDiffuseShininess.a = shininess;
    gAmbientSpecular.rgb = fragColor.rgb;
    gAmbientSpecular.a = specular.r;
}