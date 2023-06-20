#include <GL/freeglut.h>
#include <math.h>

void reshape(GLint w, GLint h);
void initGL();
void display3D();
void dibujarCubo();
void timer(int valor);
float orbitaPointForX();
float orbitaPointForY();
float rotAng = 0.0f;
float transX = 0.0f;
float transY = 0.0f;
int refreshRate = 0.00000000000000001;
// Variables para la órbita
float orbitRadius = 5.0f;
float orbitSpeed = 0.001f;
float orbitAngle = 0.0f;

// Variables para la pelota
float ballRadius = 0.05f;
float ballAngle = 0.0f;

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ejercicio Animaciones 3D");
	glutDisplayFunc(display3D);
	glutReshapeFunc(reshape); //eviat que se redibuje al aumentar la ventana, no es necesario esta funcion.
	glutTimerFunc(0,timer,0);
	initGL();
	glutMainLoop();//Mantener abierta la ventana.

}
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	//glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1, 1, 1000);	//La perspectiva esta entre 1 y 5
}

void initGL() {
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}

void timer(int valor) {
	glutPostRedisplay(); //Fuerza un redibo
	glutTimerFunc(refreshRate, timer, 0);
}

void display3D() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);	//la camara esta en z=5. Esta al frente. La imagen esta entre la camara y el origen de coordenadas

	glPushMatrix();
	//glTranslatef(transX,transY, 0.0f);
	glRotatef(rotAng, 0, 0, 1);
	dibujarCubo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(transX, 0.0f, transY);
	//glScalef(1.5f, 1.5f, 1.5f);
	glRotatef(-rotAng, 0, 1, 0);
	dibujarCubo();
	glPopMatrix();
	glutSwapBuffers();
	rotAng += 0.05f;
	transX = orbitaPointForX();
    transY = orbitaPointForY();
     // Actualizar el ángulo de la órbita y la rotación de la pelota
    orbitAngle += orbitSpeed;
    ballAngle += 0.05f; // Velocidad de rotación de la pelota
	//glutPostRedisplay();
}

float orbitaPointForX(){
    float ballX = orbitRadius * cos(orbitAngle);
    return ballX;
}

float orbitaPointForY(){   
    float ballY = orbitRadius * sin(orbitAngle);
    return ballY;
}




void dibujarCubo() {
	glBegin(GL_QUADS);

	//Izq
	glColor3b(0.1f, 0.8f, 0.7f);
	glVertex3f(-1, -1, -1);//PUNTO D
	glVertex3f(-1, -1, 1); //PUNTO A
	glVertex3f(-1, 1, 1);//PUNTO B
	glVertex3f(-1, 1, -1); //PUNTO E

	//Abajo
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	
	//Atras
	glColor3f(0.95f, 0.8f, 0.4f);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);

	//arriba
	glColor3f(0.85f, 0.25f, 0.4f);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);

	//Frontal
	glColor3b(0.0f, 0.9f, 0.4f);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);

	//Derecha
	glColor3f(1.0f, 0.9f, 0.9f);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);

	glEnd();
}
