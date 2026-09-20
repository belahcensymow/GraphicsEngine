#Vertex Shader
#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;
out vec3 FragPosView;
out vec3 NormalView;
out vec3 LightPosView;
out vec2 TexCoords;
out vec3 Normal;
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
    Normal = aNormal;
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
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct SpotLight
{
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform mat4 View;
in vec3 FragPosView;
in vec3 NormalView;
in vec3 LightPosView;
in vec2 TexCoords;
in vec3 Normal;
out vec4 fragColor;

vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos,vec3 viewDir);

void main()
{
    vec3 norm = normalize(NormalView);
    vec3 viewDir = normalize(-FragPosView);

    vec3 result = CalculateDirectionalLight(dirLight, norm, viewDir);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalculatePointLight(pointLights[i], norm, FragPosView, viewDir);

    result += CalculateSpotLight(spotLight, norm, FragPosView, viewDir);
    fragColor = vec4(result, 1.0);
}

vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.direction);
    vec3 reflectDir = reflect(lightDir, normal);

    float diff = max(dot(-lightDir, normal), 0.0);
    float spec = pow(max(dot(-viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse , TexCoords));
    vec3 diffuse  = light.diffuse  * vec3(texture(material.diffuse , TexCoords)) * diff;
    vec3 specular = light.specular * vec3(texture(material.specular, TexCoords)) * spec;

    return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightPosView = vec3(View * vec4(light.position, 1.0));
    vec3 lightDir = normalize(fragPos - lightPosView);
    vec3 reflectDir = reflect(lightDir, normal);

    float diff = max(dot(-lightDir, normal) ,0.0);
    float spec = pow(max(dot(-viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(fragPos - lightPosView);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    vec3 ambiant  = light.ambient  * vec3(texture(material.diffuse , TexCoords));
    vec3 diffuse  = light.diffuse  * vec3(texture(material.diffuse , TexCoords)) * diff;
    vec3 specular = light.specular * vec3(texture(material.specular, TexCoords)) * spec;

    return (ambiant + diffuse + specular) * attenuation;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos,vec3 viewDir)
{
    vec3 lightDir = normalize(fragPos);

    float diff = max(dot(-lightDir, normal) ,0.0);
    float spec = pow(max(dot( -viewDir, normal), 0.0), material.shininess);

    float distance = length(fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    float theta = dot(lightDir, vec3(0.0, 0.0, -1.0));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * vec3(texture(material.diffuse, TexCoords)) * spec;
    vec3 diffuse  = light.diffuse  * vec3(texture(material.diffuse, TexCoords)) * diff;

    return (ambient + specular + diffuse) * attenuation * intensity;
}
