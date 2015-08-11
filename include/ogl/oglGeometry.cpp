#include "oglGeometry.h"
#include <iterator>
#include <algorithm>

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


}