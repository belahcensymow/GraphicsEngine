#include "VertexBuffer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>

struct VertexArray {
  float x;
  float y;
  float z;
};

class VertexBuffer {
public:
  unsigned int vbo;
  VertexBuffer(VertexArray verticies) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), &verticies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, sizeof(verticies) / sizeof(float), GL_FLOAT,
                          GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
  }
  void bind() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glVertexAttribPointer(0, sizeof() / sizeof(float), GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
  }
};
