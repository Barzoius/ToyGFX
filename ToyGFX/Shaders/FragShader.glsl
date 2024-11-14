#version 330 core
in vec3 instanceColor;

out vec4 FragColor;

uniform vec3 Color;

void main()
{
    FragColor = vec4(instanceColor, 1.0); 

}