#include "Shared.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include <GL/gl.h>
#include <vector>

// #include <iostream>

int main()
{
    if(!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3
    };

    std::vector<Vertex> vertices = {
        {{ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}
    };
    std::vector<VertexLayout> verticesLayout = {
        {3, GL_FLOAT, 0},
        {3, GL_FLOAT, 1},
        {2, GL_FLOAT, 2},
    };

    VertexBuffer vbo(vertices, verticesLayout);
    ElementArray ebo(indices);
    VertexArray vao(vbo, ebo);
    Shader shader("shaders.glsl");
    vao.bind();
    shader.bind();

    Texture texture("container.jpg");
    texture.bind();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
