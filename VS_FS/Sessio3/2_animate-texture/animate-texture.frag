#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform sampler2D colorMap;
uniform float speed = 0.1;
uniform float time;
void main()
{
    float t,s = 0;

    s = vtexCoord.s + speed*time; 
    t = vtexCoord.t + speed*time; 
    fragColor = frontColor*texture(colorMap, vec2(s,t));
}
