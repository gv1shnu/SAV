#include <random>
#include <vector>
#include "Application.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
	GLFWwindow* window = InitWindow(800, 600, "SAV");
	if (!window)
		return -1;
	
	{
		// Vertex data for rectangle
		float vertices[] = {
			// square 1 (left side)
			100.0f, 100.0f, // Vertex 0
			200.0f, 100.0f, // Vertex 1
			200.0f, 200.0f, // Vertex 2
			100.0f, 200.0f, // Vertex 3
		};
		// Number of units per vertex
		unsigned int coords = 2;
		unsigned int numVertices = 8;
		// Index data for rectangle
		unsigned int indices[] = {
			// square 1
			0, 1, 2,
			2, 3, 0
		};
		unsigned int numIndices = 6;

		// projection matrix
		glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		// view matrix
		glm::mat4 ident = glm::mat4(1.0f);
		glm::vec3 trvec = glm::vec3(0, 0, 0);
		glm::mat4 view = glm::translate(ident, trvec);

		// Creating vertex arrays
		VertexArray va;

		// Creating and binding vertex buffers
		VertexBuffer vb(vertices, numVertices*sizeof(float));

		// adding buffers and its layout to the vertex array
		VertexBufferLayout layout;
		layout.pushFloat(coords);
		va.addBuffer(vb, layout);

		// Creating and binding element buffer
		IndexBuffer ib(indices, numIndices);

		// Creating shader from source
		Shader ourShader("shaders/vertex_shader.vert", "shaders/fragment_shader.frag");
		
		// creating renderer
		Renderer renderer;

		glm::vec3 translationA(200, 200, 0);
		glm::vec3 translationB(400, 200, 0);

		// Game Loop
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);

			// rendering commands here
			renderer.clear();

			// square-1
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
				glm::mat4 mvp = proj * view * model;
				ourShader.SetUniform4f("u_Color", 1.0f, 0.5f, 0.2f, 1.0f);
				ourShader.SetUniformMat4f("u_MVP", mvp);

				renderer.draw(va, ib, ourShader);
			}

			// square-2
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
				glm::mat4 mvp = proj * view * model;
				ourShader.SetUniform4f("u_Color", 0.2f, 0.5f, 1.0f, 1.0f);
				ourShader.SetUniformMat4f("u_MVP", mvp);

				renderer.draw(va, ib, ourShader);
			}

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

