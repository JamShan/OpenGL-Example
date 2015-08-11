#ifndef OGLGEOMETRY_H
#define OGLGEOMETRY_H

#include <gl/glew.h>
#include <vector>
#include <glm/glm.hpp>

namespace byhj
{

	struct  Vertex
	{
		Vertex() {}
		Vertex(const glm::vec3 &pos, const glm::vec3 &normal, const glm::vec2 &tc)
			:Pos(pos), Normal(normal), Tex(tc) {}

		Vertex(float px, float py, float pz,
			float nx, float ny, float nz,
			float u, float v) : Pos(px, py, pz), Normal(nx, ny, nz), Tex(u, v) {}

		glm::vec3 Pos;
		glm::vec3 Normal;
		glm::vec2 Tex;
	};

	struct MeshData
	{
		std::vector<Vertex> VertexData;
		std::vector<GLuint> IndexData;
	};

class OGLGeometry
{
public:
	OGLGeometry();
	~OGLGeometry();

	void CreateCube(float width, float height, float depth, MeshData &mesh);

	/// Creates a sphere centered at the origin with the given radius.  The
	/// slices and stacks parameters control the degree of tessellation.

	void CreateSphere(float radius, int sliceCount, int stackCount, MeshData& mesh);

private:


};



}
#endif 