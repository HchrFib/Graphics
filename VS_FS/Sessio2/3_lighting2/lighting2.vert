#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform mat4 modelViewMatrix;

vec4 light(vec3 N, vec3 V, vec3 L)
{
    N=normalize(N); V=normalize(V); L=normalize(L);
    vec3 R = normalize( 2.0*dot(N,L)*N-L );
    float NdotL = max( 0.0, dot( N,L ) );
    float RdotV = max( 0.0, dot( R,V ) );
    float Idiff = NdotL;
    float Ispec = 0;
    if (NdotL>0) Ispec=pow( RdotV, matShininess );
    return
    matAmbient * lightAmbient +
    matDiffuse * lightDiffuse * Idiff+
    matSpecular * lightSpecular * Ispec;
}

void main()
{
    vec3 N = normalize(normalMatrix * normal); // en eye_space
    vec3 V = normalize((modelViewMatrix*vec4(vertex,1.0)).xyz); // Vertex en eye_space
    vec3 L = normalize(lightPosition.xyz - V); // L en eye_space  = LigthPosition - V en eye space. 
    
    frontColor =  light(N, -V, L);
   
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
/* 
En el modelo de iluminación de Phong, se utiliza el vector "-V" para representar la dirección desde el punto de vista del observador 
hacia el punto en la superficie que se está iluminando. Este vector se conoce como el vector de vista o vector de visualización.

La razón por la cual se utiliza "-V" en lugar de simplemente "V" es porque se asume que el vector normal de la superficie (N) está 
apuntando hacia afuera de la superficie. Por convención, se considera que los vectores normales de las superficies apuntan hacia afuera.

Al restar "-V" en lugar de simplemente "V", se asegura que el vector resultante apunte en la dirección correcta, es decir, desde el 
punto de vista del observador hacia el punto de la superficie. Esto es importante para calcular correctamente el componente especular 
de la iluminación, que depende de la dirección de la luz reflejada en relación con la dirección del observador.

En resumen, al pasar el vector "-V" al modelo de iluminación de Phong, se asegura que los cálculos de iluminación especular sean 
consistentes y proporcionen resultados correctos al considerar la dirección desde el observador hacia el punto en la superficie que 
se está iluminando.

*/