#version 330 core

//in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;
in vec2 vtexCoord;
in vec3 N;
void main()
{
    vec4 c_rock1 = texture(rock1, vtexCoord);
    vec4 c_grass2 = texture(grass2, vtexCoord);
    vec4 c_ruido = texture(noise0, vtexCoord);
    fragColor = mix(c_rock1, c_grass2, c_ruido.r);
}
