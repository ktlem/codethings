#include "VAO.h"

// Constructor that generates a new Vertex Array Object reference.
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a Vertex Buffer Object to a Vertex Array Object using predetermined layout.
void VAO::LinkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	// Configure Vertex Attribute so that OpenGL can read the Array Buffer
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// Enable Vertex Attribute so that OpenGL can use it.
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}