#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:

	// Reference for Vertex Array Object.
	GLuint ID;

	// Constructor that generates a new reference (ID).
	VAO();

	// Links a Vertex Buffer Object to a Vertex Array Object using a predetermined layout.
	void LinkVBO(VBO VBO, GLuint layout);

	// Utility functions.
	void Bind();
	void Unbind();
	void Delete();

};

#endif
