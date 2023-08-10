#include <iostream>
#include <random>
#include <vector>
#include "Application.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"

std::vector<int> randomArrayGenerator(int keysLength)
{
	// Create a random number generator
	std::random_device rd;  // Obtain a random seed from hardware
	std::mt19937 eng(rd()); // Seed the generator
	std::uniform_int_distribution<> distr(1, 100); // Define the range of random numbers (1 to 100 in this case)

	// Create the array and populate it with random numbers
	std::vector<int> randomArray;
	for (int i = 0; i < keysLength; ++i) {
		randomArray.push_back(distr(eng));
	}

	// Print the generated array
	std::cout << "Random array of length " << keysLength << ":\n";
	for (int num : randomArray) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	return randomArray;
}

int main()
{
	std::cout << "Hello world!" << std::endl;

	// Initiating GLFW
	if (glfwInit() != GLFW_TRUE)
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// GLFW context window creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "SAV", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Loading GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	std::cout << "OpenGL Version: "<<glGetString(GL_VERSION) << std::endl;

	{
		// Vertex data for two rectangles
		float vertices[] = {
			// Rectangle 1 (left corner)
			-0.8f, -0.8f, // Vertex 0
			-0.2f, -0.8f, // Vertex 1
			-0.2f,  0.8f, // Vertex 2
			-0.8f,  0.8f, // Vertex 3

			// Rectangle 2 (right corner)
			 0.2f, -0.8f, // Vertex 0
			 0.8f, -0.8f, // Vertex 1
			 0.8f,  0.8f, // Vertex 2
			 0.2f,  0.8f  // Vertex 3
		};
		// Number of units per vertex
		unsigned int coords = 2;
		unsigned int numVertices = 16;
		// Index data for two rectangles
		unsigned int indices[] = {
			// Rectangle 1
			0, 1, 2,
			2, 3, 0,

			// Rectangle 2
			4, 5, 6,
			6, 7, 4
		};
		unsigned int numIndices = 12;

		// Creating vertex arrays
		VertexArray va1, va2;

		// Creating and binding vertex buffers
		VertexBuffer vb1(vertices, numVertices*sizeof(float));
		VertexBuffer vb2(vertices + 8, numVertices*sizeof(float));

		// adding buffers and its layout to the vertex array
		VertexBufferLayout layout;
		layout.pushFloat(coords);
		va1.addBuffer(vb1, layout);
		va2.addBuffer(vb2, layout);

		// Creating and binding element buffer
		IndexBuffer ib(indices, numIndices);

		// Creating shader from source
		Shader ourShader("shaders/vertex_shader.vert", "shaders/fragment_shader.frag");
		
		// creating renderer
		Renderer renderer;

		// Game Loop
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);

			// rendering commands here
			renderer.clear();

			ourShader.SetUniform4f("u_Color", 1.0f, 0.5f, 0.2f, 1.0f);
			renderer.draw(va1, ib, ourShader);

			ourShader.SetUniform4f("u_Color", 0.2f, 0.5f, 1.0f, 1.0f);
			renderer.draw(va2, ib, ourShader);


			// Swap front and back buffers
			glfwSwapBuffers(window);

			// Poll for and process events
			glfwPollEvents();
		}

		// Terminate the window
		glfwTerminate();
	}
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

