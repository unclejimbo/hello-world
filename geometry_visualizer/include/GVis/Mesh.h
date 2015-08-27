#pragma once

//======Standard Libraries======
#include <vector>

//======OpenGL Related==========
#include <GL/glew.h>
#include <glm/vec3.hpp>

namespace gvis {

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
	};

	class Mesh {
	public:
		// Mesh Data
		std::vector<Vertex> Vertices_;
		std::vector<GLuint> Indices_;
		GLuint VAO_;

		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
		Mesh() = default;
		~Mesh() {}

		void Draw();

	private:
		GLuint vbo_, ebo_;
	};

} // namespace gvis