#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

uniform bool sunEnabled;
uniform bool fogEnabled;
uniform vec3 fogColor;

void main()
{
    vec4 color = texture(skybox, TexCoords);
    vec3 finalColor = color.rgb;
    if(fogEnabled){
        float fogFactor = 0.95;
        vec3 fColor = fogColor;
        if(!sunEnabled){
            fColor = vec3(0.0);
        }
        finalColor = mix(color.rgb, fColor, fogFactor);

    }

    FragColor = vec4(finalColor, color.a);
}