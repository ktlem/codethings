#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
public:
	
	// Reference for Element Buffer Object
	GLuint ID;

	// Constructor for Element Buffer Object.
	EBO(GLuint* indices, GLsizeiptr size);

	// Utility functions.
	void Bind();
	void Unbind();
	void Delete();

};

#endif
