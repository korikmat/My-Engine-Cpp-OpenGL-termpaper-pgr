#version 460 core
in vec4 FragPos;
in vec3 lightPos;
in float radius;

void main()
{
    float lightDistance = length(FragPos.xyz - lightPos);

    lightDistance = lightDistance / radius;

    gl_FragDepth = lightDistance;
}