#include "Camera.h"
#include "Mathematics.h"
#include "Object3D.h"
#include "Shared.h"
#include "Texture.h"
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
  glewInit();
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glViewport(0, 0, 1200, 950);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  std::vector<Vertex> vertices = {{{-0.5f, -0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, -1.0f},
                                   {0.0f, 0.0f}},
                                  {{-0.5f, 0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, -1.0f},
                                   {0.0f, 1.0f}},
                                  {{0.5f, 0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, -1.0f},
                                   {1.0f, 1.0f}},
                                  {{0.5f, 0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, -1.0f},
                                   {1.0f, 1.0f}},
                                  {{0.5f, -0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, -1.0f},
                                   {1.0f, 0.0f}},
                                  {{-0.5f, -0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, -1.0f},
                                   {0.0f, 0.0f}},
                                  {{-0.5f, -0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, 1.0f},
                                   {0.0f, 0.0f}},
                                  {{0.5f, -0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, 1.0f},
                                   {1.0f, 0.0f}},
                                  {{0.5f, 0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, 1.0f},
                                   {1.0f, 1.0f}},
                                  {{0.5f, 0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, 1.0f},
                                   {1.0f, 1.0f}},
                                  {{-0.5f, 0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, 1.0f},
                                   {0.0f, 1.0f}},
                                  {{-0.5f, -0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 0.0f, 1.0f},
                                   {0.0f, 0.0f}},
                                  {{-0.5f, 0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {-1.0f, 0.0f, 0.0f},
                                   {1.0f, 0.0f}},
                                  {{-0.5f, 0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {-1.0f, 0.0f, 0.0f},
                                   {1.0f, 1.0f}},
                                  {{-0.5f, -0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {-1.0f, 0.0f, 0.0f},
                                   {0.0f, 1.0f}},
                                  {{-0.5f, -0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {-1.0f, 0.0f, 0.0f},
                                   {0.0f, 1.0f}},
                                  {{-0.5f, -0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {-1.0f, 0.0f, 0.0f},
                                   {0.0f, 0.0f}},
                                  {{-0.5f, 0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {-1.0f, 0.0f, 0.0f},
                                   {1.0f, 0.0f}},
                                  {{0.5f, 0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {1.0f, 0.0f, 0.0f},
                                   {1.0f, 0.0f}},
                                  {{0.5f, -0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {1.0f, 0.0f, 0.0f},
                                   {0.0f, 0.0f}},
                                  {{0.5f, -0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {1.0f, 0.0f, 0.0f},
                                   {0.0f, 1.0f}},
                                  {{0.5f, -0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {1.0f, 0.0f, 0.0f},
                                   {0.0f, 1.0f}},
                                  {{0.5f, 0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {1.0f, 0.0f, 0.0f},
                                   {1.0f, 1.0f}},
                                  {{0.5f, 0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {1.0f, 0.0f, 0.0f},
                                   {1.0f, 0.0f}},
                                  {{-0.5f, -0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, -1.0f, 0.0f},
                                   {0.0f, 1.0f}},
                                  {{0.5f, -0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, -1.0f, 0.0f},
                                   {1.0f, 1.0f}},
                                  {{0.5f, -0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, -1.0f, 0.0f},
                                   {1.0f, 0.0f}},
                                  {{0.5f, -0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, -1.0f, 0.0f},
                                   {1.0f, 0.0f}},
                                  {{-0.5f, -0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, -1.0f, 0.0f},
                                   {0.0f, 0.0f}},
                                  {{-0.5f, -0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, -1.0f, 0.0f},
                                   {0.0f, 1.0f}},
                                  {{-0.5f, 0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 1.0f, 0.0f},
                                   {0.0f, 1.0f}},
                                  {{-0.5f, 0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 1.0f, 0.0f},
                                   {0.0f, 0.0f}},
                                  {{0.5f, 0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 1.0f, 0.0f},
                                   {1.0f, 0.0f}},
                                  {{0.5f, 0.5f, 0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 1.0f, 0.0f},
                                   {1.0f, 0.0f}},
                                  {{0.5f, 0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 1.0f, 0.0f},
                                   {1.0f, 1.0f}},
                                  {{-0.5f, 0.5f, -0.5f},
                                   {1.0f, 0.5f, 0.31f},
                                   {0.0f, 1.0f, 0.0f},
                                   {0.0f, 1.0f}}};
  std::vector<unsigned int> indices = {
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
      18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
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
  std::array<float, 16> Projection =
      ::Projection(45, 4.0f / 3.0f, 0.1f, 100.0f);
  lightSource.SRT({0.2f, 0.2f, 0.2f}, {40.0f, 30.0f, 0.0f}, {1.2f, 1.0f, 2.0f});
  shader.setMatrix4fv("Projection", Projection.data());
  lightShader.setMatrix4fv("Projection", Projection.data());
  shader.setUniform3fv("lightPos", lightSource.Position.data());
  Texture texture1("container.jpg", "texture1", 0);
  Texture texture2("awesomeface.png", "texture2", 1);
  Texture boxTexture("container2.png", "material.diffuse", 2);
  Texture boxTextureSpecular("container2_specular.png", "material.specular", 3);
  cube.setTexture(boxTexture);
  cube.setTexture(boxTextureSpecular);
  shader.setFloat("material.shininess", 64.0f);

  shader.setUniform3fv("dirLight.ambient", 0.2f, 0.2f, 0.2f);
  shader.setUniform3fv("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
  shader.setUniform3fv("dirLight.specular", 1.0f, 1.0f, 1.0f);
  shader.setUniform3fv("dirLight.direction", -0.2f, -1.0f, -0.3f);

  std::array<float, 3> pointLightsPositions[] = {{0.7f, 0.2f, 2.0f},
                                                 {2.3f, -3.3f, -4.0f},
                                                 {-4.0f, 2.0f, -12.0f},
                                                 {0.0f, 0.0f, -3.0f}};

  shader.setUniform3fv("pointLights[0].position", pointLightsPositions[0].data());
  shader.setUniform3fv("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
  shader.setUniform3fv("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
  shader.setUniform3fv("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
  shader.setFloat("pointLights[0].constant", 1.0f);
  shader.setFloat("pointLights[0].linear", 0.09f);
  shader.setFloat("pointLights[0].quadratic", 0.032f);
  shader.setUniform3fv("pointLights[1].position", pointLightsPositions[1].data());
  shader.setUniform3fv("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
  shader.setUniform3fv("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
  shader.setUniform3fv("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
  shader.setFloat("pointLights[1].constant", 1.0f);
  shader.setFloat("pointLights[1].linear", 0.09f);
  shader.setFloat("pointLights[1].quadratic", 0.032f);
  shader.setUniform3fv("pointLights[2].position", pointLightsPositions[2].data());
  shader.setUniform3fv("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
  shader.setUniform3fv("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
  shader.setUniform3fv("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
  shader.setFloat("pointLights[2].constant", 1.0f);
  shader.setFloat("pointLights[2].linear", 0.09f);
  shader.setFloat("pointLights[2].quadratic", 0.032f);
  shader.setUniform3fv("pointLights[3].position", pointLightsPositions[3].data());
  shader.setUniform3fv("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
  shader.setUniform3fv("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
  shader.setUniform3fv("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
  shader.setFloat("pointLights[3].constant", 1.0f);
  shader.setFloat("pointLights[3].linear", 0.09f);
  shader.setFloat("pointLights[3].quadratic", 0.032f);
  Camera camera;

  shader.setUniform3fv("spotLight.ambient", 0.0f, 0.0f, 0.0f);
  shader.setUniform3fv("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
  shader.setUniform3fv("spotLight.specular", 1.0f, 1.0f, 1.0f);
  shader.setFloat("spotLight.constant", 1.0f);
  shader.setFloat("spotLight.linear", 0.09f);
  shader.setFloat("spotLight.quadratic", 0.032f);
  shader.setFloat("spotLight.cutOff", std::cosf(radians(12.5f)));
  shader.setFloat("spotLight.outerCutOff", std::cosf(radians(15.0f)));

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
      cube.rotate(20 * position[0], 20 * position[1], 20 * position[2],
                  ABSOLUTE);
      cube.draw();
    }
    // cube.rotate(glfwGetTime()*10, glfwGetTime()*15, 0, ABSOLUTE);
    lightSource.draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
