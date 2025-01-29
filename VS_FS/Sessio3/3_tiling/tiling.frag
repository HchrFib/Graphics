#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform sampler2D colorMap;
uniform int tiles = 1;

void main()
{    

    fragColor = texture(colorMap, tiles*vtexCoord);
}
