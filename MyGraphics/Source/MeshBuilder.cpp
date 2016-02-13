#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "MyMath.h"
#include "LoadOBJ.h"


float SphereX(float phi, float theta);
float SphereY(float phi, float theta);
float SphereZ(float phi, float theta);

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(-lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    //top
    v.pos.Set(0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(1, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v);

    for (unsigned i = 0; i < 6; ++i)
    {
        index_buffer_data.push_back(i);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLES;

    return mesh;
}


float SphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}

float SphereY(float phi, float theta)
{
	return sin(Math::DegreeToRadian(phi));
}

float SphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerStack = 180.f / numStacks;
	float anglePerSlice = 360.f / numSlices;
	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		float phi = -90.f + stack * anglePerStack;
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = anglePerSlice * slice;
			v.pos.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
            v.normal.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
            v.color = color;
			vertex_buffer_data.push_back(v);
		};
	};

	for (unsigned stack = 0; stack < numStacks; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back( (stack + 1) * (numSlices + 1) + slice);
		};
	};

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}


Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path)
{
    //Read vertices, texcoords & normals from OBJ
    std::vector<Position> vertices;
    std::vector<TexCoord> uvs;
    std::vector<Vector3> normals;
    bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
    if (!success)
        return NULL;
    //Index the vertices, texcoords & normals properly
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
    //Create the mesh and call glBindBuffer, glBufferData
    //Use triangle list and remember to set index size
    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLES;

    return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol) {
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float width = 1.f / numCol;
    float height = 1.f / numRow;
    int offset = 0;
    for (unsigned i = 0; i < numRow; ++i)
    {
        for (unsigned j = 0; j < numCol; ++j)
        {
            //Task: Add 4 vertices into vertex_buffer_data
            v.pos.Set(0.5f, -0.5f, 0.f);	v.normal.Set(0, 1, 0); v.texCoord.Set((width * j) + width, 1.f - (height * i) - height);	                vertex_buffer_data.push_back(v);
            v.pos.Set(0.5f, 0.5f, 0.f);	v.normal.Set(0, 1, 0);     v.texCoord.Set((width * j) + width, 1.f - (height * i));	                vertex_buffer_data.push_back(v);
            v.pos.Set(-0.5f, 0.5f, 0.f);	v.normal.Set(0, 1, 0); v.texCoord.Set(width * j, 1.f - (height * i));	                            vertex_buffer_data.push_back(v);
            v.pos.Set(-0.5f, -0.5f, -0.f);	v.normal.Set(0, 1, 0); v.texCoord.Set(width * j, 1.f - (height * i) - height);	                                vertex_buffer_data.push_back(v);

            //Task: Add 6 indices into index_buffer_data
            index_buffer_data.push_back(offset);
            index_buffer_data.push_back(offset + 1);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 3);
            offset += 4;
        }
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLES;

    return mesh;
}