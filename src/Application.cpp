#include "Application.h"
#include <thread>
#include <chrono>
#include <string>

#define NOMINMAX // Prevent windows.h from defining max and min macros
#include <windows.h>
#include <psapi.h>

#include "Randomizer.h"
#include "SortingFunctions.h"

int main()
{
	std::cout << std::endl << "Enter N (2 to 38): ";
	uint32_t numShapes;
	std::cin >> numShapes;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << std::endl;

	assert(numShapes > 1);
	assert(numShapes < 39);

	std::cout << std::endl << "Choose sort function from below - \n";
	std::cout << "--BUBBLE SORT" << std::endl;
	std::cout << "--INSERTION SORT" << std::endl;
	std::cout << "--MERGE SORT" << std::endl;
	std::cout << "--SELECTION SORT" << std::endl;
	std::cout << "--QUICK SORT" << std::endl;
	std::cout << "--NO SORT" << std::endl;
	std::cout << std::endl << ": ";
	std::string sortF;
	std::getline(std::cin, sortF);
	std::cout << std::endl;
	 
	std::string res = "Visualizing " + sortF.substr(2);
	const char* windowTitle = res.c_str();

	GLFWwindow* window = InitWindow(windowWidth, windowHeight, "images/icon.png", windowTitle);
	if (!window)
		return -1;
	else
	{
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

		// generating random bar heights
		std::vector<float> barHeights = randomArrayGenerator(numShapes, 50.0f, 580.0f);

		std::vector<glm::vec3> translations(numShapes);
		std::vector<glm::vec4> colorUniforms(numShapes);
		// creating random uniform vector and translation vector
		for (uint32_t i = 0; i < numShapes; i++) {
			translations[i] = glm::vec3(trvec.x + barMargin, trvec.y, 0);
			trvec = translations[i];

			colorUniforms[i] = generateRandomVec4(0.0f, 1.0f);
		}

		std::vector<std::vector<float>> iterations;
		bool nosort = false;

		if (sortF == "--BUBBLE SORT")
			iterations = generate_bubble_sort(numShapes, barHeights);
		else if (sortF == "--QUICK SORT")
			iterations = generate_quick_sort(numShapes, barHeights);
		else if (sortF == "--INSERTION SORT")
			iterations = generate_insertion_sort(numShapes, barHeights);
		else if (sortF == "--SELECTION SORT")
			iterations = generate_selection_sort(numShapes, barHeights);
		else if (sortF == "--MERGE SORT")
			iterations = generate_merge_sort(numShapes, barHeights);
		else if (sortF == "--NO SORT") {
			iterations.push_back(barHeights);
			nosort = true;
		}
		else {
			std::cout << "\nInvalid command\n";
			return 0;
		}

		size_t total_iterations = iterations.size(), m_Index = 0;
		bool sorted = false;

		// Game Loop
		while (!glfwWindowShouldClose(window))
		{
			m_Index = std::min(m_Index, total_iterations-1);
			barHeights = iterations[m_Index];

			render(numShapes, barHeights, va, vb, ib, ourShader, colorUniforms, translations, renderer);

			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			m_Index++;

			if (!nosort && !sorted && m_Index == total_iterations) {
				std::cout << "\n--Sorted--" << std::endl;
				sorted = true;
			}

			// Swap front and back buffers
			glfwSwapBuffers(window);

			// Poll for and process events
			glfwPollEvents();
		}

		// Terminate the window
		glfwTerminate();
	}

	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

	SIZE_T workingSetSize = pmc.WorkingSetSize;
	SIZE_T gpuUsage = pmc.PrivateUsage;

	std::cout << "\nRAM usage: " << workingSetSize / (1024 * 1024) << " MB" << std::endl;
	std::cout << "VRAM usage: " << gpuUsage / (1024 * 1024) << " MB" << std::endl;

	return 0;
}