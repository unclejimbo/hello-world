//======GVis Libraries==========
#include <GVis/Mesh.h>

//======OpenGL Related==========
#include <GL/glew.h>

namespace gvis {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) :
		Vertices(vertices), Indices(indices) 
	{
		// Provide this VAO for OpenGL to render
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		// Setup vertex data
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->Vertices.size() * sizeof(Vertex), &this->Vertices[0], GL_STATIC_DRAW);

		// Setup indices
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->Indices.size() * sizeof(GLuint), &this->Indices[0], GL_STATIC_DRAW);

		// Setup vertex attributes
		// 0 for Vertex Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		// 1 for Vertex Normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		// Add more attributes here:

		glBindVertexArray(0);
	}


	void Mesh::Draw() {
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, this->Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

}