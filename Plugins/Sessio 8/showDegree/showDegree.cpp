#include "showDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad()
{
	const Object &obj  =scene()->objects()[0]; // obtenemos la referencia constante para no hacer copias
	const int nFaces = obj.faces().size(); // Nos devuelve el numero de caras del objeto
	const int nVertexs = nFaces*3; // asumiendo que son triangles
	const int nVertex = obj.vertices().size();
    grauMig = double(nVertexs)/nVertex;


}
void ShowDegree::postFrame()
{
	painter.begin(glwidget()); // Ver plugin "showHelpN"
    QFont font;
    font.setPixelSize(15);
    painter.setFont(font);
    
    painter.drawText(5, 20, QString("%1").arg(grauMig));
    painter.end();
}
