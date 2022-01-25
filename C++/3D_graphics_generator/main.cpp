#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


// Vertex coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Peak
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Lower middle
};

GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

int main()
{
	// Initialize GLFW
	glfwInit();

	// Declare OpenGL version to GLFW
	// This program uses OpenGL v3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Declare profile to GLFW
	// This program uses the CORE-profile => Only modern functions are in use.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Initialize graphics window.
	GLFWwindow* window = glfwCreateWindow(800, 800, "Graphics Test", NULL, NULL);

	// Error-checking if window init fails.
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce window into the current context.
	glfwMakeContextCurrent(window);

	// Initialize GLAD for configuring OpenGL.
	gladLoadGL();

	// Specify OpenGL viewport in the graphics window.
	// Here x goes from 0 to 800, and y goes from 0 to 800.
	glViewport(0, 0, 800, 800);

	// Create Shader-object from source code.
	Shader shaderProgram("default.vert", "default.frag");

	// Create Vertex Array Object (VAO) and bind it.
	VAO VAO1;
	VAO1.Bind();

	// Create Vertex Buffer Object (VBO) and link it to vertices.
	VBO VBO1(vertices, sizeof(vertices));

	// Create Element Buffer Object (EBO) and link it to indices.
	EBO EBO1(indices, sizeof(indices));

	// Link VBO to VAO.
	VAO1.LinkVBO(VBO1, 0);

	// Unbind all graphics objects to prevent accidental modifications.
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Set window background color.
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clear back frame buffer and assign new color to buffer.
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Set back frame buffer to front frame buffer, and vice versa.
	glfwSwapBuffers(window);

	// Loop keeps window upen until close-button is pressed.
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL what shader program to use
		shaderProgram.Activate();
		// Tell OpenGL which Vertex Array to use
		VAO1.Bind();

		// Draw graphics
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Event handling within the window.
		glfwPollEvents();
	}

	// Delete all graphics objects when exiting the program.
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	
	// Delete window when exiting the program.
	glfwDestroyWindow(window);

	// Terminate GLFW when exiting the program.
	glfwTerminate();

	return 0;
}
