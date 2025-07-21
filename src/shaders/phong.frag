#version 330 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
  vec3 position;
  vec3 color;
};

#define MAX_LIGHTS 4
uniform Light lights[MAX_LIGHTS];
uniform int lightCount;

uniform Material material;

uniform vec3 viewPos;
uniform vec3 objectColor;

uniform sampler2D baseTexture;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main()
{
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 result = vec3(0.0);

  for (int i = 0; i < lightCount; ++i) {
    // Ambient
    vec3 ambient = material.ambient * lights[i].color;

    // Diffuse
    vec3 lightDir = normalize(lights[i].position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.diffuse * diff * lights[i].color;

    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * lights[i].color;

    result += (ambient + diffuse + specular);
  }

  result *= objectColor;
  result *= texture(baseTexture, TexCoord).rgb;
  FragColor = vec4(result, 1.0);
}
