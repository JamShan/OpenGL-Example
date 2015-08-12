#version 430 core

layout(triangles) in;

layout(line_strip, max_vertices = 3) out;

void main(void)
{

    for (int i = 0; i != gl_in.length(); ++i)
	{
	    gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}