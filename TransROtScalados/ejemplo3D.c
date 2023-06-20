#include <GL/freeglut.h>

void reshape(GLint w, GLint h);
void display3D();
void initGL();

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ejercicio de transformaciones 3D");
	initGL();
	glutDisplayFunc(display3D);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
	return 0;
}

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); //SC globales
	glLoadIdentity();
	gluPerspective(45.0f, 1, 5, 100); //Con éste código define la proyección
}

void initGL() {
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1, 5, 100); //Con éste código define la proyección

			
}

void display3D() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //enceramos buffer de color y profundidad
	glMatrixMode(GL_MODELVIEW); //MATRIZ DE MODELO
	glLoadIdentity();
	gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLES);	
		glVertex3f(0.0f, 1.0f, 0.0f); //Triangulo del frente
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glVertex3f(0.0f, 1.0f, 0.0f); //Triangulo de derecha
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glVertex3f(0.0f, 1.0f, 0.0f); //Triangulo de atras
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glVertex3f(0.0f, 1.0f, 0.0f); //Triangulo de izquierda
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.5f);
	glBegin(GL_LINE);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}
