#include "oglGeometry.h"
#include <iterator>
#include <algorithm>
#include <glm/gtc/constants.hpp>

namespace byhj
{

OGLGeometry::OGLGeometry()
{

}


OGLGeometry::~OGLGeometry()
{


}

void OGLGeometry::CreateCube(float width, float height, float depth, MeshData &mesh)
{
	Vertex vertexes[24];
	float w2 = 0.5f * width;
	float h2 = 0.5f * height;
	float d2 = 0.5f * depth;

	//                    Position         Normal          TexCoord
	// Fill in the front face vertex data.
	vertexes[0] = Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertexes[1] = Vertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertexes[2] = Vertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertexes[3] = Vertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	vertexes[4] = Vertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	vertexes[5] = Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	vertexes[6] = Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	vertexes[7] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	vertexes[8] = Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	vertexes[9] = Vertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	vertexes[10] = Vertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	vertexes[11] = Vertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	vertexes[12] = Vertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	vertexes[13] = Vertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	vertexes[14] = Vertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	vertexes[15] = Vertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	vertexes[16] = Vertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertexes[17] = Vertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertexes[18] = Vertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	vertexes[19] = Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	vertexes[20] = Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertexes[21] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertexes[22] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	vertexes[23] = Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	mesh.VertexData.clear();
	mesh.VertexData.assign( std::begin(vertexes), std::end(vertexes) );


	//////////////////////////indexes////////////////////////
	GLuint indexes[36];
	// Fill in the front face indexes data
	indexes[0] = 0; indexes[1] = 1; indexes[2] = 2;
	indexes[3] = 0; indexes[4] = 2; indexes[5] = 3;

	// Fill in the back face indexes data
	indexes[6] = 4; indexes[7] = 5; indexes[8] = 6;
	indexes[9] = 4; indexes[10] = 6; indexes[11] = 7;

	// Fill in the top face indexes data
	indexes[12] = 8; indexes[13] = 9; indexes[14] = 10;
	indexes[15] = 8; indexes[16] = 10; indexes[17] = 11;

	// Fill in the bottom face indexes data
	indexes[18] = 12; indexes[19] = 13; indexes[20] = 14;
	indexes[21] = 12; indexes[22] = 14; indexes[23] = 15;

	// Fill in the left face indexes data
	indexes[24] = 16; indexes[25] = 17; indexes[26] = 18;
	indexes[27] = 16; indexes[28] = 18; indexes[29] = 19;

	// Fill in the right face indexes data
	indexes[30] = 20; indexes[31] = 21; indexes[32] = 22;
	indexes[33] = 20; indexes[34] = 22; indexes[35] = 23;

	mesh.IndexData.clear();
	mesh.IndexData.assign(std::begin(indexes), std::end(indexes) );
}


void OGLGeometry::CreateSphere(float radius, int sliceCount, int stackCount, MeshData& meshData)
{
	//
	// Compute the vertices stating at the top pole and moving down the stacks.
	//

	// Poles: note that there will be texture coordinate distortion as there is
	// not a unique point on the texture map to assign to the pole when mapping
	// a rectangular texture onto a sphere.
	Vertex topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, 0.0f);
	Vertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);

	meshData.VertexData.push_back(topVertex);

	float phiStep = glm::pi<float>() / stackCount;
	float thetaStep = 2.0f * glm::pi<float>() / sliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for (int  i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i*phiStep;

		// Vertices of ring.
		for (int  j = 0; j <= sliceCount; ++j)
		{
			float theta = j*thetaStep;

			Vertex v;

			// spherical to cartesian
			v.Pos.x = radius * sinf(phi) * cosf(theta);
			v.Pos.y = radius * cosf(phi);
			v.Pos.z = radius * sinf(phi) * sinf(theta);

			v.Normal = glm::vec3(0.0f);

			v.Tex.x = theta / glm::pi<float>() * 2.0f;
			v.Tex.y = phi / glm::pi<float>();

			meshData.VertexData.push_back(v);
		}
	}
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for (int i = 1; i <= sliceCount; ++i)
	{
		meshData.IndexData.push_back(0);
		meshData.IndexData.push_back(i + 1);
		meshData.IndexData.push_back(i);
	}

	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	int baseIndex = 1;
	int ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount - 2; ++i)
	{
		for (int j = 0; j < sliceCount; ++j)
		{
			meshData.IndexData.push_back(baseIndex + i*ringVertexCount + j);
			meshData.IndexData.push_back(baseIndex + i*ringVertexCount + j + 1);
			meshData.IndexData.push_back(baseIndex + (i + 1)*ringVertexCount + j);

			meshData.IndexData.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			meshData.IndexData.push_back(baseIndex + i*ringVertexCount + j + 1);
			meshData.IndexData.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	int southPoleIndex = meshData.VertexData.size() - 1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVertexCount;

	for (int i = 0; i < sliceCount; ++i)
	{
		meshData.IndexData.push_back(southPoleIndex);
		meshData.IndexData.push_back(baseIndex + i);
		meshData.IndexData.push_back(baseIndex + i + 1);
	}
}


}