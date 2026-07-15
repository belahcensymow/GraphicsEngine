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
in vec3 FragPosView;
in vec3 NormalView;
in vec3 LightPosView;
out vec4 fragColor;
void main()
{
    float ambiantStrength = 0.2f;
    float specularStrength = 0.5f;
    vec3 objectColor = vec3(1.0f, 0.5f, 0.31f);
    vec3 lightColor = vec3(1);
    vec3 norm = normalize(NormalView);
    vec3 ambiant = ambiantStrength * lightColor * objectColor;
    vec3 lightDirection = normalize(LightPosView - FragPosView);
    vec3 diffuse = max(dot(norm, lightDirection), 0.0) * objectColor;
    vec3 reflectDirection = reflect(-lightDirection, norm);
    vec3 viewDirection = normalize(-FragPosView);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;
    fragColor = vec4((ambiant + diffuse + specular), 1.0);
}
