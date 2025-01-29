#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec4 vertex_clip;
uniform float time;

void main()
{   
    vec3 ndc = (vertex_clip.xyz/vertex_clip.w)+ vec3(1.0);  
    // solo va renderizando los ndc.x que sean menores a time
    // por ejemplo, si fijamos time = 1, entonces solo se pintaran los fragmentos ndc.x < 1
    //ya que el shader es capaz de procesar muchos vertices en un segundo.
    // creando la ilusion de que se pintan todos(esto depende el otros factores).
    if (ndc.x < time) fragColor = vec4(0,0,1,1);
    else discard;
    
}