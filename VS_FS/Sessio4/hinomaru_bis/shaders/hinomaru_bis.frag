#version 330 core

in vec4 frontColor;
out vec4 fragColor;
uniform vec4 red = vec4(1,0,0,1);
uniform vec4 white = vec4(1);
in vec2 vtexCoord;

float aastep(float treshold, float x) {
    float width = 0.7*length(vec2(dFdx(x),dFdy(x)));
    return smoothstep(treshold - width, treshold + width, x);
}

void main()
{
    float radio = 0.2;
    vec2 centro = vec2(0.5,0.5);
    float d = distance(centro, vtexCoord);
    float s = aastep(radio, d);
    if(s < 1) fragColor = red;
    else fragColor = white;
}
