#include <GL/freeglut.h>
void reshape(GLint w, GLint h);
void display();

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Hola mundo gráfico");
	glutInitDisplayMode(GLUT_RGB);
	glClearColor(0, 0, 0, 1);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}

void reshape(GLint w, GLint h) {
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.5,1.5,-1.5,1.5);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.24, 0.70, 0.44);
	glutSolidTeapot(1);
	
	glFlush();
}
