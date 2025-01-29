#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;


bool inCircle(vec2 p, vec2 c, float r) {
    return (distance(p,c) <= r);
} 
bool inRect(vec2 p, vec2 m, vec2 M) {
    return ((p.x >= m.x && p.x < M.x) &&(p.y >= m.y && p.y <= M.y));
}
void main()
{
    fragColor = vec4(0); //definim el color de fondo.
    float r = 1.5; 
    float R = 3;
    //escalamos y centramos para trabajar en [-5,5] x [-5,5]. no da error si nos salimos del plano.
    vec2 p = 10*vtexCoord - vec2(5);

    //part inferior de la "J"
    // inCircle(p,vec2(0,-1),R) -> pinta el ciculo blanco
    // (!inCircle(p, vec2(0,-1), r)  -> no pinta de blanco las p's que estan dentro del circulo pequeño
    // p.y <= -1.0 -> que se aplique solo la condicion para las p's que están por debajo de p.y = -1
    if(inCircle(p,vec2(0,-1),R) && (!inCircle(p, vec2(0,-1), r))&& p.y <= -1.0){
        fragColor = vec4(1);
    }
    //segmento vertical
   if(inRect(p, vec2(r, -1) ,vec2(R, 4))) fragColor = vec4(1);

     
}
