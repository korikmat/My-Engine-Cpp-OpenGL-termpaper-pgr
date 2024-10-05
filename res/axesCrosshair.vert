#version 330

uniform mat4 model;
uniform mat4 projView;

in vec4 position;
in vec4 color;

smooth out vec4 theColor;

void main() {
    gl_Position = projView * model * position;
    gl_Position.z = -1;
    gl_Position.w = 1;
    theColor = color;
}