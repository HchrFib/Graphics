#include "glowing.h"
#include "glwidget.h"
 
//Definimos el size del viewport
const int IMAGE_WIDTH = 512;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

 
void Glowing::load_compile_link_shaders() {

	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("glowing.vert");
	cout << "VS log: " << vs->log().toStdString() << endl;
	
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("glowing.frag");
	cout << "FS log: " << fs->log().toStdString() << endl;
    program = new QOpenGLShaderProgram(this);
	program->addShader(vs);		
	program->addShader(fs);
	program->link();
	cout << "Link log:" << program->log().toStdString() << endl;
	if (!program->isLinked()) cout << "Shader link error" << endl; 
}
void Glowing::setup_textures() {
	
	GLWidget &g = *glwidget();
	g.makeCurrent();
	//g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures(1, &textureId);
	//Hacemos bind para que todas las llamadas del TARGET "GL_TEXTURE_2D" 
	// hagan referencia a id_texture
	g.glBindTexture(GL_TEXTURE_2D, textureId); 
	// establecemos las coordenadas de wraping tanto para s como t
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// especificamos los filtros de minification y magnification
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	//configuramos las caracteristicas de la textura
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT,
		   0, GL_RGB, GL_FLOAT, NULL); // nos permite configurar la textura pero aun no tiene contenido, 
    // porque el ultimo parametro es NULL, porque aun no le hemos pasado un mapa de bits imx.bits()
    // despues cuando haya algo en el buffer de color, podremos definir la textura.
   // g.glBindTexture(GL_TEXTURE_2D, 0);
    // Resize to power-of-two viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT); // cambiamos el size de la ventana openGL 
 
} 
void Glowing::drawRect() {

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
void Glowing::onPluginLoad()
{
	load_compile_link_shaders();
	setup_textures();
}

bool Glowing::paintGL()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	//Pass 1. draw scene (este es nuestro primer paso de rendering)
	
	//printamos el fondo del viewport de color negro en este caso
	g.glClearColor(0,0,0,0);
	//Limpiamos el buffer de profundidad y de color
	g.glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
	//rederizamos/pintamos la escena con el objeto(la copa) por defecto y los shaders por defecto
	if(drawPlugin()) drawPlugin()->drawScene();
	//en este punto tenemos en el buffer de color toda la escena la copa y el fondo de color negro

	//Get texture
	g.glActiveTexture(GL_TEXTURE0); //Activamos la textura del slot0
	g.glBindTexture(GL_TEXTURE_2D, textureId); //Enlazamos/activamos la textura
	g.glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0, IMAGE_WIDTH, IMAGE_HEIGHT); //copia el contenido del buffer de color 
	// a la textura que habiamos preparado.

	//GENERAMOS/CREAMOS un Mipmap
	g.glGenerateMipmap(GL_TEXTURE_2D);
 
	//Pass 2. Draw quad using texture (dibujamos el quad con la textura que acabamos de utilizar)
	//Limpiamos el buffer de profundidad y de color (para borrar la escena (la copa con el fondo negro))
	g.glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);

	program->bind();
	program->setUniformValue("colorMap", 0);
	program->setUniformValue("SIZE", float(IMAGE_WIDTH));
	program->setUniformValue("modelViewProjectionMatrix", QMatrix4x4());
	//Draw quad
	drawRect();

	g.defaultProgram()->bind();
	g.glBindTexture(GL_TEXTURE_2D, 0);
	return true; // return true only if implemented
}
