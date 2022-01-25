#include "shaderClass.h"

// Parse source code text file into string.
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor for Shader Program from source code files.
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Convert source code into strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader object from source code and compile it into machine language.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create Fragment Shader object from source code and compile it into machine language.
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Create Shader Program object and attach Vertex and Fragment Shaders to it.
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Link all shaders together into Shader Program.
	glLinkProgram(ID);

	// Delete Shader objects now that the Shader Program has their properties.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Run Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// End Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}