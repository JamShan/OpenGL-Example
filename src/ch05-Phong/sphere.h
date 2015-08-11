#ifndef Triangle_H
#define Triangle_H

#include <GL/glew.h>
#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

namespace byhj
{

class Sphere
{
public:
	Sphere();
	~Sphere();

	void Init();
	void Render(float aspect);
	void Shutdown();

private:
	void init_buffer();
	void init_vertexArray();
	void init_shader();

	Shader CubeShader = { "Sphere Shader" };
	GLuint program = byhj::OGL_VALUE;
	GLuint vao = byhj::OGL_VALUE;
	GLuint vbo = byhj::OGL_VALUE;
	GLuint ibo = byhj::OGL_VALUE;

	struct Uniform
	{
		GLuint model_loc;
		GLuint view_loc ;
		GLuint proj_loc ;
	}uniform;

	GLuint m_VertexCount = 0;
	GLuint m_IndexCount  = 0;
};

}
#endif
