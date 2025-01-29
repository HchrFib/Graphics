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
uniform float amplitude = 0.1;
uniform float freq = 1;
const float PI = 3.141592;
void main()
{
    float x = amplitude*sin(2*PI*freq*time + 0);

    vec3 N = normalize(normalMatrix * normal);
    frontColor =  vec4(N.z); //color del vèrtex com el gris que té per components la Z de la normal en eye space.
    vec3 d = normal*x;  //porque nos dice en OBJECT SPACE
    gl_Position = modelViewProjectionMatrix * vec4(vertex + d , 1.0);
}
