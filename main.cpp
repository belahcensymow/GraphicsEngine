#include "Shared.h"
#include "Shader.h"

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
    float verticies[] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
    };
    float verticies1[] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
    };
    float verticies2[] = {
        -0.5f, -0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
    };
    unsigned int indicies[] =
        {
            0, 1, 2,
            0, 2, 3,
        };
    unsigned int indicies1[] =
        {
            0, 1, 2,
        };
    unsigned int indicies2[] =
        {
            0, 1, 2,
        };
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "FragColor = vec4(1-0.176, 1-0.408, 1-0.769, 1.0);\n"
        "}\0";

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), &verticies, GL_STATIC_DRAW);
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(verticies[0]), NULL);
    glEnableVertexAttribArray(0);
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), &indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    unsigned int vao1, vbo1, ebo1, vao2, vbo2, ebo2;
    glGenVertexArrays(1, &vao1);
    glGenBuffers(1, &vbo1);
    glGenBuffers(1, &ebo1);
    glGenVertexArrays(1, &vao2);
    glGenBuffers(1, &vbo2);
    glGenBuffers(1, &ebo2);

    glBindVertexArray(vao1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies1), &verticies1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies1), &indicies1, GL_STATIC_DRAW);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(vao2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies2), &verticies2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies2), &indicies2, GL_STATIC_DRAW);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Shader shader("shaders.glsl");
    shader.bind();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        // glBindBuffer(GL_ARRAY_BUFFER, vbo1);
        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
