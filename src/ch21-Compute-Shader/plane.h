#ifndef Plane_H
#define Plane_H

#include <GL/glew.h>
#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

namespace byhj
{

class Plane
{
public:
	Plane();
	~Plane();

	void Init(int sw, int sh);
	void Render();
	void Shutdown();

private:
	void init_buffer();
	void init_vertexArray();
	void init_shader();
	void init_texture();

	Shader PlaneShader = { "Plane Shader" };
	Shader CompShader = { "Comp Shader" };

	GLuint program = byhj::OGL_VALUE;
	GLuint comp_prog = byhj::OGL_VALUE;

	GLuint vao, ibo, vbo;
	GLuint tex = 0;

	struct Uniform
	{
		GLuint planeTex_loc = byhj::OGL_VALUE;
		GLuint imageTex_loc = byhj::OGL_VALUE;
	}uniform;

	int m_ScreenWidth = 0;
	int m_ScreenHeight = 0;
};

}
#endif
