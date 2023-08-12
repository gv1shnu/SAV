#pragma once

#include <glad/glad.h> // GLAD before GLFW
#include <GLFW\glfw3.h>

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "vendor/stb_image/stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

// context window dimensions
int windowWidth = 800, windowHeight = 600;

// projection matrix
glm::mat4 proj = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f);

// view matrix
glm::mat4 ident = glm::mat4(1.0f);
glm::vec3 trvec = glm::vec3(0, 0, 0);
glm::mat4 view = glm::translate(ident, trvec);

// bar dimensions
float barMargin = 20.0f, barWidth = 10.0f, startX = 10.0f, startY = 10.0f;
// Number of units per vertex
uint32_t coords = 2;
uint32_t numVertices = 8;
// Index data for bar
uint32_t indices[] = {
    // square 1
    0, 1, 2,
    2, 3, 0
};
uint32_t numIndices = 6;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* InitWindow(int width, int height, const char* windowIcon, const char* windowTitle)
{
    std::cout << "Hello world!" << std::endl;

    // Initiating GLFW
    if (glfwInit() != GLFW_TRUE)
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWimage images[1];
    images[0].pixels = stbi_load(windowIcon, &images[0].width, &images[0].height, nullptr, 4);

    // GLFW context window creation
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!images[0].pixels) {
        // Handle image loading error
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }

    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(images[0].pixels);

    // Loading GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << std::endl;

    return window;
}

void render(uint32_t& numShapes, std::vector<float>& barHeights, VertexArray& va, VertexBuffer& vb, IndexBuffer& ib, Shader& sh, std::vector<glm::vec4>& colorUniforms, std::vector<glm::vec3>& translations, Renderer& re)
{
    // rendering commands here
    re.clear();

    for (uint32_t i = 0; i < numShapes; i++)
    {
        // Vertex data for bar
        float vertices[] = {
            // bar i 
            startX, startY, // bottom left
            startX + barWidth, startY, // bottom right
            startX + barWidth, barHeights[i], // top right
            startX, barHeights[i] // top left
        };
        vb.bind();
        vb.setBufferSubData(vertices, numVertices);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), translations[i]);
        glm::mat4 mvp = proj * view * model;
        sh.SetUniform4f("u_Color", colorUniforms[i].x, colorUniforms[i].y, colorUniforms[i].z, colorUniforms[i].w);
        sh.SetUniformMat4f("u_MVP", mvp);

        re.draw(va, ib, sh);
    }
}