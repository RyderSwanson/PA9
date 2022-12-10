#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

//in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

uniform float test;

void main() {
	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	//FragColor = mix(texture(texture2, TexCoords), texture(texture1, TexCoords), test);// * vec4(result, 1.0f);
	FragColor = vec4(ambient + diffuse + specular, 1.0f);
};