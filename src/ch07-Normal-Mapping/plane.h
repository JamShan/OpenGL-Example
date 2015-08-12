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

		void Init();
		void Render();
		void Shutdown();

	private:
		void init_buffer();
		void init_vertexArray();
		void init_shader();
		void init_texture();

		Shader PlaneShader = { "Plane Shader" };
		GLuint program = byhj::OGL_VALUE;
		GLuint vao, ibo, vbo;
		GLuint colorTex = 0;
		GLuint normalTex = 1;

		struct Vertex
		{
			glm::vec3 Position;
			glm::vec2 TexCoord;
			glm::vec3 Normal;
			glm::vec3 Tangent;
			glm::vec3 BiTangent;
		};

		struct Uniform
		{
			GLuint colorTex_loc = byhj::OGL_VALUE;
			GLuint normalTex_loc = byhj::OGL_VALUE;
		}uniform;

	};

}
#endif
