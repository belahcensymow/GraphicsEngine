#include "Shared.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Mathematics.h"
#include "Object3D.h"
#include "Camera.h"

float lastX = 400, lastY = 300;
float offsetX, offsetY;
float sensitivity = 0.1f;
bool mouseFirst = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(mouseFirst)
    {
        lastX = xpos;
        lastY = ypos;
        mouseFirst = false;
    }
    offsetX = xpos - lastX;
    offsetY = lastY - ypos;
    offsetX *= sensitivity;
    offsetY *= sensitivity;
}

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
    glEnable(GL_DEPTH_TEST);
    glewInit();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f, -1.0f},  {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f, -1.0f},  {1.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f,  1.0f},  {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f,  1.0f},  {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f,  1.0f},  {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f,  1.0f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f,  1.0f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  0.0f,  1.0f},  {0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {-1.0f, 0.0f,  0.0f},  {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {-1.0f, 0.0f,  0.0f},  {1.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {-1.0f, 0.0f,  0.0f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {-1.0f, 0.0f,  0.0f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {-1.0f, 0.0f,  0.0f},  {0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {-1.0f, 0.0f,  0.0f},  {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f, -1.0f,  0.0f},  {1.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f, -1.0f,  0.0f},  {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  1.0f,  0.0f},  {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  1.0f,  0.0f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.5f, 0.31f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}}
    };
    std::vector<unsigned int> indices = {
        0 , 1 , 2 ,  3 , 4 , 5 ,
        6 , 7 , 8 ,  9 , 10, 11,
        12, 13, 14,  15, 16, 17,
        18, 19, 20,  21, 22, 23,
        24, 25, 26,  27, 28, 29,
        30, 31, 32,  33, 34, 35
    };
    std::vector<VertexLayout> verticesLayout = {
        {3, GL_FLOAT, 0},
        {3, GL_FLOAT, 1},
        {3, GL_FLOAT, 2},
        {2, GL_FLOAT, 3},
    };
    Shader shader("texture.glsl");
    Shader lightShader("light.glsl");
    Object3D cube(vertices, verticesLayout, indices, shader);
    Object3D lightSource(vertices, verticesLayout, indices, lightShader);
    std::array<float, 16> Projection = ::Projection(45, 4.0f/3.0f, 0.1f, 100.0f);
    lightSource.SRT({0.2f,0.2f,0.2f},{40.0f,30.0f,0.0f},{1.2f,1.0f,2.0f});
    shader.setMatrix4fv("Projection", Projection.data());
    lightShader.setMatrix4fv("Projection", Projection.data());
    shader.setUniform3fv("lightPos", lightSource.Position.data());
    Texture texture1("container.jpg", "texture1", 0);
    Texture texture2("awesomeface.png", "texture2", 1);
    cube.setTexture(texture1);
    cube.setTexture(texture2);

    shader.setUniform3fv("material.ambient", 1.0f,0.5f,0.31f);
    shader.setUniform3fv("material.diffuse", 1.0f,0.5f,0.31f);
    shader.setUniform3fv("material.specular",0.5f,0.5f,0.5f);
    shader.setFloat("material.shininess", 32.0f);
    shader.setFloat("AmbiantStrength", 0.1f);
    shader.setFloat("DiffuseStrength", 1.0f);
    shader.setFloat("SpecularStrength", 1.0f);

    Camera camera;
    float currentFrame = glfwGetTime();
    float lastFrame = 0;
    float deltaTime = 0;
    glfwSetCursorPosCallback(window, mouse_callback);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        camera.Rotation[1] = offsetX;
        camera.Rotation[0] = offsetY;
        camera.getInput(shader, window, deltaTime);
        camera.getInput(lightShader, window, deltaTime);
        cube.rotate(glfwGetTime()*10, glfwGetTime()*15, 0, ABSOLUTE);
        cube.draw();
        lightSource.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
