#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
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

uniform vec3 boundingBoxMin; // cantonada de la capsa englobant
uniform vec3 boundingBoxMax; // cantonada de la capsa englobant
in vec3 vvertex;
in vec3 nnormal;


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
    //matAmbient * lightAmbient +
    (matDiffuse * lightDiffuse * Idiff)/2.0+
    matSpecular * lightSpecular * Ispec;
}

void main()
{   
    vec3 lights[8];
    lights[0] = vec3(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMax.z);
    lights[1] = vec3(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMin.z);
    lights[2] = vec3(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMax.z);
    lights[3] = vec3(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMin.z);
    lights[4] = vec3(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMax.z);
    lights[5] = vec3(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMin.z);
    lights[6] = vec3(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMax.z);
    lights[7] = vec3(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMin.z);
    fragColor = vec4(0);
    //vec3 NE = normalize(normalMatrix*nnormal);
    vec3 N = nnormal;   
    
    vec3 V  = (modelViewMatrixInverse * vec4(0.0, 0.0, 0.0, 1.0)).xyz-vvertex;
    vec3 V1 = (modelMatrix*vec4(V,1.0)).xyz; 
    
    for(int i = 0; i < 8; ++i)
    {
        vec3 L = (modelMatrix*vec4(lights[i]-vvertex,1.0)).xyz;
        fragColor += light(N, V, L);
    }

}

