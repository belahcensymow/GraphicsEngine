#include "Shared.h"
#include "VertexBuffer.h"
#include "ElementArray.h"

class VertexArray
{
  public:
      unsigned int vao;
      VertexArray(VertexBuffer vbo, ElementArray ebo);
      void bind();
      void unbind();
};
