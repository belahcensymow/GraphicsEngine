#include "Camera.h"
#include "Mathematics.h"
#include "Object3D.h"
#include "Shared.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>

float lastX = 400, lastY = 300;
float offsetX, offsetY;
float sensitivity = 0.1f;
bool mouseFirst = true;
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (mouseFirst) {
    lastX = xpos;
    lastY = ypos;
    mouseFirst = false;
  }
  offsetX = xpos - lastX;
  offsetY = lastY - ypos;
  offsetX *= sensitivity;
  offsetY *= sensitivity;
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  if (!glfwInit())
    return -1;
  GLFWwindow *window = glfwCreateWindow(1200, 950, "OpenGL", NULL, NULL);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_BLEND_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glewInit();
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glViewport(0, 0, 1200, 950);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  std::vector<Vertex> vertices = {
      {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
      {{-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},
      {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
      {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
      {{ 0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},
      {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
      {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
      {{ 0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},
      {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
      {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
      {{-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},
      {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
      {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
      {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
      {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
      {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
      {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
      {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
      {{ 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
      {{ 0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
      {{ 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
      {{ 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
      {{ 0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
      {{ 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
      {{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},
      {{ 0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
      {{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
      {{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
      {{-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},
      {{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},
      {{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},
      {{-0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},
      {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
      {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
      {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},
      {{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},
  };
  std::vector<unsigned int> indices = {
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
      18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
  std::vector<VertexLayout> verticesLayout = {
      {3, GL_FLOAT},
      {3, GL_FLOAT},
      {2, GL_FLOAT},
  };
  Shader shader("texture.glsl");
  Shader lightShader("light.glsl");
  Mesh cubeMesh(vertices, verticesLayout, indices);
  Model cubeModel(cubeMesh);
  Model backpackModel("resources/backpack/backpack.obj");
  Object3D backpack(backpackModel, shader);
  Object3D cube(cubeModel, shader);
  Object3D lightSource(cubeModel, lightShader);
  lightSource.SRT({0.2f, 0.2f, 0.2f}, {40.0f, 30.0f, 0.0f}, {1.2f, 1.0f, 2.0f});
  shader.setUniform3fv("lightPos", lightSource.Position.data());
  Texture boxTexture("resources/container2.png", "material.Diffuse");
  Texture boxTextureSpecular("resources/container2_specular.png", "material.Specular");
  shader.setFloat("material.Shininess", 64.0f);
  shader.setUniform3fv("dirLight.Ambient", 0.2f, 0.2f, 0.2f);
  shader.setUniform3fv("dirLight.Diffuse", 0.5f, 0.5f, 0.5f);
  shader.setUniform3fv("dirLight.Specular", 1.0f, 1.0f, 1.0f);
  shader.setUniform3fv("dirLight.Direction", -0.2f, -1.0f, -0.3f);
  std::array<float, 3> pointLightsPositions[] = {{0.7f, 0.2f, 2.0f}, {2.3f, -3.3f, -4.0f}, {-4.0f, 2.0f, -12.0f}, {0.0f, 0.0f, -3.0f}};
  shader.setUniform3fv("pointLights[0].Position", pointLightsPositions[0].data());
  shader.setUniform3fv("pointLights[0].Ambient", 0.05f, 0.05f, 0.05f);
  shader.setUniform3fv("pointLights[0].Diffuse", 0.8f, 0.8f, 0.8f);
  shader.setUniform3fv("pointLights[0].Specular", 1.0f, 1.0f, 1.0f);
  shader.setFloat("pointLights[0].Constant", 1.0f);
  shader.setFloat("pointLights[0].Linear", 0.09f);
  shader.setFloat("pointLights[0].Quadratic", 0.032f);
  shader.setUniform3fv("pointLights[1].Position", pointLightsPositions[1].data());
  shader.setUniform3fv("pointLights[1].Ambient", 0.05f, 0.05f, 0.05f);
  shader.setUniform3fv("pointLights[1].Diffuse", 0.8f, 0.8f, 0.8f);
  shader.setUniform3fv("pointLights[1].Specular", 1.0f, 1.0f, 1.0f);
  shader.setFloat("pointLights[1].Constant", 1.0f);
  shader.setFloat("pointLights[1].Linear", 0.09f);
  shader.setFloat("pointLights[1].Quadratic", 0.032f);
  shader.setUniform3fv("pointLights[2].Position", pointLightsPositions[2].data());
  shader.setUniform3fv("pointLights[2].Ambient", 0.05f, 0.05f, 0.05f);
  shader.setUniform3fv("pointLights[2].Diffuse", 0.8f, 0.8f, 0.8f);
  shader.setUniform3fv("pointLights[2].Specular", 1.0f, 1.0f, 1.0f);
  shader.setFloat("pointLights[2].Constant", 1.0f);
  shader.setFloat("pointLights[2].Linear", 0.09f);
  shader.setFloat("pointLights[2].Quadratic", 0.032f);
  shader.setUniform3fv("pointLights[3].Position", pointLightsPositions[3].data());
  shader.setUniform3fv("pointLights[3].Ambient", 0.05f, 0.05f, 0.05f);
  shader.setUniform3fv("pointLights[3].Diffuse", 0.8f, 0.8f, 0.8f);
  shader.setUniform3fv("pointLights[3].Specular", 1.0f, 1.0f, 1.0f);
  shader.setFloat("pointLights[3].Constant", 1.0f);
  shader.setFloat("pointLights[3].Linear", 0.09f);
  shader.setFloat("pointLights[3].Quadratic", 0.032f);
  shader.setUniform3fv("spotLight.Ambient", 0.0f, 0.0f, 0.0f);
  shader.setUniform3fv("spotLight.Diffuse", 1.0f, 1.0f, 1.0f);
  shader.setUniform3fv("spotLight.Specular", 1.0f, 1.0f, 1.0f);
  shader.setFloat("spotLight.Constant", 1.0f);
  shader.setFloat("spotLight.Linear", 0.09f);
  shader.setFloat("spotLight.Quadratic", 0.032f);
  shader.setFloat("spotLight.CutOff", std::cosf(radians(12.5f)));
  shader.setFloat("spotLight.OuterCutOff", std::cosf(radians(15.0f)));
  Camera camera;
  float currentFrame = glfwGetTime();
  float lastFrame = 0;
  float deltaTime = 0;
  glfwSetCursorPosCallback(window, mouse_callback);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  float cubePositions[][3] = {
      {0.0f, 0.0f, 0.0f},     {2.0f, 5.0f, -15.0f}, {-1.5f, -2.2f, -2.5f},
      {-3.8f, -2.0f, -12.3f}, {2.4f, -0.4f, -3.5f}, {-1.7f, 3.0f, -7.5f},
      {1.3f, -2.0f, -2.5f},   {1.5f, 2.0f, -2.5f},  {1.5f, 0.2f, -1.5f},
      {-1.3f, 1.0f, -1.5f},
  };
  std::cout << "Entering loop" << std::endl;
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    camera.Rotation[1] = offsetX;
    camera.Rotation[0] = offsetY;
    camera.getInput(shader, window, deltaTime);
    camera.getInput(lightShader, window, deltaTime);
    for (auto position : cubePositions) {
      cube.translate(position[0], position[1], position[2], ABSOLUTE);
      cube.rotate(20 * position[0], 20 * position[1], 20 * position[2], ABSOLUTE);
      cube.setTexture(boxTexture, 2);
      cube.setTexture(boxTextureSpecular, 3);
      cube.draw();
    }
    // cube.rotate(glfwGetTime()*10, glfwGetTime()*15, 0, ABSOLUTE);
    backpack.draw();
    lightSource.draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
