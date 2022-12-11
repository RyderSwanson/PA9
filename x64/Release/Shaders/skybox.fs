#version 330 core

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_normal1;
	float shininess;
};


out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform Material material;

uniform vec3 viewPos;

const float lowerLimit = 0.45;
const float upperLimit = 0.35;
const vec3 fogColor = vec3(0.03, 0.03, 0.03);

void main() {
	float factor = (TexCoords.y - lowerLimit) / (upperLimit - lowerLimit);
    factor = clamp(factor, 0.0, 1.0);

	FragColor = mix(vec4(fogColor, 1.0f), vec4(vec3(texture(material.texture_diffuse1, TexCoords)), 1.0), factor);
};
