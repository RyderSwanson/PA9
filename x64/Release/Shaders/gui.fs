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
uniform float batteryLevel;

const float width = 0.01;
const float height = .15;
const vec3 batteryColor = vec3(1,1,0.8);


void main() {
	if (TexCoords.y > height * batteryLevel || TexCoords.x > width) {
		discard;
	}

	FragColor = vec4(batteryColor, 1.0);
};
