#Vertex Shader
#version 430 core
layout(location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
}

#Fragment Shader
#version 430 core
out vec4 fragColor;
void main()
{
    fragColor = vec4(1 - 0.176, 1 - 0.408, 1 - 0.769, 1.0);
}
