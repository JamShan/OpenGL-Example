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
}

void Plane::Render()
{
	//Use this shader and vao data to render
	glUseProgram(program);
	glBindVertexArray(vao);

	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glDrawElements(GL_PATCHES, 4, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}


void Plane::Shutdown()
{
	glDeleteProgram(program);
}


const static GLfloat VertexData[] = 
{
	// Positions     
	-0.5, -0.5, 0.0,
	 0.5, -0.5, 0.0,
	 0.5,  0.5, 0.0,
	-0.5,  0.5, 0.0,
};

const static GLuint ElementData[] = {  // Note that we start from 0!
	0, 1, 2, 3
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	glBindVertexArray(0);
}

void Plane::init_shader()
{
	PlaneShader.init();
	PlaneShader.attach(GL_VERTEX_SHADER, "Plane.vert");
	PlaneShader.attach(GL_TESS_CONTROL_SHADER, "Plane.tcs");
	PlaneShader.attach(GL_TESS_EVALUATION_SHADER, "plane.tes");
	PlaneShader.attach(GL_GEOMETRY_SHADER, "plane.geom");
	PlaneShader.attach(GL_FRAGMENT_SHADER, "Plane.frag");
	PlaneShader.link();
	program = PlaneShader.GetProgram();
}

}