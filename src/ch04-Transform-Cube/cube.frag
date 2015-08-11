#version 430 core

layout (location = 0) out vec4 fragColor;

in VS_OUT
{
 vec3 normal;
 vec2 tex;
}vs_out;


void main(void)
{
   fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}