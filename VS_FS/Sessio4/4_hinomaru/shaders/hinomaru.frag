#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform vec4 red = vec4(1,0,0,1.0);



void main()
{   
    float radi = 0.2;
    vec2 centro = vec2(0.5,0.5);
    float  d  = distance(centro,vtexCoord); // calculamos la distancia entre dos puntos. Para saber si estamos dentro del circulo o no.
    
    float res = step(radi,d);
    fragColor = vec4(1);
    if(res == 0) fragColor = red;
   
}
