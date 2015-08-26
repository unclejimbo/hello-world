#pragma once

//======Standard Libraries======
#include <string>

//======OpenGL Related==========
#include <GL/glew.h>

namespace gvis {

	class Shader {
	public:
		GLuint Program;

		Shader() = default;
		Shader(const GLchar* vs_path, const GLchar* fs_path, const GLchar* gs_paht = nullptr);
		~Shader() {}

		void UseProgram();
		void UseShader(const GLchar* path, std::string type);

	private:
		const char* readShaderSource(const GLchar* path);
		void checkError(GLuint obj, std::string type);
	};

} // namespace gvis
