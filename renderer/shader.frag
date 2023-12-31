#version 330 core

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 LightPosA;
uniform vec3 LightPosB;
uniform vec3 LightPosC;

void main()
{
    vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightColor = vec3(0.5f, 0.5f, 0.5f);

    vec3 normal = normalize(Normal);

    vec3 lightDirA = normalize(LightPosA - FragPos);
    vec3 lightDirB = normalize(LightPosB - FragPos);
    vec3 lightDirC = normalize(LightPosC - FragPos);

    float diffA = max(dot(normal, lightDirA), 0.0);
    float diffB = max(dot(normal, lightDirB), 0.0);
    float diffC = max(dot(normal, lightDirC), 0.0);

    vec3 diffuse = (diffA + diffB + diffC) * lightColor;

    vec3 ambient = 0.2f * lightColor;
    vec3 result = clamp(objectColor * (ambient + diffuse), 0, 1);
    FragColor = vec4(result, 1.0f);
}
