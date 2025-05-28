#version 330 core
out vec4 FragColor;

in vec3 ourColor;

uniform float timeValue;

void main()
{
    vec3 colorOnTime = ourColor * abs(sin(timeValue));
    FragColor = vec4(colorOnTime, 1.0f);
}
