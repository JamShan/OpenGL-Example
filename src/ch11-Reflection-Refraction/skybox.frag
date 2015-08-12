#version 430 core

layout(location = 0) out vec4 fragColor;

in vec3 tc;
uniform samplerCube cubemapTex;

void main()
{    
    fragColor = texture(cubemapTex, tc);
}