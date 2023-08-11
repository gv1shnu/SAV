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

#include <iomanip> // Include this for std::setprecision

std::vector<float> randomArrayGenerator(int length, float minRange, float maxRange)
{
	// Create a random number generator
	std::random_device rd;   // Obtain a random seed from hardware
	std::mt19937 eng(rd());  // Seed the generator

	// Define the range of random integers for generating 1 decimal point
	int intMin = static_cast<int>(minRange * 10);
	int intMax = static_cast<int>(maxRange * 10);
	std::uniform_int_distribution<int> intDistr(intMin, intMax);

	// Create the vector and populate it with random floats
	std::vector<float> randomArray;
	for (int i = 0; i < length; ++i) {
		int intValue = intDistr(eng);
		randomArray.push_back(static_cast<float>(intValue) / 10.0f);
	}

	// Print the generated vector
	std::cout << "Random vector of length " << length << ":\n";
	for (float num : randomArray) {
		std::cout << std::fixed << std::setprecision(1) << num << " ";
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
	std::cout << std::endl << "-- Enter N (1 to 39): ";
	unsigned int numShapes;
	std::cin >> numShapes;
	std::cout << std::endl;

	int windowWidth = 800, windowHeight = 600;
	GLFWwindow* window = InitWindow(windowWidth, windowHeight, "SAV");
	if (!window)
		return -1;
	
	{
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
		VertexBuffer vb(nullptr, 1000);

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

		assert(numShapes < 39);
		std::vector<float> barHeights = randomArrayGenerator(numShapes, 50.0f, 580.0f);

		unsigned int barMargin = 20.0f;

		std::vector<glm::vec3> translations(numShapes);
		std::vector<glm::vec4> colorUniforms(numShapes);

		for (unsigned int i = 0; i < numShapes; i++) {
			translations[i] = glm::vec3(trvec.x + barMargin, trvec.y, 0);
			trvec = translations[i];

			colorUniforms[i] = generateRandomVec4(0.0f, 1.0f);
		}
		
		unsigned int barWidth = 10.0f;
		unsigned startX = 10.0f;
		unsigned startY = 10.0f;

		// Game Loop
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);			

			// rendering commands here
			renderer.clear(); 

			for (unsigned int i = 0; i < numShapes; i++)
			{
				// Vertex data for bar
				float vertices[] = {
					// bar i 
					startX, startY, // Vertex 0
					startX + barWidth, startY, // Vertex 1
					startX + barWidth, barHeights[i], // Vertex 2
					startX, barHeights[i] // Vertex 3
				};
				vb.bind();
				vb.setBufferSubData(vertices, numVertices);

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

