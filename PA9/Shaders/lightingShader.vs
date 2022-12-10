#version 330 core

layout(location = 0) in vec3 aPos;

//uniform mat4 scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
	//mat4 model1 = scale * model;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);


}