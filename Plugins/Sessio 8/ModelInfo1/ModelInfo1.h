#ifndef _MODELINFO1_H
#define _MODELINFO1_H

#include "plugin.h" 

class ModelInfo1: public QObject, public Plugin
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
	 void onSceneClear(); 	
  private:
	// add private methods and attributes here
	void sceneInfo();
	
	unsigned int nObjects;
	unsigned int nPolygons;
	unsigned int nVertexs;
	double nPolygons_triangles;
	double percentage;
};

#endif
