#version 330 core
layout(location = 0) in vec3 in_position;  //set the frist input on location (index) 0 ; in_position is our attribute 
 
void main()
{
  gl_Position = vec4(in_position, 1.0);//w is 1.0
}