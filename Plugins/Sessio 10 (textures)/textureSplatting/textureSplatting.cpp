#include "textureSplatting.h"
#include "glwidget.h"

void TextureSplatting::onPluginLoad()
{
	load_compile_link_shaders();
	load_texture_noise0();
	load_texture_rock1();
	load_texture_grass2();

	
}

void TextureSplatting::load_texture_grass2() {
	GLWidget &g = *glwidget();
    g.makeCurrent();

    QString filename2 = QFileDialog::getOpenFileName(0, "Open Image 2", "../../Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename2);	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
    g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE1);
	g.glGenTextures( 1, &grass2);
	g.glBindTexture(GL_TEXTURE_2D, grass2);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
}
void TextureSplatting::load_texture_rock1() { 

	GLWidget &g = *glwidget();
    g.makeCurrent();

    QString filename2 = QFileDialog::getOpenFileName(0, "Open Image 2", "../../Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename2);	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
    g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE1);
	g.glGenTextures( 1, &rock1);
	g.glBindTexture(GL_TEXTURE_2D, rock1);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureSplatting::load_texture_noise0() {

	GLWidget &g = *glwidget(); // cogemos el apuntados a nuestra ventana y los guardamos en una referencia
    g.makeCurrent(); // usamos nuestro contexto grafico de nuestro GLwidget
	  
	// VS 
	// Load Texture noise
	QString filename = QFileDialog::getOpenFileName(0, "Open Image", "../../Textures", "Image file (*.png *.jpg)");	
	//cout << filename.toStdString() << endl;
	QImage img0(filename);	
   
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored(); 
    g.makeCurrent(); 

	g.glActiveTexture(GL_TEXTURE0); 
	g.glGenTextures( 1, &noise0); // Nos da un identificador de textura
	g.glBindTexture(GL_TEXTURE_2D, noise0); 
    
    g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits()); //definimos el BitMAP
    g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0); 
}
void TextureSplatting::load_compile_link_shaders() {

	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("textureSplatting.vert");
	cout << "VS log:" << vs->log().toStdString() << endl;
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("textureSplatting.frag");
	cout << "FS log:" << fs->log().toStdString() << endl;
	program = new QOpenGLShaderProgram(this);
	                        
    program->addShader(vs);
    program->addShader(fs);
    program->link(); 
	cout << "Link log:" << program->log().toStdString() << endl;
     
	if (!program->isLinked()) cout << "Shader link error" << endl; 
}

void TextureSplatting::preFrame()
{
	GLWidget &g = *glwidget();
    g.makeCurrent();
	program->bind();
	program->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() * g.camera()->viewMatrix());
    program->setUniformValue("normalMatrix", g.camera()->viewMatrix().normalMatrix());
	program->setUniformValue("noise0", 0);  // texture unit del primer sampler 
    program->setUniformValue("rock1", 1);  //  texture unit del segon  sampler 
    program->setUniformValue("grass2", 2);  // texture unit del tercer  sampler
 
     // bind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, noise0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, rock1);
    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, grass2);

}
void TextureSplatting::postFrame()
{
	GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind default shaders
    g.defaultProgram()->bind();
    // unbind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureSplatting::onObjectAdd()
{
	
}

bool TextureSplatting::drawScene()
{
	return false; // return true only if implemented
}

bool TextureSplatting::drawObject(int)
{
	return false; // return true only if implemented
}

bool TextureSplatting::paintGL()
{
	return false; // return true only if implemented
}

void TextureSplatting::keyPressEvent(QKeyEvent *)
{
	
}

void TextureSplatting::mouseMoveEvent(QMouseEvent *)
{
	
}

