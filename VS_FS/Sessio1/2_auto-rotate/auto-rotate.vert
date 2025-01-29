#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float speed = 0.5;
uniform float time;
//opcion1
mat4 rotate(float angle) {
    return mat4( vec4(cos(angle) ,0, -sin(angle), 0 ),
                 vec4(0          ,1,      0     , 0 ),
                 vec4(sin(angle) ,0, cos(angle) , 0 ),
                 vec4(0          ,0,      0     , 1.0 )   
                );
}
//opcion2
mat3 rotate() {
    return mat3 (   
                    vec3(cos(speed*time),0,-sin(speed*time)),
                    vec3(0,1,0),
                    vec3(sin(speed*time),0,cos(speed*time))
                );
}
void main()
{
    float angle = time*speed;
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    mat4 R = rotate(angle);
    
    //opcion 1
    //gl_Position = modelViewProjectionMatrix * R*vec4(vertex, 1.0);
    
    //opcion2
    gl_Position = modelViewProjectionMatrix *vec4(rotate()*vertex, 1.0);
}
