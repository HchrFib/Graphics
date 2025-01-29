#ifndef _MODELINFO2_H
#define _MODELINFO2_H

#include "plugin.h" 
#include <QPainter>

class ModelInfo2: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
	 void onObjectAdd();
	 void onSceneClear(); 	
  private:
	// add private methods and attributes here
	void sceneInfo();
	
	unsigned int nObjects;
	unsigned int nPolygons;
	unsigned int nVertexs;
	double  nPolygons_triangles;
	double percentage;

	//ModelInfo2
	//----------

	QPainter painter;
};

#endif

