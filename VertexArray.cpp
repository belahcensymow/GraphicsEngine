#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VertexArray.h"

struct Vertex {
    float x = 0;
    float y = 0;
    float z = 0;
};

class VertexArray
{
  public:
      unsigned int id;
      VertexArray()
      {
          glGenVertexArrays(1, &id);
      }
      void bind()
      {
          glBindBuffer(GL_ARRAY_BUFFER, id);
      }
      void unbind()
      {
          glBindBuffer(GL_ARRAY_BUFFER, 0);
      }
      // void setVertexBuffer(VertexBuffer vbo)
      // {
      //     this->bind();
      //     vbo.bind();
      //     this->unbind();
      //     vbo.unbind();
      // }

};
