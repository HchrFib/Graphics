#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform float time;
uniform sampler2D colorMap;
uniform sampler2D colorMap1;
// Declaramos la textura.
// las coordenadas de textura la recibe el VS  textCoord y las saca como un vec2 vtextCoord.
 

void main()
{
    // hacemos un acceso a textura con texture(de que textura quiero tomar la muestras, y las coord. de textura S,T)
    // que vamos a utilizar.
    
    //Ejemplo 1:
    //----------
    
    //if(fract(time) < 0.5) {
    
        fragColor = texture(colorMap , 2*vtexCoord);
    //} else {
        //fragColor = texture(colorMap1 , vtexCoord);
    //}

    //Ejemplo 2: para ver hacia a donde avanzan las coorderadas s y t usando la textura grid y cualquiero objeto
    //----------
    //if(vtexCoord.x >= 0 && vtexCoord.t >= 0)  fragColor = texture(colorMap , vtexCoord); // esta condicion depende del modelo
    //else fragColor = vec4(0);
    // Ejemplo 3: para saber a donde hacia donde avanzan las coordenadas S , T , segun el color y el objeto plano.
    //-----------
    //fragColor = vec4(vtexCoord,  0 ,0);  
}
