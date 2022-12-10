#version 330 core

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_normal1;
	float shininess;
};


struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NUMBER_POINT_LIGHTS 1

struct FlashLight {
	vec3 direction; 
	vec3 position;	

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;
};

out vec4 FragColor;

//in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NUMBER_POINT_LIGHTS];
uniform FlashLight flashLight;

uniform vec3 viewPos;


//prototypes
vec3 CalcDirLight(DirLight light);
vec3 CalcPointLight(PointLight light);
vec3 CalcFlashLight(FlashLight light);

void main() {
	vec3 result;
	//result = CalcDirLight(dirLight);

	for (int i = 0; i < 1; i++) {
		result += CalcPointLight(pointLights[i]);
	}

	result += CalcFlashLight(flashLight);

	FragColor = vec4(result, 1.0f);
	//FragColor = vec4(vec3(texture(material.texture_normal1, TexCoords)), 1.0);	
};

vec3 CalcDirLight(DirLight light) {
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 norm = normalize(Normal);
	//norm *= normalize(vec3(texture(material.texture_normal1, TexCoords)));

	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * diff * vec3(texture(material.texture_specular1, TexCoords));

	return (ambient + diffuse + specular);
	//FragColor = vec4(vec3(texture(material.texture_normal1, TexCoords)), 1.0);
};

vec3 CalcPointLight(PointLight light) {
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 norm = normalize(Normal);
	//norm *= normalize(vec3(texture(material.texture_normal1, TexCoords)));

	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * diff * vec3(texture(material.texture_specular1, TexCoords));

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
};

vec3 CalcFlashLight(FlashLight light) {
	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

		
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
	//vec3 ambient = light.ambient * vec3(1,1,1);
	vec3 norm = normalize(Normal);
	//norm *= vec3(texture(material.texture_normal1, TexCoords));
			
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
	//vec3 diffuse = light.diffuse * diff * vec3(1,1,1);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * diff * vec3(texture(material.texture_specular1, TexCoords));

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	//ambient *= attenuation;
		

	diffuse *= attenuation;
	specular *= attenuation;
	diffuse *= intensity;
	specular *= intensity;

		
	return (ambient + diffuse + specular);
	//FragColor = vec4(vec3(texture(material.texture_normal1, TexCoords)), 1.0);
};