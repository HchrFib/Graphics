#include "modelInfo2.h"
#include "glwidget.h"


void ModelInfo2::sceneInfo() {

	nObjects = scene()->objects().size();
	// el onSceneClear lo hace.
	nPolygons = 0;
	nVertexs = 0;
	nPolygons_triangles = 0;
	percentage = 0;

	for(unsigned int i = 0; i < nObjects; ++i ) {
		const Object& obj = scene()->objects()[i];
		nPolygons += obj.faces().size();
		
		for(unsigned int j = 0; j < obj.faces().size(); ++j) {
			int vertex = obj.faces()[j].numVertices();
			nVertexs += vertex;
			if(vertex == 3) ++nPolygons_triangles;
		}
		
	}
	percentage = (nPolygons_triangles/nPolygons)*100;
} 
void ModelInfo2::onPluginLoad()
{
	sceneInfo();
}
void ModelInfo2::onObjectAdd()
{
	sceneInfo();
}
void ModelInfo2::onSceneClear()
{
	nObjects = 0;
	nPolygons = 0;
	nVertexs = 0;
	nPolygons_triangles = 0;
	
}
void ModelInfo2::postFrame()
{
	// se llama inmediatamente despues de pintar la escena
	cout << "Number objects: " << nObjects << endl;
	cout << "Number polygons all objects: " << nPolygons << endl;
	cout << "Number of vertexs is: " << nVertexs << endl;
	cout << "Percentage: " << percentage << endl; 


  QFont font;
  font.setPixelSize(15);
  painter.begin(glwidget());
  painter.setFont(font);
  int x = 15;
  int y = 20;
  painter.drawText(x, y, QString("Number objects: "   + QString::number(nObjects)));    
  y += 20;
  painter.drawText(x, y, QString("Number polygons all objects: "   + QString::number(nPolygons))); 
  y += 20;
  painter.drawText(x, y, QString("Number of vertexs is: "   + QString::number(nVertexs)));
  y += 20;
  painter.drawText(x, y, QString("Percentage: "   + QString::number(percentage)+ "%"));
   
  painter.end();
}