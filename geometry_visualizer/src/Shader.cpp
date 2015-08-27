//======GVis Libraries==========
#include <GVis/Shader.h>

//======Standard Libraries======
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//======OpenGL Related==========
#include <GL/glew.h>

namespace gvis {

	// Constructor from shader files
	Shader::Shader(const GLchar* vs_path, const GLchar* fs_path, const GLchar* gs_path /*= nullptr*/ ) {
		// Shaders
		GLuint vertex_shader, fragment_shader, geometry_shader;

		// Read and compile vertex shader
		const GLchar* vs_source = readShaderSource(vs_path);
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vs_source, NULL);
		glCompileShader(vertex_shader);
		checkError(vertex_shader, "VERTEX");

		// Read and compile fragment shader
		const GLchar* fs_source = readShaderSource(fs_path);
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fs_source, NULL);
		glCompileShader(fragment_shader);
		checkError(fragment_shader, "FRAGMENT");

		// If gs_path is provided, read and compile geometry shader
		if (gs_path != nullptr) {
			const GLchar* gs_source = readShaderSource(gs_path);
			geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry_shader, 1, &gs_source, NULL);
			glCompileShader(geometry_shader);
			checkError(geometry_shader, "GEOMETRY");
		}

		// Attach shaders to program and link
		this->Program_ = glCreateProgram();
		glAttachShader(this->Program_, vertex_shader);
		glAttachShader(this->Program_, fragment_shader);
		if (gs_path != nullptr)
			glAttachShader(this->Program_, geometry_shader);
		glLinkProgram(this->Program_);

		// Delete shaders
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		if (gs_path != nullptr)
			glDeleteShader(geometry_shader);
	}


	// Use shader provided by file,
	// you should call UseProgram() after calling this one
	void Shader::UseShader(const GLchar* path, std::string type) {
		GLuint shader;
		if (type == "VERTEX") {
			const GLchar* shader_source = readShaderSource(path);
			shader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(shader, 1, &shader_source, NULL);
			glCompileShader(shader);
			checkError(Program_, "VERTEX");
			glAttachShader(this->Program_, shader);
		} else if (type == "FRAGMENT") {
			const GLchar* shader_source = readShaderSource(path);
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(shader, 1, &shader_source, NULL);
		} else if (type == "GEOMETRY") {
			const GLchar* shader_source = readShaderSource(path);
			shader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(shader, 1, &shader_source, NULL);
		} else {
			std::cerr << "ERROR::SHADER::UseShader: Please provide the right shader type." << std::endl;
		}
		glLinkProgram(this->Program_);
		checkError(this->Program_, "PROGRAM");
		glDeleteShader(shader);
	}


	// Read shader source file
	const char* Shader::readShaderSource(const GLchar* path) {
		std::ifstream file(path);
		if (!file) {
			std::cerr << "ERROR::SHADER::readShaderSource: " << path << " FAILED." << std::endl;
			exit(EXIT_FAILURE);
		}
		std::stringstream buffer;
		buffer<< file.rdbuf();
		file.close();
		std::string shader_source = buffer.str();
		return shader_source.c_str();
	}


	// Check compile and link error
	void Shader::checkError(GLuint obj, std::string type) {
		GLint success;
		GLchar info_log[512];
		if (type != "PROGRAM") {
			glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(obj, 512, NULL, info_log);
				std::cerr << "ERROR::SHADER::SHADER_COMPILE_ERROR of type: " << type << std::endl
					<< info_log << std::endl;
			}
		} else if (type == "PROGRAM") {
			glGetProgramiv(obj, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(obj, 512, NULL, info_log);
				std::cerr << "ERROR::SHADER::PROGRAM_LINK_ERROR" << std::endl;
			}
		} else {
			std::cerr << "ERROR::SHADER::checkError: Please provide the right type." << std::endl;
		}
	}

} // namespace gvis