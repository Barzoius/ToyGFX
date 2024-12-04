#version 330 core

in vec3 VertexColor; 

out vec4 FragColor;


uniform vec3 Color;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(VertexColor ,1.0); 

}

