#include "ModelInfo1.h"
#include "glwidget.h"


void ModelInfo1::sceneInfo() {
	
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
void ModelInfo1::onPluginLoad()
{
	nObjects = scene()->objects().size();
	sceneInfo();
	
	
}

void ModelInfo1::preFrame()
{
	
}

void ModelInfo1::postFrame()
{
	cout << "Number objects: " << nObjects << endl;
	cout << "Number polygons all objects: " << nPolygons << endl;
	cout << "Number of vertexs is: " << nVertexs << endl;
	cout << "Percentage: " << percentage << "%" << endl;
}

void ModelInfo1::onObjectAdd()
{
	nObjects = scene()->objects().size();
	sceneInfo();
}
void ModelInfo1::onSceneClear()
{
	nObjects = 0;
	nPolygons = 0;
	nVertexs = 0;
	nPolygons_triangles = 0;
	
}
bool ModelInfo1::drawScene()
{
	return false; // return true only if implemented
}
 
bool ModelInfo1::drawObject(int)
{
	return false; // return true only if implemented
}

bool ModelInfo1::paintGL()
{
	return false; // return true only if implemented
}

void ModelInfo1::keyPressEvent(QKeyEvent *)
{
	
}

void ModelInfo1::mouseMoveEvent(QMouseEvent *)
{
	
}

