#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D colormap;

void main()
{
    float s = 15.0*vtexCoord.s;
    float t = 15.0*vtexCoord.t;
    fragColor = vec4(0);
    //las cuatro esquinas ---------
    if(s <= 1 && t >= 14)           fragColor = texture(colormap,  vec2(-(1/6.0) -s*(1/6.0) ,t));    
    if(s>=14 && t >=14)             fragColor = texture(colormap,  vec2((2/6.0)+s*(1/6.0) ,t));    
    if(s<=1 && t <=1)               fragColor = texture(colormap,  vec2( (-1/6.0)-s*(1/6.0),-t));    
    if(s>=14 && t <=1)              fragColor = texture(colormap,  vec2((-4/6.0)+ s*(1/6.0),-t));    
    // ---------------------------

    //laterales
    if((s<=1 || s>=14) && t>=1  && t<=14)     fragColor = texture(colormap, vec2(mod(t*1/6.0, 1/6.0) + 3/6.0 , s));
    //horizontal
    if(s>=1 && s <=14 &&(t <= 1 || t >= 14))  fragColor = texture(colormap, vec2(mod(s*1/6.0 ,1/6.0)+ 3/6.0 ,t));  
    
    //barras internas
    if(mod(int(s),2) == 0 && t >=2 && t <=13 && int(t) != 7) fragColor = texture(colormap, vec2(mod(t*1/6.0 ,1/6.0)+ 3/6.0 ,s)); 
    
    //dibuja los puntos
    if(mod(int(s),2) == 1 && t >= 2 && t <=13 || (int(t) == 1  || int(t) ==7 || int(t) ==13)&&( s >=1 && s <= 14) )
        fragColor = texture(colormap, vec2(mod(s*1/6.0 ,1/6.0)+ 5/6.0 ,t));

    //dibujamos el comecoco
    if(int(s) == 4 && int(t)== 1) fragColor = texture(colormap, vec2(3/6.0 + s*(1/6.0),t));
    //dibujamos el fantasma
    if(int(s) == 5 && int(t)== 1) fragColor = texture(colormap, vec2(1/6.0 + s*(1 /6.0),t));
    
}
