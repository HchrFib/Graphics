#ifndef _RGBDEPTH_H
#define _RGBDEPTH_H

#include "plugin.h" 
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class RGBDepth: public QObject, public Plugin
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

	QOpenGLShaderProgram* program1;
	QOpenGLShader* vs1;
	QOpenGLShader* fs1;


	GLuint textureId;
	GLuint VAO_rect;
	GLuint VBO_coords;
	void load_compile_link_shaders();
	void load_compile_link_shaders1();
	void setup_textures();
	void drawRect();
};

#endif
