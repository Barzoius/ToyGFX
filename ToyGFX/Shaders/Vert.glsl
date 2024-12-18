#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; 


out vec3 VertexColor;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 transforms;


void main()
{
    VertexColor = aColor;

    gl_Position = projection * view * transforms * model * vec4(aPos, 1.0f);

}