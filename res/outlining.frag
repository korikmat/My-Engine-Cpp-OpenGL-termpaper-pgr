#version 460 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec3 FragPos;
in vec3 Normal;

void main()
{
    gPosition = FragPos;

    gNormal = normalize(Normal);

    vec4 fragColor = vec4(1.0, 1.0, 1.0, 1.0);

    gAlbedoSpec = fragColor;
}