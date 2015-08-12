#version 430 core

layout (location = 0) out vec4 fragColor;

in VS_OUT
{
 vec3 normal;
 vec3 worldPos;
}vs_out;

layout (binding = 0) uniform samplerCube cubemapTex;
uniform vec3 camPos = vec3(0.0f, 0.0f, 3.0f);

void main(void)
{
   vec3 I = normalize(vs_out.worldPos - camPos);
   vec3 R = reflect(I, normalize(vs_out.normal) );
   fragColor =  texture(cubemapTex, R);
}