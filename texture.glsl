#Vertex Shader
#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;
out vec3 FragPosView;
out vec3 NormalView;
out vec3 LightPosView;
out vec2 TexCoords;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 lightPos;
void main()
{
    FragPosView = vec3(View * Model * vec4(aPos, 1.0f));
    gl_Position = Projection * vec4(FragPosView, 1.0f);
    NormalView = mat3(transpose(inverse(View * Model))) * aNormal;
    LightPosView = vec3(View * vec4(lightPos, 1.0f));
    TexCoords = aTexCoord;
}

#Fragment Shader
#version 430 core
struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Material material;
uniform Light light;
in vec3 FragPosView;
in vec3 NormalView;
in vec3 LightPosView;
in vec2 TexCoords;
out vec4 fragColor;
void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    vec3 norm = normalize(NormalView);
    vec3 lightDirection = normalize(LightPosView - FragPosView);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    vec3 viewDirection = normalize(-FragPosView);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    fragColor = vec4((ambient + diffuse + specular), 1.0);
}
