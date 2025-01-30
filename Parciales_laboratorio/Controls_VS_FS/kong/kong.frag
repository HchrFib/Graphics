#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform sampler2D colorMap;

void paintMario(float x, float y) {
    //fragColor = texture(colorMap,vec2( 4.2/7.0 +  vtexCoord.s ,vtexCoord.t*13));
      fragColor = texture(colorMap, vec2( mod(-vtexCoord.s*2,1/7.)+5/7. , y));
}
void paintPrincess(float x, float y) {
    //fragColor = texture(colorMap,vec2( 4.2/7.0 +  vtexCoord.s ,vtexCoord.t*13));
      fragColor = texture(colorMap, vec2( mod(-vtexCoord.s*2,1/7.)+4/7. , y));
}
void paintMonkey(float x, float y) {
    //fragColor = texture(colorMap,vec2( 4.2/7.0 +  vtexCoord.s ,vtexCoord.t*13));
      fragColor = texture(colorMap, vec2( mod(-vtexCoord.s*2,1/6.5) + 1/7. , y));
}
void paintBarril(float x, float y) {
    
      fragColor = texture(colorMap, vec2(mod(vtexCoord.s*2,1/7.)+0/7. , y));
}
void paintBarrilH(float x, float y) {
    
    fragColor = texture(colorMap,vec2(  y/7.0 + 3/7. , x));
    fragColor = texture(colorMap,vec2(  13/7.0*vtexCoord.t + 3/7. , vtexCoord.s*13));
    fragColor = texture(colorMap, vec2(mod(vtexCoord.t*1.85,1/7.)+0/7. , x));
}
void paintWallX(float x, float y) {   
    
    fragColor = texture(colorMap,vec2(mod(vtexCoord.s*2,1/7.) + 2/7., vtexCoord.t*13));
}
void paintWallY(float x, float y) {   
   
    fragColor = texture(colorMap,vec2(mod(vtexCoord.s*2,1/7.) + 3/7., vtexCoord.t*13));
}
void main()
{
    //fragColor = texture(colorMap, vtexCoord);

    //definimos el tablero
    float x = vtexCoord.s*13;
    float y = vtexCoord.t*13;
    if(y > 0  && y < 1 || y > 3  && y < 4 || y > 6  && y < 7 || y > 9  && y < 10 ||
        ( y > 11  && y < 12 && x > 2.6 && x < 5.7 ) ) paintWallX(x,y); //definimos el las coordenadas donde va a aparecer 
    else if(  (y > 1 && y < 3   && (x > 3 && x < 3.5 || x > 6.5 && x < 7.5 || x > 11 && x < 12)) 
           || (y > 4 && y < 6   && (x > 2 && x < 2.7 || x > 5.5 && x < 6.5 || x > 10.1 && x < 11)) 
           || (y > 7 && y < 9   && (x > 3 && x < 3.5 || x > 6.5 && x < 7.5 || x > 11 && x < 12))
           || (y > 10 && y < 13 && (x > 2 && x < 2.8 || x > 5.5 && x < 7.5 ))  ) paintWallY(x,y);
    else if(x > 4.6 && x < 5.5  &&  y > 7 && y < 8) paintMario(x,y);
    else if(x > 3.7 && x < 4.5  &&  y > 12 && y < 13) paintPrincess(x,y);
    else if(x > 10.2 && x < 12  &&  y > 10 && y < 12) paintBarril(x,y);
    else if(x > 9.1 && x < 10  &&  y > 10 && y < 11) paintMonkey(x,y);
    else fragColor = vec4(0);
    if (x > 2 && x < 3 && (y > 4 && y < 5 ) ||
        x > 6 && x < 7 && (y > 4 && y < 5 ) ||
        x > 10 && x <  11 && (y > 4 && y < 5 ) 
         ) paintBarrilH(x,y);
    

    // pintamos de negro los laterales.
    if(x < 1.0 || x > 12) fragColor = vec4(0);
   
}
