#Vertex Shader
#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
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
    sampler2D Diffuse;
    sampler2D Specular;
    float Shininess;
};
struct Light
{
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};
struct DirLight
{
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};
struct PointLight
{
    vec3 Position;

    float Constant;
    float Linear;
    float Quadratic;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};
struct SpotLight
{
    float CutOff;
    float OuterCutOff;

    float Constant;
    float Linear;
    float Quadratic;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
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
    // fragColor = vec4(CalculateDirectionalLight(dirLight, norm, viewDir), 1.0);
}

vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.Direction);
    vec3 reflectDir = reflect(lightDir, normal);

    float diff = max(dot(-lightDir, normal), 0.0);
    float spec = pow(max(dot(-viewDir, reflectDir), 0.0), material.Shininess);

    vec3 ambient  = light.Ambient  * vec3(texture(material.Diffuse , TexCoords));
    vec3 diffuse  = light.Diffuse  * vec3(texture(material.Diffuse , TexCoords)) * diff;
    vec3 specular = light.Specular * vec3(texture(material.Specular, TexCoords)) * spec;

    return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightPosView = vec3(View * vec4(light.Position, 1.0));
    vec3 lightDir = normalize(fragPos - lightPosView);
    vec3 reflectDir = reflect(lightDir, normal);

    float diff = max(dot(-lightDir, normal) ,0.0);
    float spec = pow(max(dot(-viewDir, reflectDir), 0.0), material.Shininess);

    float distance = length(fragPos - lightPosView);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * distance * distance);

    vec3 ambiant  = light.Ambient  * vec3(texture(material.Diffuse , TexCoords));
    vec3 diffuse  = light.Diffuse  * vec3(texture(material.Diffuse , TexCoords)) * diff;
    vec3 specular = light.Specular * vec3(texture(material.Specular, TexCoords)) * spec;

    return (ambiant + diffuse + specular) * attenuation;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos,vec3 viewDir)
{
    vec3 lightDir = normalize(fragPos);

    float diff = max(dot(-lightDir, normal) ,0.0);
    float spec = pow(max(dot( -viewDir, normal), 0.0), material.Shininess);

    float distance = length(fragPos);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * distance * distance);

    float theta = dot(lightDir, vec3(0.0, 0.0, -1.0));
    float epsilon = light.CutOff - light.OuterCutOff;
    float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient  = light.Ambient  * vec3(texture(material.Diffuse, TexCoords));
    vec3 specular = light.Specular * vec3(texture(material.Diffuse, TexCoords)) * spec;
    vec3 diffuse  = light.Diffuse  * vec3(texture(material.Diffuse, TexCoords)) * diff;

    return (ambient + specular + diffuse) * attenuation * intensity;
}
