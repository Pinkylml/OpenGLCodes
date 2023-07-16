#include <iostream>
#include <GL/freeglut.h>

void reshape(int w, int h);
void initGL();
void display();

//son importantes los argumentos
int main(int argc,char **  argv) 
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ejemplo iluminacion");
	initGL(); //inicizaliamos las luces
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
	} 

//funcion de reshape
void reshape(int w, int h) {
	glViewport(0, 0, w, h);// comienza desde 0 de la ventana y se va ir hasta el ancho y el alto de la ventana
	//proyeccion ortogonal 
	glMatrixMode(GL_PROJECTION);//
	glLoadIdentity();
	gluOrtho2D(-6,6,-4,4);
	//paso el objeto 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//init donde se habilitara las luces
void initGL() {
	glClearColor(0.3,0.3,0.3,0.0);//limpieza del fondo
	//habilitamos el test de profundidad
	glEnable(GL_DEPTH_TEST);
	//color de la luz
	GLfloat ambient[] = { 0.0, 0.0, 0.0 , 1.0 };
	GLfloat diffuse[] = {  1.0, 1.0, 1.0 ,1.0 };
	GLfloat position[] = {  2.0, 3.0, 2.0 , 0.0 };
	//intensidad de la luz ambiental
	GLfloat model_ambient[] = { 0.5,0.5,0.5,1.0 };
	//definir un punto de visualización
	GLfloat local_view[] = { 0.0 };
	//creamos luces, estamos trabajando con la luz 0
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//mandamos parametros del modelo y vista
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	//habilitamos luces
	//primero del modelo
	glEnable(GL_LIGHTING);
	//luego del punto de luz
	glEnable(GL_LIGHT0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	//Inicio de dibujo esfera
	glColor3f(1, 0, 0); 
	glutSolidSphere(1, 16, 16);
	glPopMatrix();
	glutSwapBuffers();
}