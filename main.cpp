#include "Shared.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Object3D.h"
#include "Mathematics.h"

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
    Object3D cube(vertices, verticesLayout, indices, "shaders.glsl");
    Texture texture1("container.jpg", "texture1", 0);
    Texture texture2("awesomeface.png", "texture2", 1);
    cube.setTexture(texture1);
    cube.setTexture(texture2);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        cube.SRT(0.5, 0.5, 0.5, glfwGetTime()*10, glfwGetTime()*10, 0, 0.25, 0.25, 0.25);
        cube.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
