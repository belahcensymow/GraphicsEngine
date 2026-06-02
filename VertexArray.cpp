#include "VertexArray.h"
#include "Shared.h"

      VertexArray::VertexArray(VertexBuffer vbo, ElementArray ebo)
      {
          glGenVertexArrays(1, &vao);
          bind();
          vbo.bind();
          ebo.bind();
          unbind();
          vbo.unbind();
          ebo.unbind();
      }
      void VertexArray::bind()
      {
          glBindVertexArray(vao);

      }
      void VertexArray::unbind()
      {
          glBindVertexArray(0);
      }
