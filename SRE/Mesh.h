#pragma once

#include "GLEW/include/GL/glew.h"


//////////////////////////////////////////////////////////////////////////
// not sure if i should store a pointer to the shader here
//////////////////////////////////////////////////////////////////////////

namespace SRE
{
	class Mesh
	{
	public:
		Mesh();

		void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
		void RenderMesh();
		void ClearMesh();

		~Mesh();

	private:
		GLuint VAO, VBO, IBO;
		GLsizei indexCount;
	};
}
