#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float scale=8;
uniform float time;

float triangleWave(float x) {
    return abs(mod(x,1)-1.0);
}

mat4 Mtranslate(float tx, float ty, float tz) {
    return mat4 (   vec4(1,0,0,0),
                    vec4(0,1,0,0),
                    vec4(0,0,1,0),
                    vec4(tx,ty,tz,1)
                );
}
mat4 Mscale(float sx, float sy, float sz) {
    return mat4 (   vec4(sx,0,0,0),
                    vec4(0,sy,0,0),
                    vec4(0,0,sz,0),
                    vec4(0,0,0,1)
                );
} 
void main()
{

    vec3 t = vec3(triangleWave(time/1.618), triangleWave(time), 0);
    vec3 T0 = vec3(-1,-1,0);
    vec3 V  = vec3(2,2,0);
    vec3 T  = scale*(T0 + V*t);
    
    vec3 Vtrasladado = (Mtranslate(T.x, T.y, T.z)*vec4(vertex, 1.0)).xyz;
    vec3 Te = (Mscale(1.0/scale, 1.0/scale, 1.0/scale)*vec4(Vtrasladado, 1.0)).xyz;
    
    //vec3 Te = (vertex + T)/scale;  //solucion alternativa

    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(0.3, 0.3, 0.9, 1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4( Te, 1.0);
}
