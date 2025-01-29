#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 n_normal;
uniform mat3 normalMatrix;

void main()
{
    
    vec3 N_eye = normalize(normalMatrix * n_normal);
    fragColor = frontColor*N_eye.z;
}
