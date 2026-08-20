#Vertex Shader
#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
out vec3 FragPosView;
out vec3 NormalView;
out vec3 LightPosView;
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
}

#Fragment Shader
#version 430 core
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;
uniform float AmbiantStrength;
uniform float DiffuseStrength;
uniform float SpecularStrength;
in vec3 FragPosView;
in vec3 NormalView;
in vec3 LightPosView;
out vec4 fragColor;
void main()
{
    vec3 lightColor = vec3(1);
    vec3 ambient = lightColor * material.ambient * AmbiantStrength;

    vec3 norm = normalize(NormalView);
    vec3 lightDirection = normalize(LightPosView - FragPosView);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = lightColor * diff * material.diffuse * DiffuseStrength;

    vec3 viewDirection = normalize(-FragPosView);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = lightColor * spec * material.specular * SpecularStrength;
    fragColor = vec4((ambient + diffuse + specular), 1.0);
}
