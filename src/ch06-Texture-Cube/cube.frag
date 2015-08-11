#version 430 core

layout (location = 0) out vec4 fragColor;

in VS_OUT
{
 vec3 normal;
 vec2 tex;
}vs_out;

uniform sampler2D tex;

void main(void)
{
   fragColor = texture2D(tex, vs_out.tex);
}