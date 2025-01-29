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

mat4 translate(int tx , int ty, int tz) {
    return mat4 (
                    vec4(1,0,0,0),
                    vec4(0,1,0,0),
                    vec4(0,0,1,0),
                    vec4(tx,ty,tx,1.0)

                );
}
mat4 rotation(float A) {
    return mat4 (
                    vec4(1,0,0,0),
                    vec4(0,cos(A), sin(A),0),
                    vec4(0, -sin(A),cos(A),0),
                    vec4(0,0,0,1)
                );
}
void main()
{
    
    mat3 r;
    float A = 0.0;
    if(vertex.y >= 0.5) A = (vertex.y-0.5)*sin(time); 
    
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * translate(0,1,0)*rotation(A)*translate(0,-1,0)*vec4(vertex, 1.0);
}
