#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform vec4 gris = vec4(0.8);
uniform vec4 negro = vec4(0);
uniform float n = 8;
void main()
{

    //version1
    // ----------
    /*float x = vtexCoord.s*n;
    float y = vtexCoord.t*n;
    if(mod(x, 1) < 0.1 || mod(y, 1) <= 0.1 ) fragColor = negro;
    else fragColor = gris;*/
    
    // version2
    /*float x = vtexCoord.s;
    float y = vtexCoord.t;
    if((mod(x , 1.0/n) < 1/(10.0*n))||(mod(y , 1.0/n) < 1/(10.0*n)) ) fragColor = negro;
    else fragColor =gris;*/
    
    //version3
    float ancho_raya = 0.1; //porque como el ancho del cuadrado es 1 entoncnes
    vec2 c = vtexCoord*n;
    if(fract(c.s) <= ancho_raya  || fract(c.t) <= ancho_raya) fragColor =vec4(0,0,0,1);
    else fragColor =gris;
    
}
