#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

//in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform float step = 0.10;

void generar_cubo(vec3 centro, float r) {
	
	//para cada cara del cubo tenemos que calcular
	//su normal (tema iluminacion, color)

	vec4 grey = vec4(0.8);

	//Cara frontal
	vec3 N = normalMatrix*vec3(0,0,1);
	gfrontColor = grey*N.z;
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, -r, r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, -r, r),1);
	EmitVertex();

    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, r, r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, r, r),1);
	EmitVertex();

    EndPrimitive();


	//Cara trasera
	N = normalMatrix*vec3(0,0,-1);
	gfrontColor = grey*N.z;
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, -r, -r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, -r, -r),1);
	EmitVertex();

    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, r, -r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, r, -r),1);
	EmitVertex();
    EndPrimitive();

	//Cara arriba
	N = normalMatrix*vec3(0,1,0);
	gfrontColor = grey*N.z;
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, r, r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, r, r),1);
	EmitVertex();

    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, r, -r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, r, -r),1);
	EmitVertex();
    EndPrimitive();


	//Cara abajo
	N = normalMatrix*vec3(0,-1,0);
	gfrontColor = grey*N.z;
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, -r, r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, -r, r),1);
	EmitVertex();

    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, -r, -r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, -r, -r),1);
	EmitVertex();
    EndPrimitive();

	//Cara derecha
	N = normalMatrix*vec3(1,0,0);
	gfrontColor = grey*N.z;
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, -r, r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, -r, -r),1);
	EmitVertex();

    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, r, r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(r, r, -r),1);
	EmitVertex();
    EndPrimitive();


	//Cara izquierda
	N = normalMatrix*vec3(-1,0,0);
	gfrontColor = grey*N.z;
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, -r, -r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, -r, r),1);
	EmitVertex();

    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, r, -r),1);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix
				*vec4(centro + vec3(-r, r, r),1);
	EmitVertex();
    EndPrimitive();

}

void main( void )
{
	//gfrontColor = vfrontColor[i];
	vec3 baricentro = (gl_in[0].gl_Position.xyz 
					+ gl_in[1].gl_Position.xyz 
					+ gl_in[2].gl_Position.xyz)/3.0;
	
	
	vec3 centro = baricentro/step;
	centro.x = int(centro.x);
	centro.y = int(centro.y);
	centro.z = int(centro.z);
	centro *= step;

    float radio = step/2.0;
	generar_cubo(centro, radio);	
}
