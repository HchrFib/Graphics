#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 vvertex;
uniform mat3 normalMatrix;

void main()
{
    //Calcular los vectores tangentes a la superficie utilizando las funciones dFdx y dFdy 
    //con las coordenadas de la posicion del fragmento
    vec3 v_tangente1 = dFdx(vvertex);
    vec3 v_tangente2 = dFdy(vvertex);
    vec3 n = normalize(cross(v_tangente1, v_tangente2));
    
    vec3 N = normalize(normalMatrix*n);
    
    fragColor = frontColor*N.z;
}
