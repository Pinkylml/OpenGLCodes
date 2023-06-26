#include <iostream>
#include <GL/freeglut.h>
#include <math.h>

void reshape(GLint w, GLint h);
void initGL();
void timer(int valor);
void display3D();
void dibujarpiramide();
void keyDown(int key, int, int);
void keyUp(int key, int, int);
void mouse(int button, int state, int x, int y);
void spinDisplayIzq();
void spinDisplayDer();
float orbitaPointForX();
float orbitaPointForY();
void spinDisplayOrbit();

float rotAng = 0.0f, spin=0.0f;
int refreshRate = 5;
bool iskey = false, ismouse = false;
float posx = 0.0f;
float transX = 0.0f;
float transY = 0.0f;

// Variables para la órbita
float orbitRadius = 5.0f;
float orbitSpeed = 0.001f;
float orbitAngle = 0.0f;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Deber Animaciones con mouse");

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
    gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    
    glRotatef(-rotAng, 0, 0, 1);
    if (iskey){
        //glTranslatef(posx, 0, -6.0f);
        glTranslatef(transX, 0.0f, transY);
    }
    else
        glTranslatef(posx, 0.0f, -6.0f);
    
    dibujarpiramide();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0f, 0.0f, 0.0f);
    glScalef(1.5f, 1.5f, 1.5f);
    if (ismouse)
        glRotatef(spin, 0, 0, 1);
    else
        glRotatef(rotAng, 0, 0, 1);
    dibujarpiramide();    
    glPopMatrix();

    glutSwapBuffers();
    rotAng += 0.05f;
    spin+=0.0005f;
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
    if (iskey){
        posx -= 0.005f;
    }        
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

void spinDisplayOrbit() {
    if (ismouse) {
        spin += 0.1;
        if (spin > 360) {
            spin -= 360;
        }
    }
    if (iskey)
        transX = orbitaPointForX();
        transY = orbitaPointForY();
    glutPostRedisplay();
}

float orbitaPointForX(){
    float ballX = orbitRadius * cos(orbitAngle);
    return ballX;
}

float orbitaPointForY(){   
    float ballY = orbitRadius * sin(orbitAngle);
    return ballY;
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
    case GLUT_KEY_UP:
        iskey = true;
        glutIdleFunc(spinDisplayOrbit);
        break;
    case GLUT_KEY_RIGHT:
        iskey = false;
        glutIdleFunc(NULL);
        break;
    default:
        break;
    }
}


void dibujarpiramide(){
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.843, 0.0);
        glVertex3f(-1, -1, 1);
        glVertex3f(1, -1, 1);
        glVertex3f(1, -1, -1);
        glVertex3f(-1, -1, -1);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0, 1, 0);
        glColor3f(1.0f, 0.647f, 0.0f);
        glVertex3f(1, -1, 1);
        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-1, -1, 1);
       
        glColor3f(1.0f, 0.647f, 0.0f);
        glVertex3f(0, 1, 0);
        glVertex3f(1, -1, 1);
        glVertex3f(1, -1, -1);

        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0, 1, 0);
        glVertex3f(-1, -1, 1);
        glVertex3f(-1, -1, -1);

        glColor3f(0.529f, 0.808f, 0.922f);
        glVertex3f(0, 1, 0);
        glVertex3f(-1, -1, -1);
        glVertex3f(1, -1, -1);
    glEnd(); 
} 

    


