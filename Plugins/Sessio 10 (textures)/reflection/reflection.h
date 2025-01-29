#ifndef _REFLECTION_H
#define _REFLECTION_H

#include "plugin.h" 

class Reflection: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 bool paintGL();

  private:
	// add private methods and attributes here
	 QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;  
    GLuint textureId;
};

#endif
