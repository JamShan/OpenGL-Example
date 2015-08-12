#include "Cube.h"
#include "ogl/oglGeometry.h"
#include "ogl/loadTexture.h"
#include "ogl/oglDebug.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>
#include <FreeImage.h>

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
	init_texture();

}

void Cube::Render(float aspect)
{
	float currentTime = static_cast<float>(glfwGetTime());
	glm::mat4 view  = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj  = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), currentTime, glm::vec3(1.0f, 1.0f, 1.0f));


	glDepthFunc(GL_LEQUAL);

	//Use this shader and vao data to render
	glUseProgram(skybox_prog);
	glBindVertexArray(vao);

	glm::mat4 skybox_view  = glm::mat4( glm::mat3(view) );
	glm::mat4 skybox_proj  = proj;
	glm::mat4 skybox_model = glm::rotate(glm::mat4(1.0f), currentTime, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(skybox_uniform.model_loc, 1, GL_FALSE, &skybox_model[0][0]);
	glUniformMatrix4fv(skybox_uniform.view_loc, 1, GL_FALSE,  &skybox_view[0][0]);
	glUniformMatrix4fv(skybox_uniform.proj_loc, 1, GL_FALSE,  &skybox_proj[0][0]);


	glActiveTexture(GL_TEXTURE0);
	glUniform1i(skybox_uniform.cubeMapTex_loc, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTex);

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);

	glDepthFunc(GL_LESS);

	///////////////////////////////////////////////////////////////////////////////////

	//Use this shader and vao data to render
	glUseProgram(cube_prog);
	glBindVertexArray(vao);

	glUniformMatrix4fv(cube_uniform.model_loc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(cube_uniform.view_loc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(cube_uniform.proj_loc, 1, GL_FALSE, &proj[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(cube_uniform.cubeMapTex_loc, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTex);

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);

}


void Cube::Shutdown()
{

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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(byhj::Vertex), (GLvoid*)( sizeof(glm::vec3) * 3) );
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(byhj::Vertex), (GLvoid*)( sizeof(glm::vec3) * 6) );

	glBindVertexArray(0);
}

void Cube::init_shader()
{
	CubeShader.init();
	CubeShader.attach(GL_VERTEX_SHADER, "Cube.vert");
	CubeShader.attach(GL_FRAGMENT_SHADER, "Cube.frag");
	CubeShader.link();
	cube_prog = CubeShader.GetProgram();

	cube_uniform.cubeMapTex_loc = glGetUniformLocation(cube_prog, "cubemapTex");
	cube_uniform.model_loc = glGetUniformLocation(cube_prog, "model");
	cube_uniform.view_loc = glGetUniformLocation(cube_prog, "view");
	cube_uniform.proj_loc = glGetUniformLocation(cube_prog, "proj");

	SkyboxShader.init();
	SkyboxShader.attach(GL_VERTEX_SHADER, "skybox.vert");
	SkyboxShader.attach(GL_FRAGMENT_SHADER, "skybox.frag");
	SkyboxShader.link();
	skybox_prog = SkyboxShader.GetProgram();

	skybox_uniform.cubeMapTex_loc = glGetUniformLocation(skybox_prog, "cubemapTex");
	skybox_uniform.model_loc = glGetUniformLocation(skybox_prog, "model");
	skybox_uniform.view_loc = glGetUniformLocation(skybox_prog, "view");
	skybox_uniform.proj_loc = glGetUniformLocation(skybox_prog, "proj");

}



void Cube::init_texture()
{

	std::vector<std::string> faces;
	faces.push_back("../../media/textures/skybox/right.jpg");
	faces.push_back("../../media/textures/skybox/left.jpg");
	faces.push_back("../../media/textures/skybox/top.jpg");
	faces.push_back("../../media/textures/skybox/bottom.jpg");
	faces.push_back("../../media/textures/skybox/back.jpg");
	faces.push_back("../../media/textures/skybox/front.jpg");

	cubeMapTex = loadCubeMap(faces);

	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTex);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

}