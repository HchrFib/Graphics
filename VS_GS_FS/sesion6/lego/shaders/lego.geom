#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

//in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec3 gnormal;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float step = 0.5;

vec4 grey = vec4(vec3(0.8), 1.0);


void generar_cubo(vec3 c, float r) {
	vec3 N;
	//Cara frontal
	N = normalize(normalMatrix*vec3(0,0,1));
	gfrontColor = grey*N.z;
	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,-r,r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,-r,r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,r,r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,r,r),1.0);
	EmitVertex();
	EndPrimitive();

	//Cara detras
	
	N = normalize(normalMatrix*vec3(0,0,-1));
	gfrontColor = grey*N.z;
	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,-r,-r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,-r,-r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,r,-r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,r,-r),1.0);
	EmitVertex();
	EndPrimitive();

	//Cara derecha
	
	N = normalize(normalMatrix*vec3(1,0,0));
	gfrontColor = grey*N.z;
	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,-r,-r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,-r,r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,r,-r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,r,r),1.0);
	EmitVertex();
	EndPrimitive();

	//Cara izquierda
	
	N = normalize(normalMatrix*vec3(-1,0,0));
	gfrontColor = grey*N.z;
	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,-r,-r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,-r,r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,r,-r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,r,r),1.0);
	EmitVertex();
	EndPrimitive();


	//Cara Arriba
	
	N = normalize(normalMatrix*vec3(0,1,0));
	gfrontColor = grey*N.z;
	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,r,r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,r,r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,r,-r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,r,-r),1.0);
	EmitVertex();
	EndPrimitive();

	//Cara abajo
	
	N = normalize(normalMatrix*vec3(0,-1,0));
	gfrontColor = grey*N.z;
	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,-r,-r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,-r,-r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(-r,-r,r),1.0);
	EmitVertex();

	gl_Position = modelViewProjectionMatrix
					*vec4(c + vec3(r,-r,r),1.0);
	EmitVertex();
	EndPrimitive();

}

void main( void )
{
	
	vec3 baricentro = (gl_in[0].gl_Position.xyz +
	                   gl_in[1].gl_Position.xyz +
					   gl_in[2].gl_Position.xyz)/3.0;

	vec3 centro = baricentro/step;
    centro.x = int(centro.x);
	centro.y = int(centro.y);
	centro.z = int(centro.z);
	centro *= step;
	float radio = step/2;
	generar_cubo(centro, radio);
	gnormal = vec3(0,1,0);
}
