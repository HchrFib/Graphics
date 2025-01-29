#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform bool classic = true;

vec2 centro = vec2(0.5,0.5);
float radio = 0.2;


vec4 RED = vec4(1,0,0,1);
vec4 WHITE = vec4(1);
float PI = 3.141592;
float fi = PI/16;

float aastep(float umbral, float x) {
    
    float ancho_filtro = 0.7*length(vec2(dFdx(x),dFdy(x)));
    return smoothstep(umbral - ancho_filtro, umbral + ancho_filtro, x);
   
}

void main()
{   
    float d = distance(vtexCoord, centro);
    float edge = aastep(radio,d);
    float r = aastep(radio, d);
    
    if(classic) {    
        fragColor = vec4(aastep(radio, d)); 
        if (fragColor != vec4(1)) fragColor = vec4(1.0,0.0,0.0,1.0);
        //if(r == 0) fragColor = RED;
        //else fragColor = WHITE;
    } else {
        vec2 u = vtexCoord - centro;
        float tetta = atan(u.t,u.s);
        //El fragment serà vermell si mod(θ/φ +0.5, 2) < 1 o bé si és a dins del cercle de radi 0.2.
        if(mod(tetta/fi+ 0.5,2) < 1 || r == 0) fragColor = RED;
        else fragColor = WHITE;
    }
        
    
   
   
    
}
