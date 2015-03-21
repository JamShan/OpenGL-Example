#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "textfile.h"
using namespace std;

GLuint program;
struct Window {
	Window(char* t, const int &w, const int &h, const int &px, const int &py)
		:title(t), width(w), height(h), posX(px), posY(py){}
	int width, height;
	int posX, posY;
	char *title;
};

Window window("toon shader", 720, 640, 300, 0);


void setShaders() {

	char *vs = NULL,*fs = NULL;

	GLuint v = glCreateShader(GL_VERTEX_SHADER);
	GLuint f = glCreateShader(GL_FRAGMENT_SHADER);


	vs = textFileRead("toon.vert");
	fs = textFileRead("toon.frag");

	const char * ff = fs;
	const char * vv = vs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

	GLuint p = glCreateProgram();
	glAttachShader(p,f);
	glAttachShader(p,v);

	glLinkProgram(p);
	glUseProgram(p);
}
void init()
{
	float lpos[4] = {1, 0.5 , 1 ,0};
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	setShaders();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

}


static glm::vec3 target(0.0f, 0.0f, 0.0f);
static glm::vec3 up(0.0f, 1.0f, 0.0f);
static float camX = 0.0, camY = 0.0, camZ = 5.0;
int startX, startY, tracking = 0;
float alpha = 0.0f, beta = 0.0f;
float r = 5.0f;
void render()
{
	//glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0)[0]);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSolidTeapot(1.0f);
	static glm::mat4 view_matrix;
	view_matrix = glm::lookAt(glm::vec3(camX, camY, camZ), target, up);
	static glm::mat4 proj_matrix =  glm::perspective(45.0f, 1.0f, 1.0f, 1000.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(&proj_matrix[0][0]);
	//gluPerspective(45.0, 1.0, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glLoadMatrixf(&view_matrix[0][0]);
	glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) 
{
	switch(key) {

		case 27:
			glutLeaveMainLoop();
			break;
		case 'z': r -= 0.1f; break;
		case 'x': r += 0.1f; break;	
		case 'm': glEnable(GL_MULTISAMPLE); break;
		case 'n': glDisable(GL_MULTISAMPLE); break;
	}
	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r *   						     sin(beta * 3.14f / 180.0f);

//  uncomment this if not using an idle func
//	glutPostRedisplay();
}

void processMouseButtons(int button, int state, int xx, int yy)
{
	// start tracking the mouse
	if (state == GLUT_DOWN)  {
		startX = xx; //获取当前坐标
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
	}

	//stop tracking the mouse
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (startX - xx);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			r += (yy - startY) * 0.01f;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy)
{
	int deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	deltaX = startX - xx;
	deltaY = yy - startY;

	// left mouse button: move camera
	if (tracking == 1) {
		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;
		if (betaAux > 85.0f)
			betaAux = 85.0f;
		else if (betaAux < -85.0f)
			betaAux = -85.0f;
		rAux = r;

		camX = rAux * cos(betaAux * 3.14f / 180.0f) * sin(alphaAux * 3.14f / 180.0f);
		camZ = rAux * cos(betaAux * 3.14f / 180.0f) * cos(alphaAux * 3.14f / 180.0f);
		camY = rAux * sin(betaAux * 3.14f / 180.0f);
	}
	// right mouse button: zoom
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r + (deltaY * 0.01f);

		camX = rAux * cos(betaAux * 3.14f / 180.0f) * sin(alphaAux * 3.14f / 180.0f);
		camZ = rAux * cos(betaAux * 3.14f / 180.0f) * cos(alphaAux * 3.14f / 180.0f);
		camY = rAux * sin(betaAux * 3.14f / 180.0f);
	}
}

void mouseWheel(int wheel, int direction, int x, int y) {

	r += direction * 0.1f;
	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r * sin(beta * 3.14f / 180.0f);
}

void reshape(int w, int h)
{  
	glViewport(0, 0, w, h);

}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(window.posX, window.posY);
	glutInitWindowSize(window.width, window.height);
	glutCreateWindow(window.title);
	glewInit();
	init();
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutMouseWheelFunc (mouseWheel);
	glutIdleFunc(idle);
	glutMainLoop();
}
