#version 460 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gDiffuseShininess;
layout (location = 3) out vec4 gAmbientSpecular;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

struct Materials {
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform Materials material;
uniform bool useDiffTexture;
uniform bool useSpecTexture;

void main()
{
    gPosition = FragPos;

    gNormal = normalize(Normal);

    vec3 diffuse = material.diffuse.rgb;
    float shininess = material.shininess;
    vec3 specular = material.specular.rgb;
    vec3 ambient = material.diffuse.rgb;

    if(useDiffTexture){
        diffuse = texture(texture_diffuse1, TexCoords).rgb;
        ambient *= texture(texture_diffuse1, TexCoords).rgb;
    }
    if(useSpecTexture){
        specular += texture(texture_specular1, TexCoords).rgb;
    }

    gDiffuseShininess.rgb = diffuse;
    gDiffuseShininess.a = shininess;
    gAmbientSpecular.rgb = ambient;
    gAmbientSpecular.a = specular.r;
}