#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
vec4 black = vec4(0);
vec4 gray = vec4(0.8);
void main()
{
    if(int(mod(vtexCoord.s,2)) == int(mod(vtexCoord.t,2))) fragColor = gray; 
    else fragColor = black;
    
}
