#version 330 core

in vec4 gfrontColor;
out vec4 fragColor;
in vec3 gnormal;
uniform sampler2D colorMap; 
void main()
{

    fragColor = gfrontColor;
}
