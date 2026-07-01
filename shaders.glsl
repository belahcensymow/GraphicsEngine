#Vertex Shader
#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
out vec3 aColors;
out vec2 TexCoord;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0f);
    aColors = aColor;
    TexCoord = aTexCoord;
}

#Fragment Shader
#version 430 core
in vec3 aColors;
in vec2 TexCoord;
out vec4 fragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // FragColor = vec4(1 - 0.176, 1 - 0.408, 1 - 0.769, 1.0);
    // fragColor = vec4(aColors, 1.0f);
    fragColor = mix(
            texture(texture1, TexCoord),
            texture(texture2, TexCoord),
            0.5f
        );
    // fragColor = texture(texture2, TexCoord) * vec4(aColors, 1.0f);
}
