#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStacks = 18, unsigned numSlices = 36);
    static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
    static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif