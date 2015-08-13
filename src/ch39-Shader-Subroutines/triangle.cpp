#include "Triangle.h"

namespace byhj
{

Triangle::Triangle()
{

}

Triangle::~Triangle()
{

}

void Triangle::Init()
{
	init_buffer();
	init_vertexArray();
	init_shader();
}

void Triangle::Render()
{
	glUseProgram(program);

	// Setting up functions for the red triangle.
	glUniformSubroutinesuiv(GL_VERTEX_SHADER,   1, &offsetRed_loc);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &colorRed_loc);

	glDrawArrays(GL_TRIANGLES, 0, 3);

///////////////////////////////////////////////////////////////

	// Setting up functions for the green triangle.
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &offsetGreen_loc);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &colorGreen_loc);

	glDrawArrays(GL_TRIANGLES, 0, 3);

///////////////////////////////////////////////////////////////////////////
	// Setting up functions for the blue triangle.
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &offsetBlue_loc);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &colorBlue_loc);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glUseProgram(0);
}


void Triangle::Shutdown()
{
	glDeleteProgram(program);
}

void Triangle::init_buffer()
{

}

void Triangle::init_vertexArray()
{

}

void Triangle::init_shader()
{
	TriangleShader.init();
	TriangleShader.attach(GL_VERTEX_SHADER, "triangle.vert");
	TriangleShader.attach(GL_FRAGMENT_SHADER, "triangle.frag");
	TriangleShader.link();
	program = TriangleShader.GetProgram();

	// Get the subroutine indices from the vertex shader.
	offsetRed_loc   = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "redOffset");
	offsetGreen_loc = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "greenOffset");
	offsetBlue_loc  = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "blueOffset");

	// Get the subroutine indices from the fragment shader.
	colorRed_loc    = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, "redColor");
	colorGreen_loc  = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, "greenColor");
	colorBlue_loc   = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, "blueColor");

}

}