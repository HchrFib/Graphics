#include "RGBDepth.h"
#include "glwidget.h"


//Definimos el size del viewport
const int IMAGE_WIDTH = 512;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void RGBDepth::load_compile_link_shaders(){

	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("RGBDepth.vert");
	cout << "VS log: " << vs->log().toStdString() << endl;
	
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("RGBDepth.frag");
	cout << "FS log: " << fs->log().toStdString() << endl;
    program = new QOpenGLShaderProgram(this);
	program->addShader(vs);		
	program->addShader(fs);
	program->link();
	cout << "Link log:" << program->log().toStdString() << endl;
	if (!program->isLinked()) cout << "Shader link error" << endl; 
}

void RGBDepth::load_compile_link_shaders1() {

	vs1 = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs1->compileSourceFile("SplitView.vert");
	cout << "VS log: " << vs1->log().toStdString() << endl;
	 
	fs1 = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs1->compileSourceFile("SplitView.frag");
	cout << "FS log: " << fs->log().toStdString() << endl;
    program1 = new QOpenGLShaderProgram(this);
	program1->addShader(vs1);		
	program1->addShader(fs1);
	program1->link();
	cout << "Link log:" << program1->log().toStdString() << endl;
	if (!program1->isLinked()) cout << "Shader link error" << endl; 
}

void RGBDepth::setup_textures() {
	
	GLWidget &g = *glwidget();
	g.makeCurrent();
	
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureId);

	g.glBindTexture(GL_TEXTURE_2D, textureId);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
        //cout << textureId[i] << endl;
    
	// Resize to power-of-two viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);
 
} 
void RGBDepth::drawRect() {

	static bool created = false;
	GLWidget &g = *glwidget();
	g.makeCurrent();
	 
	if(!created) {
		cout << created << endl;
		
		created = true;
		//create and bind empty VAO
		g.glGenVertexArrays(1, &VAO_rect);
		//todo lo que declaremos dentro  de g.glGenVertexArrays(1, &VAO_rect)  y g.glBindVertexArray(VAO_rect);
		//pertenecera la VAO_rect

		g.glBindVertexArray(VAO_rect); //Enlazamos VAO_rect para que todo lo que haya dentro, pertenezca al VAO_rect 
		//Aqui declaramos  todos los VBO'S que necesitemos
		//colocamos las coordenadas de tal manera que dibujen una z
		float coords[] = {
			-1,-1, 0,
			 1,-1, 0,
			-1, 1, 0,
			 1, 1, 0
		};
 
		g.glGenBuffers(1, &VBO_coords);
		g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);//Enlazamos el VBO_coords, 
		//Aqui podemo realizar las configuraciones del VBO_coords
		//copiamos lo que hay en la memoria a la GPU
		g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords),coords, GL_STATIC_DRAW);
		// Indicamos como tenemos que interpretar los vertices del buffer coords
		g.glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,0,0);
		g.glEnableVertexAttribArray(0);//Desenlazamos el VBO_coords
		g.glBindVertexArray(0); // Desenlazamos el VAO_rect
		cout << "se ha generado el quad perfectamente" << endl;
	}
	// 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
	
}
void RGBDepth::onPluginLoad()
{
	load_compile_link_shaders();
	load_compile_link_shaders1();
	setup_textures();
}

bool RGBDepth::paintGL()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	//Pass 1. draw scene (este es nuestro primer paso de rendering)
	
	//printamos el fondo del viewport de color negro en este caso
	g.glClearColor(0,0,0,0);
	//Limpiamos el buffer de profundidad y de color
	g.glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
	program->bind();
	program->setUniformValue("colorMap", 0);
	program->setUniformValue("SIZE", float(IMAGE_WIDTH));
	//program->setUniformValue("modelViewProjectionMatrix", QMatrix4x4());
	program->setUniformValue("modelViewProjectionMatrix", camera()->projectionMatrix() * camera()->viewMatrix() );  
	program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
	//rederizamos/pintamos la escena con el objeto(la copa) por defecto y los shaders por defecto

	g.glViewport(0, 0, IMAGE_WIDTH / 2.0, IMAGE_HEIGHT / 2.0);
	if(drawPlugin()) drawPlugin()->drawScene();
	
	g.glViewport(0, IMAGE_WIDTH/ 2.0, IMAGE_WIDTH / 2.0, IMAGE_HEIGHT / 2.0);
	if(drawPlugin()) drawPlugin()->drawScene();
	
	g.glViewport(IMAGE_WIDTH / 2.0, 0, IMAGE_WIDTH/2.0, IMAGE_HEIGHT / 2.0);
	if(drawPlugin()) drawPlugin()->drawScene();

	g.glViewport(IMAGE_WIDTH / 2.0, IMAGE_HEIGHT / 2.0, IMAGE_WIDTH / 2.0, IMAGE_HEIGHT / 2.0);
	if(drawPlugin()) drawPlugin()->drawScene();
	
 
	g.glActiveTexture(GL_TEXTURE0); //Activamos la textura del slot0
	g.glBindTexture(GL_TEXTURE_2D, textureId); //Enlazamos/activamos la textura
	g.glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0, IMAGE_WIDTH, IMAGE_HEIGHT); //copia el contenido del buffer de color 
	g.glGenerateMipmap(GL_TEXTURE_2D);
 
	//PAS2

	g.glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
	
	
	program1->bind();
	program1->setUniformValue("colorMap", 0);
	program1->setUniformValue("SIZE", float(2.0*IMAGE_WIDTH));
	program1->setUniformValue("modelViewProjectionMatrix", QMatrix4x4() );  
	//program->setUniformValue("modelViewProjectionMatrix", camera()->projectionMatrix() * camera()->viewMatrix() );  //MOLESTA EL PLANO
	g.glViewport(0, 0, IMAGE_WIDTH / 2.0, IMAGE_HEIGHT / 2.0);
	g.glBindTexture(GL_TEXTURE_2D, textureId); //Enlazamos/activamos la textura
	
	program1->setUniformValue("display", 0);
	drawRect();

	g.glViewport(0, IMAGE_WIDTH/ 2.0, IMAGE_WIDTH / 2.0, IMAGE_HEIGHT / 2.0);
	g.glBindTexture(GL_TEXTURE_2D, textureId); //Enlazamos/activamos la textura
	
	 
	program1->setUniformValue("display", 1);
    drawRect();

	g.glViewport(IMAGE_WIDTH / 2.0, IMAGE_HEIGHT / 2.0, IMAGE_WIDTH / 2.0, IMAGE_HEIGHT / 2.0);
	g.glBindTexture(GL_TEXTURE_2D, textureId); //Enlazamos/activamos la textura
	 
	program1->setUniformValue("display", 2);
	drawRect();

	g.glViewport(IMAGE_WIDTH / 2.0, 0, IMAGE_WIDTH/2.0, IMAGE_HEIGHT / 2.0);
	g.glBindTexture(GL_TEXTURE_2D, textureId); //Enlazamos/activamos la textura
	program1->setUniformValue("display", 3);
	drawRect();

	// restore state
    g.defaultProgram()->bind();
    g.glBindTexture(GL_TEXTURE_2D, 0);

	return true; // return true only if implemented
}


