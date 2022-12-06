#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	int type; //0 = point, 1 = directional, 2 = attenuated point, 3 = flashlight

	//both used in flashlight
	vec3 direction; //used in directional
	vec3 position;	//used in point lights

	//used in all
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	//attenuated
	float constant;
	float linear;
	float quadratic;

	//flashlight
	float cutOff;
	float outerCutOff;
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
	
// point light
	if (light.type == 0) {
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
	}
	//dir light
	if (light.type == 1) {
		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(-light.direction);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectionDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

		//FragColor = mix(texture(texture2, TexCoords), texture(texture1, TexCoords), test);// * vec4(result, 1.0f);
		FragColor = vec4(ambient + diffuse + specular, 1.0f);
	}
	//attenuated point Light
	if (light.type == 2) {
		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light.position - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectionDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

		float distance = length(light.position - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		//FragColor = mix(texture(texture2, TexCoords), texture(texture1, TexCoords), test);// * vec4(result, 1.0f);
		FragColor = vec4(ambient + diffuse + specular, 1.0f);
	}

	//flashlight
	if (light.type == 3) {
		vec3 lightDir = normalize(light.position - FragPos);
		float theta = dot(lightDir, normalize(-light.direction));
		float epsilon = light.cutOff - light.outerCutOff;
		float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

		
		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
		vec3 norm = normalize(Normal);
			
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectionDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

		float distance = length(light.position - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
		//ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
		diffuse *= intensity;
		specular *= intensity;

		//FragColor = mix(texture(texture2, TexCoords), texture(texture1, TexCoords), test);// * vec4(result, 1.0f);
		FragColor = vec4(ambient + diffuse + specular, 1.0f);

		
	
		
	}

	
};