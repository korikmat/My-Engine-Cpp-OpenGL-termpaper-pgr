#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 texCoord;

void main()
{
    texCoord = (aPos.xy + vec2(1.0)) / 2;
    gl_Position = vec4(aPos, 1.0);
}