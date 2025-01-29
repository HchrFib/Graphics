#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

const vec4 colors[5]= vec4[5](
        
        vec4(1,0,0,1), //red
        vec4(1,1,0,1), //yellow
        vec4(0,1,0,1), //green
        vec4(0,1,1,1), //cian
        vec4(0,0,1,1)  //blue
);

void main()
{

    float minY = boundingBoxMin.y;
    float maxY = boundingBoxMax.y;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    
    //ahora tenemos las coordenadas en NDC -> vertex_NDC (-1,1)
    vec3 vertex_NDC = gl_Position.xyz/gl_Position.w;

    //pasamos las coordenadas entre 0 y 2
    vertex_NDC = vertex_NDC +1;
    // no podemos hacer (maxY - minY)/4.0, porque estas variables no estan en NDC, estan en coordenadas de modelo
    float trozo = (1.0 - (-1.0))/4.0;
    
    float k = vertex_NDC.y/trozo;



    float fracccion = fract(k);
    frontColor = mix(colors[int(k)], colors[int(k)+1], fracccion);
}
