#Vertex Shader
#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
out vec3 aColors;
void main()
{
    gl_Position = vec4(aPos, 1.0f);
    aColors = aColor;
}

#Fragment Shader
#version 430 core
in vec3 aColors;
out vec4 fragColor;
void main()
{
    // FragColor = vec4(1 - 0.176, 1 - 0.408, 1 - 0.769, 1.0);
    fragColor = vec4(aColors, 1.0f);
}
