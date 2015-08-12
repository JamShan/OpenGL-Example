#version 430 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

out VS_OUT
{
 vec3 normal;
 vec3 worldPos;
}vs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(void)
{
   vs_out.normal = mat3( transpose( inverse(model) ) )* Normal; 
   vs_out.worldPos = mat3(model) * Position;

   mat4 mvp = proj * view * model;
   gl_Position = mvp * vec4(Position, 1.0f);
   
}