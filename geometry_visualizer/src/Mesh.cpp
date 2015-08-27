//======GVis Libraries==========
#include <GVis/Mesh.h>

//======OpenGL Related==========
#include <GL/glew.h>

namespace gvis {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) :
		Vertices_(vertices), Indices_(indices) 
	{
		Setup(vertices, indices);
	}


	void Mesh::Setup(std::vector<Vertex> vertices, std::vector<GLuint> indices) {
		// Provide this VAO for OpenGL to render
		glGenVertexArrays(1, &this->VAO_);
		glBindVertexArray(this->VAO_);

		// Setup vertex data
		glGenBuffers(1, &this->vbo_);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);
		glBufferData(GL_ARRAY_BUFFER, this->Vertices_.size() * sizeof(Vertex), &this->Vertices_[0], GL_STATIC_DRAW);

		// Setup indices
		glGenBuffers(1, &this->ebo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->Indices_.size() * sizeof(GLuint), &this->Indices_[0], GL_STATIC_DRAW);

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
		glBindVertexArray(this->VAO_);
		glDrawElements(GL_TRIANGLES, this->Indices_.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

}