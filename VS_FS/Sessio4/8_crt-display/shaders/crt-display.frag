#version 330 core

in vec4 frontColor;
out vec4 fragColor;
uniform int n=8;
void main()
{

    float coord_Fragmento = gl_FragCoord.y;
     //if(int(gl_FragCoord.y)%n == 0) fragColor =frontColor;
    //mostrar solo una de cada cuatro líneas de la ventana de visualización
    // (en este caso, cualquier línea cuyo número sea un múltiplo de 4). Si n = 4.
    if(int(mod(gl_FragCoord.y,n))== 0) fragColor = frontColor;
    else discard;
    
}
