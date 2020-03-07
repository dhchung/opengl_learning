#version 330 core

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutoff;
    float outercutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    
};

uniform Light light;
uniform Material material;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;
uniform vec3 viewPos;

void main() {


    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + 
                             light.linear * distance +
                             light.quadratic * distance * distance);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    ambient *= attenuation;

    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(-light.direction);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, TexCoords));
    diffuse *= attenuation;


    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    specular *= attenuation;


    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outercutoff;
    float intensity = clamp((theta - light.outercutoff)/epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular*= intensity;

    vec3 result;

    if(theta > light.outercutoff) {
        result = ambient + diffuse + specular;
    } else {
        result = light.ambient * vec3(texture(material.diffuse, TexCoords));
    }


    FragColor = vec4(result, 1.0);
}