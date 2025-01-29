#version 330 core

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

void main()
{
    float riudo_noise = texture(noise0,  vtexCoord).r; //obtenemos el ruido
    vec4 rock  = texture(rock1,  vtexCoord);
    vec4 grass = texture(grass2, vtexCoord);
    fragColor = mix(rock, grass, riudo_noise);
}
