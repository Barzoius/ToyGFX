#version 330 core

layout (location = 0) out vec4 FragColor;

uniform vec2 uResolution;


void render(inout vec3 color, in vec2 uv)
{
    color.rg += uv;
}


void main()
{
    vec2 uv = (2.0f * gl_FragCoord.xy - uResolution.xy) / uResolution.y;

    vec3 color;

    render(color, uv);

    FragColor = vec4(color, 1.0f);
}