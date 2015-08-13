#version 430 core

const vec4 Position[3] = 
{
   vec4(-0.5f, -0.5f, 0.0f, 1.0f),
   vec4( 0.5f, -0.5f, 0.0f, 1.0f),
   vec4( 0.0f,  0.5f, 0.0f, 1.0f)
};

subroutine vec4 GetOffset();

subroutine uniform GetOffset getOffset;

in vec4 a_vertex;

out gl_PerVertex
{
	vec4 gl_Position;
};

subroutine(GetOffset)
vec4 redOffset()
{
	return vec4(0.0, 0.5, 0.0, 1.0);
}

subroutine(GetOffset)
vec4 greenOffset()
{
	return vec4(-0.5, 0.0, 0.0, 1.0);
}

subroutine(GetOffset)
vec4 blueOffset()
{
	return vec4(0.5, 0.0, 0.0, 1.0);
}

void main(void)
{
	gl_Position = getOffset() + Position[gl_VertexID];
}
