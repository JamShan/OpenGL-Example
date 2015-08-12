#include "Sphere.h"
#include "ogl/oglGeometry.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>

namespace byhj
{

Sphere::Sphere()
{

}

Sphere::~Sphere()
{

}

void Sphere::Init()
{
	init_buffer();
	init_vertexArray();
	init_shader();
}

void Sphere::Render(float aspect)
{
	//Use this shader and vao data to render
	glUseProgram(program);
	glBindVertexArray(vao);

	float currentTime = static_cast<float>( glfwGetTime());
	glm::mat4 view  = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj  = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), currentTime, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniform.model_loc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(uniform.view_loc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(uniform.proj_loc, 1, GL_FALSE, &proj[0][0]);

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}


void Sphere::Shutdown()
{
	glDeleteProgram(program);
}

void Sphere::init_buffer()
{
	byhj::MeshData meshData;
	OGLGeometry oglGeometry;
	oglGeometry.CreateSphere(1.0f, 100, 100, meshData);


	m_VertexCount = meshData.VertexData.size();
	m_IndexCount  = meshData.IndexData.size();

	for (int i = 0; i != m_IndexCount; i += 3)
	{
		GLuint index1 = meshData.IndexData[i];
		GLuint index2 = meshData.IndexData[i + 1];
		GLuint index3 = meshData.IndexData[i + 2];

		glm::vec3 va = meshData.VertexData[index1].Pos;
		glm::vec3 vb = meshData.VertexData[index2].Pos;
		glm::vec3 vc = meshData.VertexData[index3].Pos;

		glm::vec3 ab = va - vb;
		glm::vec3 bc = vb - vc;
		glm::vec3 n = glm::cross(ab, bc);

		meshData.VertexData[index1].Normal += n;
		meshData.VertexData[index2].Normal += n;
		meshData.VertexData[index3].Normal += n;
	}

	for (int i = 0; i != m_IndexCount; i++)
	{
		GLuint index = meshData.IndexData[i];
		glm::normalize( meshData.VertexData[index].Normal );
	}
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_VertexCount * sizeof(byhj::Vertex), &meshData.VertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount * sizeof(GLuint), &meshData.IndexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Sphere::init_vertexArray()
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

void Sphere::init_shader()
{
	SphereShader.init();
	SphereShader.attach(GL_VERTEX_SHADER, "Sphere.vert");
	SphereShader.attach(GL_GEOMETRY_SHADER, "sphere.geom");
	SphereShader.attach(GL_FRAGMENT_SHADER, "Sphere.frag");
	SphereShader.link();
	program = SphereShader.GetProgram();

	uniform.model_loc = glGetUniformLocation(program, "model");
	uniform.view_loc = glGetUniformLocation(program, "view");
	uniform.proj_loc = glGetUniformLocation(program, "proj");
}

}