#version 430 core

uniform mat4 mvp;

const vec4 Position[3] = 
{
   vec4(-0.5f, -0.5f, 0.0f, 1.0f),
   vec4( 0.5f, -0.5f, 0.0f, 1.0f),
   vec4( 0.0f,  0.5f, 0.0f, 1.0f)
};

//Your should declar it
out gl_PerVertex
{
	vec4 gl_Position;
};

void main(void)
{
    gl_Position = Position[gl_VertexID];
}