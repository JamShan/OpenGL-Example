#include "Plane.h"
#include "ogl/TextureManager.h"



namespace byhj
{

const int LocalSize = 16;

Plane::Plane()
{

}

Plane::~Plane()
{

}

void Plane::Init(int sw, int sh)
{
	m_ScreenWidth = sw;
	m_ScreenHeight = sh;

	init_buffer();
	init_vertexArray();
	init_shader();
	init_texture();
}

void Plane::Render()
{
	//Write the data to the image for a texture
	glUseProgram(comp_prog);

	glBindTexture(GL_TEXTURE_2D, tex);
	glBindImageTexture(0, tex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
	glUniform1i(uniform.imageTex_loc, 0);

	glDispatchCompute(m_ScreenWidth /LocalSize, m_ScreenHeight / LocalSize, 1);

	glUseProgram(0);

	///////////////////////Show the image data///////////////////////////////////
	glUseProgram(program);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(uniform.planeTex_loc, 0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}


void Plane::Shutdown()
{
	glDeleteProgram(program);
}


const static GLfloat VertexData[] = {
	// Positions        // Texture Coords
	-1.0, -1.0, 0.0,    0.0, 0.0,
	1.0, -1.0, 0.0,     1.0, 0.0,
	1.0, 1.0, 0.0,      1.0, 1.0,
	-1.0, 1.0, 0.0,     0.0, 1.0
};

const static GLuint ElementData[] = {  // Note that we start from 0!
	0, 1, 2, // First Triangle
	2, 3, 0  // Second Triangle
};

void Plane::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ElementData), ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Plane::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);         //notice, sizeof(GLfloat) usually is 4
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	glBindVertexArray(0);
}

void Plane::init_shader()
{
	PlaneShader.init();
	PlaneShader.attach(GL_VERTEX_SHADER, "Plane.vert");
	PlaneShader.attach(GL_FRAGMENT_SHADER, "Plane.frag");
	PlaneShader.link();
	program = PlaneShader.GetProgram();
	uniform.planeTex_loc = glGetUniformLocation(program, "tex");

	CompShader.init();
	CompShader.attach(GL_COMPUTE_SHADER, "plane.comp");
	CompShader.link();
	comp_prog = CompShader.GetProgram();
	uniform.imageTex_loc = glGetUniformLocation(program, "imageTex");
}

void Plane::init_texture()
{

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_ScreenWidth, m_ScreenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);
}

}