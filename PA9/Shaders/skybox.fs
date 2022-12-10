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


void main() {


	FragColor = vec4(vec3(texture(material.texture_diffuse1, TexCoords)), 1.0);
};
