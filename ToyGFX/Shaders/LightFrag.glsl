#version 330 core
//in vec3 instanceColor;

out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 Color;

uniform vec3 lightOrigin;

uniform vec3 camOrigin;

void main()
{
    float ambient = 0.35f;

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightOrigin - Position);

    float diffuse  = max(dot(normal, lightDir), 0.0f);

    float specLight = 0.50f;
    vec3 eyeDir = normalize(camOrigin - Position);
    vec3 reflectedRay = reflect(-lightDir, normal);

    float specIntensity =  pow(max(dot(eyeDir, reflectedRay), 0.0f), 8);

    float spec = specIntensity * specLight;

    FragColor = vec4(Color ,1.0) * (diffuse + ambient + spec); 

}