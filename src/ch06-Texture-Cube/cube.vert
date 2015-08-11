#version 430 core

layout (location = 0) in vec4 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

out VS_OUT
{
 vec3 normal;
 vec2 tex;
}vs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(void)
{
   vs_out.normal = mat3( transpose( inverse(model) ) )* Normal; 
   vs_out.tex = TexCoord;
   mat4 mvp = proj * view * model;
   gl_Position = mvp * Position;
   
}