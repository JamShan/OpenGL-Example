#include "Cube.h"
#include "ogl/oglGeometry.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>

namespace byhj
{

Cube::Cube()
{

}

Cube::~Cube()
{

}

void Cube::Init()
{
	init_buffer();
	init_vertexArray();
	init_shader();
}

void Cube::Render(float aspect)
{
	//Use this shader and vao data to render
	glUseProgram(program);
	glBindVertexArray(vao);

	float currentTime = static_cast<float>( glfwGetTime());
	glm::mat4 view  = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj  = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), currentTime, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniform.model_loc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(uniform.view_loc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(uniform.proj_loc, 1, GL_FALSE, &proj[0][0]);

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}


void Cube::Shutdown()
{
	glDeleteProgram(program);
}

void Cube::init_buffer()
{
	byhj::MeshData meshData;
	OGLGeometry oglGeometry;
	oglGeometry.CreateCube(1.0f, 1.0f, 1.0f, meshData);

	m_VertexCount = meshData.VertexData.size();
	m_IndexCount  = meshData.IndexData.size();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_VertexCount * sizeof(byhj::Vertex), &meshData.VertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount * sizeof(GLuint), &meshData.IndexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Cube::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(byhj::Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(byhj::Vertex), (GLvoid*)( sizeof(glm::vec3) ) );
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(byhj::Vertex), (GLvoid*)( sizeof(glm::vec3) * 2));

	glBindVertexArray(0);
}

void Cube::init_shader()
{
	CubeShader.init();
	CubeShader.attach(GL_VERTEX_SHADER, "Cube.vert");
	CubeShader.attach(GL_FRAGMENT_SHADER, "Cube.frag");
	CubeShader.link();
	program = CubeShader.GetProgram();

	uniform.model_loc = glGetUniformLocation(program, "model");
	uniform.view_loc = glGetUniformLocation(program, "view");
	uniform.proj_loc = glGetUniformLocation(program, "proj");
}

}