#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Source code for Vertex Shader
const char* vertexShaderSource = "#version 330 \n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Source code for Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



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

	// Vertex coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};


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

	// Create Vertex Shader object from source code and compile it into machine language.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create Fragment Shader object from source code and compile it into machine language.
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create Shader Program object and attach Vertex and Fragment Shaders to it.
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Build Shader Program
	glLinkProgram(shaderProgram);

	// Delete Shader objects now that the Shader Program has their properties.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Create reference containers for Vertex Array Object (VAO) and Vertex Buffer Object (VBO).
	GLuint VAO, VBO;

	// Generate 1 VAO object and 1 VBO object. 
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Set the created VAO object as the current Vertex Array Object in use. 
	glBindVertexArray(VAO);

	// Set the created VBO object as the current Array Buffer in use.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices to the Array Buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure Vertex Attribute so that OpenGL can read the Array Buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable Vertex Attribute so that OpenGL can use it.
	glEnableVertexAttribArray(0);

	// Set both VBO and VAO to 0 so they aren't accidentally modified.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



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
		glUseProgram(shaderProgram);
		// Tell OpenGL which Vertex Array to use
		glBindVertexArray(VAO);

		// Draw graphics
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Event handling within the window.
		glfwPollEvents();
	}

	// Delete all graphics objects when exiting the program.
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	// Delete window when exiting the program.
	glfwDestroyWindow(window);

	// Terminate GLFW when exiting the program.
	glfwTerminate();

	return 0;
}