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

glm::vec4 generateRandomVec4(float minVal, float maxVal) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(minVal, maxVal);

	float x = dis(gen);
	float y = dis(gen);
	float z = dis(gen);
	float w = dis(gen);

	return glm::vec4(x, y, z, w);
}

int main()
{
	int windowWidth = 800, windowHeight = 600;
	GLFWwindow* window = InitWindow(windowWidth, windowHeight, "SAV");
	if (!window)
		return -1;
	
	{
		// Vertex data for rectangle
		float vertices[] = {
			// square 1 (left side)
			100.0f, 100.0f, // Vertex 0
			150.0f, 100.0f, // Vertex 1
			150.0f, 150.0f, // Vertex 2
			100.0f, 150.0f, // Vertex 3
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
		glm::mat4 proj = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f);

		// view matrix
		glm::mat4 ident = glm::mat4(1.0f);
		glm::vec3 trvec = glm::vec3(0, 0, 0);
		glm::mat4 view = glm::translate(ident, trvec);

		// Creating vertex arrays
		VertexArray va;

		// Creating and binding vertex buffers
		VertexBuffer vb(vertices, numVertices);

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

		unsigned int numShapes = 3;

		std::vector<glm::vec3> translations(numShapes);
		std::vector<glm::vec4> colorUniforms(numShapes);

		for (unsigned int i = 0; i < numShapes; i++) {
			translations[i] = glm::vec3(trvec.x + 150, trvec.y + 100, 0);
			trvec = translations[i];

			colorUniforms[i] = generateRandomVec4(0.0f, 1.0f);
		}
	
		// Game Loop
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);

			// rendering commands here
			renderer.clear();

			for (unsigned int i = 0; i < numShapes; i++)
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translations[i]);
				glm::mat4 mvp = proj * view * model;
				ourShader.SetUniform4f("u_Color", colorUniforms[i].x, colorUniforms[i].y, colorUniforms[i].z, colorUniforms[i].w);
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

