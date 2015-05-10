#version 330 core

uniform mat4 camera;
uniform mat4 projection;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
 
out vec4 color;

void main()
{
	color = in_color;
	gl_Position = projection * camera * vec4(in_position, 1.0);//w is 1.0
	//fist multiply by camera then projection
}