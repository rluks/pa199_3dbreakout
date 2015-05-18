#version 330 core

in vec4 color;
in vec2 fragTexCoord; //this is the texture coord

uniform sampler2D tex; //this is the texture

layout(location = 0) out vec4 out_color;
 
void main(void)
{
	out_color = color;
	//out_color = texture(tex, vec2(1 - fragTexCoord.x, fragTexCoord.y));
}