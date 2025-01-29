#include "animateVertices.h"
#include "glwidget.h"


void AnimateVertices1::onPluginLoad()
{
	
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("animate-vertices1.vert");
	cout << "VS log:" << vs->log().toStdString() << endl;
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("animate-vertices1.frag");
	cout << "FS log:" << fs->log().toStdString() << endl;
    program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
    program->addShader(fs);
	program->link(); 
    
	cout << "Link log:" << program->log().toStdString() << endl;
	elapsedTimer.start();
	
}

void AnimateVertices1::preFrame()
{
    program->bind(); 

    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix(); // aqui podemos realizar la transformacion de modelado (osea 	montamos las matrices de modelado)
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
    program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.0));
}

void AnimateVertices1::postFrame()
{
	
}

void AnimateVertices1::onObjectAdd()
{
	
}

bool AnimateVertices1::drawScene()
{
	return false; // return true only if implemented
}

bool AnimateVertices1::drawObject(int)
{
	return false; // return true only if implemented
}

bool AnimateVertices1::paintGL()
{
	return false; // return true only if implemented
}

void AnimateVertices1::keyPressEvent(QKeyEvent *)
{
	
}

void AnimateVertices1::mouseMoveEvent(QMouseEvent *)
{
	
}


