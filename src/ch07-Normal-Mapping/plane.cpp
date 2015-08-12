#include "Plane.h"
#include "ogl/TextureManager.h"
namespace byhj
{

Plane::Plane()
{

}

Plane::~Plane() 
{

}

void Plane::Init()
{
	init_buffer();
	init_vertexArray();
	init_shader();
	init_texture();
}

void Plane::Render()
{
	//Use this shader and vao data to render
	glUseProgram(program);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(uniform.colorTex_loc, 0);
	TextureManager::Inst()->BindTexture(colorTex);

	glActiveTexture(GL_TEXTURE1);
	glUniform1i(uniform.normalTex_loc, 1);
	TextureManager::Inst()->BindTexture(normalTex);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}


void Plane::Shutdown()
{
	glDeleteProgram(program);
}


const static GLfloat VertexData[] = {
	// Positions             Normal              Tex
	-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
	-1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
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
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(6 * sizeof(GLfloat)));
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
	uniform.colorTex_loc = glGetUniformLocation(program, "colorTex");
	uniform.normalTex_loc = glGetUniformLocation(program, "normalTex");
}

void Plane::init_texture()
{
	TextureManager::Inst()->LoadTexture("../../media/textures/rock_color.tga", colorTex, GL_RGB, GL_RGB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);

	TextureManager::Inst()->LoadTexture("../../media/textures/rock_normal.tga", normalTex, GL_RGB, GL_RGB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);
}

}