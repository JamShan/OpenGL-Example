#version 430 core

layout (location = 0) out vec4 fragColor;

in VS_OUT
{
  vec4 color;
}vs_out;

void main(void)
{
   fragColor = vs_out.color;
}