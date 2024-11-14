#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aOffset;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


layout (std140) uniform ColorBlock {
    vec3 instanceColors[100];
};

out vec3 instanceColor;

void main()
{

    gl_Position = projection * view * model *  vec4(aPos + aOffset, 1.0);

    instanceColor = instanceColors[gl_InstanceID];
}