/******************************************************************************/
/*!
\file       Mesh.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
class to define mesh
*/
/******************************************************************************/
#ifndef MESH_H
#define MESH_H

#include <string>
#include "MaterialBuilder.h"

/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	~Mesh();
	void Render();
    void Mesh::Render(unsigned offset, unsigned count);

	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned colorBuffer;
	unsigned indexBuffer;
	unsigned indexSize;
    unsigned textureID;

	Material material = MaterialBuilder::GenerateLambert();
};

#endif