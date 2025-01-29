#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform sampler2D explosion;
uniform float time;

void main()
{
    int frame = int(time*30);
    float s = vtexCoord.s;
    float t = vtexCoord.t;
    fragColor = texture(explosion, vec2((frame/8.0)+ s*(1/8.0) ,  (5/6.0)-((frame/8)/6.0)+ t*(1/6.0)));
    fragColor *= fragColor.a;
}
