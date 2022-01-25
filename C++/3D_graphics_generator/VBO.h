#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
	public:

		// Reference for Vertex Buffer Object.
		GLuint ID;
		// Constructor for Vertex Buffer Object.
		VBO(GLfloat* vertices, GLsizeiptr size);

		// Utility functions.
		void Bind();
		void Unbind();
		void Delete();

};

#endif
