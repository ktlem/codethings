#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		// Reference for Shader Program
		GLuint ID;

		// Constructor for Shader Program from source code files.
		Shader(const char* vertexFile, const char* fragmentFile);

		// Run Shader Program
		void Activate();

		// End Shader Program
		void Delete();

};

#endif