#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 vertice; //NOS LLEGA EN COORDENADAS DE CLIP SPACE [-1,1]


vec4 red = vec4(1,0,0,0);
vec4 yellow = vec4(1,1,0,0);
void main()
{
    // Usando gl_FragCoord
    // -------------------------------------------------------
    //No es buena opcion utilizar las coordenadas del fragmento en windows space.(PORQUE SON LAS Coordenadas de ventana)
    //Lo mejor es usar las coordenadas en object space.
    // -------------------------------------------------------
    //vec2 centro = vec2(330, 240);
    //distancia en pixels
    //gl_FragCoord -> fragmento , solo consideramos la x,y
    //float d = distance(centro, gl_FragCoord.xy);
    //fragColor = mix(red, yellow,d/150.0);
    //--------------------------------------------------------
    
    
    // Usando coordenadas del vertice
    // --------------------------------------------------------
    //vec2 centro = vec2(0, 0); // centro del modelo
   
    //float d = distance(centro, vertice.xy);
    //fragColor = mix(red, yellow, d/sqrt(2));
    // --------------------------------------------------------

    // Si queremos un cambio de color brusco 
    // --------------------------------------------------------
    vec2 centro = vec2(0, 0); // centro del modelo
   

    float d = distance(centro, vertice.xy); // la distancia esta en object space
    if(d < 0.5) {
        fragColor = red;
    } else fragColor = yellow;
    // --------------------------------------------------------



}
