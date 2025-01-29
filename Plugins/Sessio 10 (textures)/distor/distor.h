#ifndef _DISTOR_H
#define _DISTOR_H

#include "plugin.h" 
#include <QElapsedTimer>
class Distor: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 bool paintGL();

	
  private:
	// add private methods and attributes here
	
		// add private methods and attributes here
	QOpenGLShaderProgram* program;
	QOpenGLShader* vs;
	QOpenGLShader* fs;
	GLuint textureId;
	GLuint VAO_rect;
	GLuint VBO_coords;
	void load_compile_link_shaders();
	void setup_textures();
	void drawRect();
	QElapsedTimer elapsedTimer;
};

#endif
