#ifndef _DRAWBOUNDINGBOX_H
#define _DRAWBOUNDINGBOX_H

#include "plugin.h" 
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class DrawBoundingBox: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();


  private:
	// add private methods and attributes here

	QOpenGLShaderProgram* program;
    QOpenGLShader* vs;  // Apuntador al vs
    QOpenGLShader* fs;  // Apuntador al fs

	bool created;
	GLuint VAO_cube;   //identifacodor de VAO
	GLuint VBO_coords; //identificador de VBO de vertices
	GLuint VBO_color;  //identificador de VBO de color
	void createVertexArrayObject(); 
	void createVertexBufferObject();
	void load_compile_link_shaders();
};

#endif
