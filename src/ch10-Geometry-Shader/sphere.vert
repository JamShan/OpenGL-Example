#version 430 core

layout (location = 0) in vec4 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

out VS_OUT
{
 vec3 normal;
}vs_out;


void main(void)
{
   vs_out.normal = Normal; 
   gl_Position = Position;
}