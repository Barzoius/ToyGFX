#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; 



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 transforms;


out vec3 Normal;
out vec3 Position;


void main()
{

    Position = vec3(model * vec4(aPos, 1.0f));

    gl_Position = projection * view * transforms * model * vec4(Position, 1.0f);

    Normal = aNormal;
    //Normal = mat3(transpose(inverse(model))) * aNormal;


}