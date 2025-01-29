#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform vec2 Min=vec2(-1,-1);
uniform vec2 Max=vec2(1,1);

void main() {
    frontColor=vec4(color,1.0);
    
    // La idea del ejercicio es mostrar el modelo proyectado sobre el espacio de textura
    // acotamos el espacio de textura
    // uniform vec2 Min=vec2(-1,-1);
    // uniform vec2 Max=vec2(1,1);
    // como esta definido en un plano que va de min(-1 -1)  a  max(1, 1)
    // y sabemos que todo el viewport va de  [0 ,1]
    // tenemos que trasladar los puntos y finalmente escalarlo *2 , por min-max = 2
 
    //normalizamos las coordenadas de textura entre [0,1]
	float x=(texCoord.x-Min.x)/(Max.x-Min.x);
	float y=(texCoord.y-Min.y)/(Max.y-Min.y);
	//if(vertex.y > 0 && vertex.y  < 1 &&  vertex.x > 0 && vertex.x  < 1) frontColor = vec4(1,0,0,1);
    
    //gl_Position=vec4( texCoord.x ,texCoord.y , 0, 1); // funciona porque ya esta entre cero y uno.
    
    gl_Position=vec4( 2*x-1 ,2*y-1 , 0, 1); // funciona porque ya esta entre cero y uno.
}
