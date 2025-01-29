#include "drawBoundingBox.h"
#include "glwidget.h"

void DrawBoundingBox::onPluginLoad()
{

	// Carregar shader, compile & link 
	load_compile_link_shaders();
	//create VAO 
    createVertexArrayObject();
	//create VBO's
	createVertexBufferObject();
}
void DrawBoundingBox::createVertexArrayObject() 
{
	GLWidget &g = *glwidget(); // para tener nuestra ventana activa
	g.makeCurrent();
	//definimos el VAO
	g.glGenVertexArrays(1, &VAO_cube); // obtenemos un identificador de VAO
	g.glBindVertexArray(VAO_cube);     // asociamos
}
void DrawBoundingBox::load_compile_link_shaders() 
{
	
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("drawBoundingBox.vert");
	cout << "VS log:" << vs->log().toStdString() << endl;
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("drawBoundingBox.frag");
	cout << "FS log:" << fs->log().toStdString() << endl;
	program = new QOpenGLShaderProgram(this);
	
    program->addShader(vs);
    program->addShader(fs);
    program->link();
	cout << "Link log:" << program->log().toStdString() << endl;

	if (!program->isLinked()) cout << "Shader link error" << endl; 
}
void DrawBoundingBox::createVertexBufferObject() 
{ 
	GLWidget &g = *glwidget();
    g.makeCurrent();
	//definimos el bufffer, with los vertices que definen la caja contenededora que es un cubo
	//with 36 vertices, tenemos vertices repetidos
	GLfloat buffer_vertex[] = { 
			0,0,1,
			1,0,1,
			0,1,1,

			1,0,1,
			0,1,1,
			1,1,1,

			0,1,1,
			1,1,1,
			0,1,0,

			1,1,1,
			0,1,0,
			1,1,0,

			1,0,1,
			1,0,0,
			1,1,1,

			1,0,0,
			1,1,1,
			1,1,0,

			0,0,0,
			0,0,1,
			0,1,0,

			0,0,1,
			0,1,0,
			0,1,1,

			0,0,0,
			1,0,0,
			0,0,1,

			1,0,0,
			0,0,1,
			1,0,1,

			0,0,0,
			1,0,0,
			0,1,0,

			1,0,0,
			0,1,0,
			1,1,0
	};
	// Define Vertex
	g.glGenBuffers(1, &VBO_coords); // obtemos un identificador para nuestro VBO
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);  // Enlazamos el array con el identificador
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_vertex), buffer_vertex, GL_STATIC_DRAW); // copiamos de RAM a GPU
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Describimos  que cada 3 floats definen un vertice
    g.glEnableVertexAttribArray(0); 

	//Define Color 
	GLfloat buffer_color[] = { // definimos el color para cada vertice, en este caso el color por vertice de la caja contenedora.
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0
	};
	//Define VBO of color
	g.glGenBuffers(1, &VBO_color);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_color), buffer_color, GL_STATIC_DRAW);
    g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(2);
	
    g.glBindVertexArray(0);  //desactivamos el bind  

}


void DrawBoundingBox::postFrame()
{
	program->bind();
	GLWidget &g = *glwidget();
    g.makeCurrent();


	QMatrix4x4 MVP = camera()-> projectionMatrix()*camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);

	Scene* scn = scene();
    const vector<Object>  &obj = scn->objects();
 
	// pintar la capsa contenidora de tots els objectes de l'escena
	for (int i = 0; i < (int)obj.size(); ++i) {
       
        program->setUniformValue("boundingBoxMin",obj[i].boundingBox().min());
        program->setUniformValue("boundingBoxMax",obj[i].boundingBox().max());
        g.glBindVertexArray(VAO_cube);
        //g.glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // activar pintar nomes linies
        g.glDrawArrays(GL_TRIANGLES, 0, 36);
        g.glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // desactivar
        g.glBindVertexArray(0);
    } 
	program->release();
}






