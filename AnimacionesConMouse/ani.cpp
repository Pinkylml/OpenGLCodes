#include <iostream>
#include <GL/freeglut.h>

void reshape(GLint w, GLint h);
void initGL();
void display3D();
void dibujarCubo();
void timer(int valor);
void keyDown(int key, int, int);
void keyUp(int key, int, int);
void mouse(int button, int state, int x, int y);
void spinDisplayIzq();
void spinDisplayDer();

float rotAng = 0.0f, spin=0.0f;
int refreshRate = 5;
bool iskey = false, ismouse = false;
float posx = 0.0f;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ejercicio Animaciones 3D");

    glutDisplayFunc(display3D);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyDown);
    glutSpecialUpFunc(keyUp);
    glutMouseFunc(mouse);
    glutTimerFunc(0,timer,0);
    initGL();
    glutMainLoop();

}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1, 5, 100);
}

void initGL() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void display3D() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    glRotatef(-rotAng, 0, 0, 1);
    if (iskey)
        glTranslatef(posx, 0, -6.0f);
    else
        glTranslatef(posx, 0.0f, -6.0f);
    
    dibujarCubo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0f, 0.0f, 0.0f);
    glScalef(1.5f, 1.5f, 1.5f);
    if (ismouse)
        glRotatef(spin, 0, 0, 1);
    else
        glRotatef(rotAng, 0, 0, 1);
    dibujarCubo();
    glPopMatrix();

    glutSwapBuffers();
    rotAng += 0.05f;
}

void timer(int valor) {
    glutPostRedisplay();
    glutTimerFunc(refreshRate, timer, 0);
}

void spinDisplayIzq(){
    if (ismouse) {
        spin -= 0.1;
        if (spin > 360) {
            spin -= 360;
        }
    }
    if (iskey)
        posx -= 0.005f;
    glutPostRedisplay();
}

void spinDisplayDer() {
    if (ismouse) {
        spin += 0.1;
        if (spin > 360) {
            spin -= 360;
        }
    }
    if (iskey)
        posx += 0.005f;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            ismouse = true;
            glutIdleFunc(spinDisplayIzq);
        }
        else if (state == GLUT_UP) {
            ismouse = false;
            glutIdleFunc(NULL);
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) {
            ismouse = true;
            glutIdleFunc(spinDisplayDer);
        }
        else if (state == GLUT_UP) {
            ismouse = false;
            glutIdleFunc(NULL);
        }
        break;
    default:
        break;
    }
}

void keyDown(int key, int,int){
    switch (key) {
    case GLUT_KEY_LEFT:
        iskey = true;
        glutIdleFunc(spinDisplayIzq);
        break;
    case GLUT_KEY_RIGHT:
        iskey = true;
        glutIdleFunc(spinDisplayDer);
        break;
    default:
        break;
    }
}

void keyUp(int key, int, int) {
    switch (key) {
    case GLUT_KEY_LEFT:
        iskey = false;
        glutIdleFunc(NULL);
        break;
    case GLUT_KEY_RIGHT:
        iskey = false;
        glutIdleFunc(NULL);
        break;
    default:
        break;
    }
}

void dibujarCubo(){
    glBegin(GL_QUADS);
    //Izq
    glColor3f(0.9f, 0.8, 0.7);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);
    //Der
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    //Abajo
    glColor3f(0.0f, 0.5f, 1.0f);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    //Arriba
    glColor3f(0.85f, 0.25f, 0.4f);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    //Atr�s
    glColor3f(0.95f, 0.8f, 0.4f);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);
    //Frontal
    glColor3f(1.0f, 0.7f, 0.4f);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glEnd();
}
