#Vertex Shader
#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
out vec3 aColors;
out vec2 TexCoord;
void main()
{
    gl_Position = vec4(aPos, 1.0f);
    aColors = aColor;
    TexCoord = aTexCoord;
}

#Fragment Shader
#version 430 core
in vec3 aColors;
out vec4 fragColor;

in vec2 TexCoord;
uniform sampler2D sampledTexture;

void main()
{
    // FragColor = vec4(1 - 0.176, 1 - 0.408, 1 - 0.769, 1.0);
    // fragColor = vec4(aColors, 1.0f);
    fragColor = texture(sampledTexture, TexCoord);
}
