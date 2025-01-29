#ifndef _TEXTURESPLATTING_H
#define _TEXTURESPLATTING_H

#include "plugin.h" 

class TextureSplatting: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
	 bool drawScene();
	 bool drawObject(int);

	 bool paintGL();

	 void keyPressEvent(QKeyEvent *);
	 void mouseMoveEvent(QMouseEvent *);
  private:
	// add private methods and attributes here
	QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs; 
	void load_compile_link_shaders();
	void load_texture_noise0();
	void load_texture_rock1();
	void load_texture_grass2();

	//create name textures
	GLuint rock1, grass2, noise0;

};

#endif
