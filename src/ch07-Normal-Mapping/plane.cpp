#include "Plane.h"
#include "ogl/Texture.h"

#include <glfw/glfw3.h>

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

void Plane::Render(float aspect)
{
	//Use this shader and vao data to render
	glUseProgram(program);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(uniform.colorTex_loc, 0);
	glBindTexture(GL_TEXTURE_2D, colorTex);

	glActiveTexture(GL_TEXTURE1);
	glUniform1i(uniform.normalTex_loc, 1);
	glBindTexture(GL_TEXTURE_2D, normalTex);


	float currentTime = static_cast<float>(glfwGetTime());
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);
	glm::mat4 model = glm::mat4(1.0f);// glm::rotate(glm::mat4(1.0f), currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniform.model_loc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(uniform.view_loc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(uniform.proj_loc, 1, GL_FALSE, &proj[0][0]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}


void Plane::Shutdown()
{
	glDeleteProgram(program);
}


const static GLfloat VertexData[] = {
	// Positions             Normal              Tex          Tangent           BiTangent
	-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	 1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	-1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
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
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), BUFFER_OFFSET(6 * sizeof(GLfloat)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), BUFFER_OFFSET(8 * sizeof(GLfloat)));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), BUFFER_OFFSET(11 * sizeof(GLfloat)));

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
	uniform.model_loc = glGetUniformLocation(program, "model");
	uniform.view_loc = glGetUniformLocation(program, "view");
	uniform.proj_loc = glGetUniformLocation(program, "proj");
}

void Plane::init_texture()
{
	colorTex = loadTexture("../../media/textures/rock_color.tga");
	normalTex = loadTexture("../../media/textures/rock_normal.tga");
}

}