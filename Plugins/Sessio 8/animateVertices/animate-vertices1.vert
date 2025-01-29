#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

// -----------------------------
uniform float amplitude = 0.1;
uniform float freq = 1; 


uniform float time;
const float PI = 3.141592;

// -----------------------------
void main()
{
	float dt;
	vec3 x;
	dt = amplitude*sin(2*PI*freq*time)+0;
    x = dt*normal; // necesitamos que el dt se mueva en la direccion de la normal por eso la multiplicamos con la normal.

    vec3 N = normalize(normalMatrix * normal);
    //frontColor = vec4(color,1.0) * N.z;
    frontColor = vec4(N.z);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex + x, 1.0); // le sumamos un cierto x
}

