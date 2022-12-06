#version 330 core

out vec4 FragColor;

//in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float test;

void main()
{
	FragColor = mix(texture(texture2, TexCoord), texture(texture1, TexCoord), test);
};