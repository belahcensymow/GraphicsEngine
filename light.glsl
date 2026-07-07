#Vertex Shader
#version 430 core
layout(location = 0) in vec3 aPos;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0f);
}

#Fragment Shader
#version 430 core
out vec4 fragColor;
void main()
{
    fragColor = vec4(1.0f);
}
