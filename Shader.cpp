#include "Shared.h"
#include "Shader.h"
#include <fstream>
#include <iostream>

Shader::Shader(std::string shaderPath) {
  Shader::shaderPath = shaderPath;
  Shader::recompileShaders();
}

void Shader::recompileShaders() {
  std::ifstream file(this->shaderPath);
  if (!file.is_open())
  {
    std::cout << "[ ERROR ] Could not find shader source file!" << std::endl;
  }
  else
  {
      vertexString = "";
      fragmentString = "";
    ShaderType shaderType = UNDEFINED_SHADER;
    std::string line;
    while (std::getline(file, line)) {
      if (line == "#Vertex Shader") {
        shaderType = VERTEX_SHADER;
        continue;
      } else if (line == "#Fragment Shader") {
        shaderType = FRAGMENT_SHADER;
        continue;
      } else if (shaderType == VERTEX_SHADER) {
        vertexString += line + "\n";
      } else if (shaderType == FRAGMENT_SHADER) {
        fragmentString += line + "\n";
      }
    }
  }
  vertexShaderSource = vertexString.c_str();
  fragmentShaderSource = fragmentString.c_str();
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  int success;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    int length;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
    char *infoLog = new char[length];
    glGetShaderInfoLog(vertexShader, length, NULL, infoLog);
    std::cout << "[ ERROR ] Vertex Shader compilation error: " << infoLog
              << std::endl;
    delete[] infoLog;
  }
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    int length;
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
    char *infoLog = new char[length];
    glGetShaderInfoLog(fragmentShader, length, NULL, infoLog);
    std::cout << "[ ERROR ] Fragment Shader compilation error: " << infoLog
              << std::endl;
    delete[] infoLog;
  }
  program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    int length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    char *infoLog = new char[length];
    glGetProgramInfoLog(program, length, NULL, infoLog);
    std::cout << "[ ERROR ] Shader Program compilation error: " << infoLog
              << std::endl;
    delete[] infoLog;
  }
}
void Shader::bind()
{
    glUseProgram(program);
    std::cout << " <---- Vertex Shader ----> \n" << vertexString << std::endl;
    std::cout << " <---- Fragment Shader ----> \n" << fragmentString << std::endl;
}
void Shader::unbind() { glUseProgram(0); }
Shader::~Shader() {
  Shader::unbind();
  glDeleteProgram(program);
}
