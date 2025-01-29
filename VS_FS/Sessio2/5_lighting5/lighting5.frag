#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 o_vertex, o_normal;
uniform bool world = false;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrixInverse;

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
    if(!world) {
        vec3 N = normalize(normalMatrix*o_normal);
        vec3 V = normalize((modelViewMatrix*vec4(o_vertex, 1.0)).xyz);
        vec3 L = normalize(lightPosition.xyz - V);
        fragColor = light(N,-V,L);
    } else {
        //El (0,0,0) en eye space que es donde esta el origen de la camara, hay que pasarlo a world space
        vec3 V_world = normalize((modelViewMatrixInverse*vec4(0,0,0,1)).xyz - o_vertex);
        vec3 L_World = normalize((modelViewMatrixInverse*lightPosition).xyz - o_vertex);        
        fragColor = light(o_normal, V_world, L_World);
    }
}
