#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform float size = 0.07;
uniform float depth = -0.01;
uniform mat4 modelViewProjectionMatrix;
out vec2 gtexCoord;

void main( void )
{
	
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix*gl_in[i].gl_Position;
		gtexCoord =  vec2(-1.0,-1.0);
		EmitVertex();
	}
    EndPrimitive();

	//Constuimos el triangulo izquierdo 
	gfrontColor = vec4(1,0,0,0);
	vec4 v1_clip = modelViewProjectionMatrix* vec4( 1, 1, 0.001,1);
	vec4 v2_clip = modelViewProjectionMatrix* vec4(-1, 1, 0.001,1);
	vec4 v3_clip = modelViewProjectionMatrix* vec4(-1,-1, 0.001,1);

	/*gl_Position = v1_clip; EmitVertex();
	gl_Position = v2_clip; EmitVertex();
	gl_Position = v3_clip; EmitVertex();
    EndPrimitive();*/

    vec4 v1_ndc = vec4(vec3(v1_clip.xyz/v1_clip.w), 1.0);
	vec4 v2_ndc = vec4(vec3(v2_clip.xyz/v2_clip.w), 1.0);
	vec4 v3_ndc = vec4(vec3(v3_clip.xyz/v3_clip.w), 1.0);

	
  
    vec4 baricentro = (v1_ndc+ v2_ndc+v3_ndc)/3.0;
	baricentro = vec4(baricentro.x , baricentro.y, baricentro.z + depth, 1.0);
	gfrontColor = vec4(1,1,0,0);
	gl_Position = vec4(baricentro.x - size , baricentro.y - size, 0.01, 1.0); 
	gtexCoord =  vec2(0,0);
	EmitVertex();
	gl_Position = vec4(baricentro.x + size , baricentro.y - size, 0.01, 1.0); 
	gtexCoord =  vec2(7,0);
	EmitVertex();
	gl_Position = vec4(baricentro.x - size , baricentro.y + size, 0.01, 1.0); 
	gtexCoord =  vec2(0,7);
	EmitVertex();
	gl_Position = vec4(baricentro.x + size , baricentro.y + size, 0.01, 1.0); 
	gtexCoord =  vec2(7,7);
	EmitVertex();
	EndPrimitive();

	
	//Constuimos el triangulo derecho 
	gfrontColor = vec4(0,1,0,0);
	vec4 v4_clip = modelViewProjectionMatrix* vec4(1,  1, 0.001,1);
	vec4 v5_clip = modelViewProjectionMatrix* vec4(1, -1, 0.001,1);
	vec4 v6_clip = modelViewProjectionMatrix* vec4(-1,-1, 0.001,1);

	/*gl_Position = v4_clip; EmitVertex();
	gl_Position = v5_clip; EmitVertex();
	gl_Position = v6_clip; EmitVertex();
    EndPrimitive();*/

    vec4 v4_ndc = vec4(vec3(v4_clip.xyz/v4_clip.w), 1.0);
	vec4 v5_ndc = vec4(vec3(v5_clip.xyz/v5_clip.w), 1.0);
	vec4 v6_ndc = vec4(vec3(v6_clip.xyz/v6_clip.w), 1.0);
  
    baricentro = (v4_ndc+ v5_ndc+v6_ndc)/3.0;
	baricentro = vec4(baricentro.x , baricentro.y, baricentro.z + depth, 1.0);
	gfrontColor = vec4(1,1,0,0);
	gl_Position = vec4(baricentro.x - size , baricentro.y - size, 0.02, 1.0); 
	gtexCoord =  vec2(0,0);
	EmitVertex();
	gl_Position = vec4(baricentro.x + size , baricentro.y - size, 0.02, 1.0); 
	gtexCoord =  vec2(7,0);
	EmitVertex();
	gl_Position = vec4(baricentro.x - size , baricentro.y + size, 0.01, 1.0); 
	gtexCoord =  vec2(0,7);
	EmitVertex();
	gl_Position = vec4(baricentro.x + size , baricentro.y + size, 0.01, 1.0); 
	gtexCoord =  vec2(7,7);
	EmitVertex();
	EndPrimitive();

}
