#define _USE_MATH_DEFINES
#include <stdio.h>
#include <GL/freeglut.h>
#include <math.h>

int refreshRate = 300;
int segNum = 4;  //porque empesamos con un cuadrado
int radio = 50;


void reshape(GLint w, GLint h);
void initGL();
void timer(int valor);
void morphing(int segmentos);
void displayMorph();

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ejercicio MOrphing");
	glutDisplayFunc(displayMorph);
	glutReshapeFunc(reshape); //eviat que se redibuje al aumentar la ventana, no es necesario esta funcion.
	glutTimerFunc(0, timer, 0);
	initGL();
	glutMainLoop();//Mantener abierta la ventana.

}

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	//glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0f, 1, 5, 100);	//La perspectiva esta entre 1 y 5
	gluOrtho2D(-100, 100, -100, 100);
}

void initGL() {
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}

void timer(int valor) {
	glutPostRedisplay(); //Fuerza un recibo
	glutTimerFunc(refreshRate, timer, 0);
}

void displayMorph() {
	glClear(GL_COLOR_BUFFER_BIT);
		morphing(segNum);
		glutSwapBuffers();
	segNum++;
}

void morphing(int segmentos) {
	float theta = 0.0f;
	float x = 0.0f;
	float y = 0.0f;
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < segmentos; i++) {
		double theta = M_PI * 2.0 * ((double)i) / ((double)segmentos);
        double x = ((double)radio) * cos(theta - (M_PI * 45.0 / 180.0));
        double y = ((double)radio) * sin(theta - (M_PI * 45.0 / 180.0));

		glVertex2f(x, y);
	}
	glEnd();
}
