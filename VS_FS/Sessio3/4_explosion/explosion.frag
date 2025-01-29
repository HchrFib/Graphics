#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform sampler2D explosion ;
uniform float time;


void main()
{
    
    int frame = int(time*30); 
    int y =  int(1 + frame/8.0) ;
    
    fragColor = texture(explosion,vec2(frame/8.0 + vtexCoord.s/8.0,  (1-y/6.0+ vtexCoord.t/6.0)));
    fragColor *= fragColor.a;
}
