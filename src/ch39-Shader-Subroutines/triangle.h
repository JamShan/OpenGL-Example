#ifndef Triangle_H
#define Triangle_H

#include <GL/glew.h>
#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"

namespace byhj
{

class Triangle
{
public:
	Triangle();
	~Triangle();

	void Init();
	void Render();
	void Shutdown();

private:
	void init_buffer();
	void init_vertexArray();
	void init_shader();

	Shader TriangleShader = { "Triangle Shader" };
	GLuint program = byhj::OGL_VALUE;

	GLuint offsetRed_loc;
	GLuint offsetGreen_loc;
	GLuint offsetBlue_loc;

	GLuint colorRed_loc;
	GLuint colorGreen_loc;
	GLuint colorBlue_loc;
};

}
#endif
