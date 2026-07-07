#Vertex Shader
#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;
out vec3 aColors;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 lightPos;
void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0f);
    FragPos = vec3(Model * vec4(aPos, 1.0f));
    aColors = aColor;
    TexCoord = aTexCoord;
    Normal = mat3(Model) * aNormal;
    LightPos = lightPos;
}

#Fragment Shader
#version 430 core
in vec3 aColors;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
out vec4 fragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    float ambiantStrength = 0.2f;
    vec3 objectColor = vec3(1.0f, 0.5f, 0.31f);
    vec3 lightColor = vec3(1);
    vec3 ambiant = ambiantStrength * lightColor * objectColor;
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(LightPos - FragPos);
    vec3 diffuse = max(dot(norm, lightDirection), 0.0) * objectColor;
    fragColor = vec4((ambiant + diffuse), 1);
    // FragColor = vec4(1 - 0.176, 1 - 0.408, 1 - 0.769, 1.0);
    // fragColor = vec4(aColors, 1.0f);
    // fragColor = mix(
    //         texture(texture1, TexCoord),
    //         texture(texture2, TexCoord),
    //         0.5f
    //     );
    // fragColor = texture(texture2, TexCoord) * vec4(aColors, 1.0f);
}
