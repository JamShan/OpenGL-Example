#version 430 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

out vec3 tc;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    mat4 mvp  = proj * view * model;
    vec4 pos = mvp * vec4(Position, 1.0f);
	tc = Position;

	//Set the z depth value to 1.0f for most far
	gl_Position = pos.xyww;
 }
