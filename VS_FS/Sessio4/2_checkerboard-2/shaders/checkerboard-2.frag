#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform float n = 8;

vec4 black= vec4(0);
vec4 gray = vec4(0.8);

void main()
{
    float ps = vtexCoord.s*n;
    float pt = vtexCoord.t*n;
    
    if(int(mod(ps, 2)) == int(mod(pt, 2))) fragColor = gray; 
    else fragColor = black;
}
