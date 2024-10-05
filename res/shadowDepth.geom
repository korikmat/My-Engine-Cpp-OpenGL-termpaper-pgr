#version 460 core
layout (triangles, invocations = 6) in;
layout (triangle_strip, max_vertices=18) out;

struct LightData
{
    vec3 position;
    vec3 color;
    vec3 attenuation;
    vec4 direction_angle;
    mat4 vp[6];
};

layout(std140, binding = 0) uniform Light
{
    LightData lightData[10];
} light_g;

uniform int light_i;

out vec4 FragPos;
out vec3 lightPos;
out float radius;

void main()
{

    for(int i = 0; i < 3; ++i)
    {
        FragPos = gl_in[i].gl_Position;
        lightPos = light_g.lightData[light_i].position;
        radius = light_g.lightData[light_i].attenuation.r;
        gl_Position = light_g.lightData[light_i].vp[gl_InvocationID] * FragPos;
        gl_Layer = gl_InvocationID + light_i*6;
        EmitVertex();
    }
    EndPrimitive();

}