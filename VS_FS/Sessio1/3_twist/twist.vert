#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

//opcion1

mat4 rotation1(float angle) {
    return mat4( 
                    vec4(cos(angle), 0 , -sin(angle),0),
                    vec4(0,1,0,0),
                    vec4(sin(angle), 0, cos(angle),  0 ),
                    vec4(0,0,0,1)
               );
}
//opcion2

mat3 rotation2(float angle) {
    return mat3 (
                    vec3(cos(angle),0,-sin(angle)),
                    vec3( 0,1,0),
                    vec3(sin(angle),0,cos(angle))
                );
}

void main()
{
    float angle = 0.4*vertex.y*sin(time);

    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0); //sin iluminacion
    
    //opcion1
    //mat4 rotation = rotation1(angle);
    
    //gl_Position = modelViewProjectionMatrix *rotation* vec4(vertex, 1.0);
    //opcion2
    mat3 rot = rotation2(angle);
    gl_Position = modelViewProjectionMatrix * vec4(rot*vertex, 1.0);
}
