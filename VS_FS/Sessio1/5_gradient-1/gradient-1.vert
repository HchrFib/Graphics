#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;


out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

const vec4 colors[5] = vec4[5] (

                        vec4(1,0,0,1), //red
                        vec4(1,1,0,1), //yellow
                        vec4(0,1,0,1), //green
                        vec4(0,1,1,1), //cian
                        vec4(0,0,1,1)  //blue
                    );


void main()
{
	//num_intervalos = boxSize
    float num_intervalos = (boundingBoxMax.y-boundingBoxMin.y)/4;
    float pos = (vertex.y - boundingBoxMin.y)/num_intervalos;

    int index  = int(pos);
    float t = fract(pos);



    vec3 N = normalize(normalMatrix * normal);
    //frontColor = vec4(color,1.0) * N.z;
    frontColor = mix(colors[index], colors[index+1], t);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
