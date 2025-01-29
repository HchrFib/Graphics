#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 o_vertex, o_normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;


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

    // si hacemos //al hacer normalize().xyz,  con la operacion .xyz el vector deja de estar normmalizado, porque
    // la operacion xyz  se hace despues del normalize.
    // en cambio, si hacemos normalize((....).xyz), entonces, el normalize se hace despues de la operacion .xyz  
    
    vec3 N = normalize(normalMatrix * o_normal);
    vec3 V = normalize((modelViewMatrix*vec4(o_vertex,1.0)).xyz);
    vec3 L = normalize(lightPosition.xyz - V);
    fragColor = light(N, -V, L);
}
