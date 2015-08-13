#include "Triangle.h"
#include "ogl/loadText.h"

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

void Triangle::Render(float aspect)
{
	glBindProgramPipeline(pipeline);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) );
	glm::mat4 proj = glm::perspective(45.0f, aspect, 1.0f, 1000.0f);
	glm::mat4 mvp = model * view * proj;
	glProgramUniformMatrix4fv(vert_prog, mvp_loc, 1, GL_FALSE, &mvp[0][0]);

	const static GLfloat color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glProgramUniform4fv(frag_prog, color_loc, 1, color);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindProgramPipeline(0);

}


void Triangle::Shutdown()
{
	glDeleteProgram(vert_prog);
	glDeleteProgram(frag_prog);
	glDeleteProgramPipelines(1, &pipeline);
}

void Triangle::init_buffer()
{

}

void Triangle::init_vertexArray()
{

}

void Triangle::init_shader()
{
	glGenProgramPipelines(1, &pipeline);

	const char *vertContent = byhj::loadText("triangle.vert");
	vert_prog = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vertContent);
	glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vert_prog);
	mvp_loc = glGetUniformLocation(vert_prog, "mvp");


	const char *fragContext = byhj::loadText("triangle.frag");
	frag_prog = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragContext);
	glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, frag_prog);
	color_loc = glGetUniformLocation(frag_prog, "color");




}

}