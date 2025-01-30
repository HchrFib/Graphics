#version 330 core

in vec4 gfrontColor;
out vec4 fragColor;
in vec2 gtexCoord;


void main()
{   
    
    fragColor = gfrontColor; 
    if(gtexCoord != vec2(-1, -1)) {
        if((gtexCoord.s >= 2.0 && gtexCoord.s <= 3.0) && (gtexCoord.t <= 6.0 && gtexCoord.t >=1.0) ) {
            fragColor = vec4(0);
        }
        if((gtexCoord.s >= 2.0 && gtexCoord.s <= 5.0) && (gtexCoord.t <= 6.0 && gtexCoord.t >=5.0)) {
            fragColor = vec4(0);
        }
        if((gtexCoord.s >= 2.0 && gtexCoord.s <= 4.0) && (gtexCoord.t >= 3.0 && gtexCoord.t <=4.0)) {
            fragColor = vec4(0);
        }
    }
    
}
