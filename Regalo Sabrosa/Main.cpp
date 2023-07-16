#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include  "Texture.h"

void reshape(GLint w, GLint h);
void initGL();
void display3D();
void dibujarCubo();
void dibujarCuboColorido();
void dibujarCuboColoridoTexturisado();
void timer(int valor);
void moverCamara(int key,int,int);
void orbitCamara(int key, int, int);
void orbitCamara2(int key, int, int);

int refreshRate = 10;
float rotAng = 0.5f;
float camX = 10.0f, camY = 10.0f, camZ= 10.0f;
float cameraSpeed = 0.1f;
float centerX = 0.0f, centerY = 0.0f;
float orbitAng = 0.0f;
float radious = 20.0;
float angleX = 0.0f, angleY = 0.0f;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("eJEMPLO DE TEXTURA");

    glutDisplayFunc(display3D);
    glutReshapeFunc(reshape);
    glutSpecialFunc(moverCamara);
    glutSpecialFunc(orbitCamara2);
    //glutSpecialUpFunc(keyUp);
    //glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);
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
    glEnable(GL_DEPTH_TEST); //Por defecto siempre hace el less
    //glDepthFunc(GL_ALWAYS);
    glEnable(GL_BLEND); //Para que funcione transparencia
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void moverCamara(int key, int, int) {
    switch (key)
    {
    case GLUT_KEY_LEFT:
        camX -= cameraSpeed;
        centerX -= cameraSpeed;
        break;
    case GLUT_KEY_RIGHT:
        camX += cameraSpeed;
        centerX += cameraSpeed;
        break;
    case GLUT_KEY_UP:
        camY += cameraSpeed;
        centerY += cameraSpeed;
        break;
    case GLUT_KEY_DOWN:
        camY -= cameraSpeed;
        centerY -= cameraSpeed;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void orbitCamara(int key, int, int){
    switch (key)
    {
    case GLUT_KEY_LEFT:
        camX = sin(orbitAng) * radious;
        camZ = cos(orbitAng) * radious;
        orbitAng += 0.1;
        break;
    case GLUT_KEY_RIGHT:
        camX = -sin(orbitAng) * radious;
        camZ = -cos(orbitAng) * radious;
        orbitAng -= 0.1;
        break;
    case GLUT_KEY_UP:
        camY = sin(orbitAng) * radious;
        camZ = cos(orbitAng) * radious;
        orbitAng += 0.1;
    case GLUT_KEY_DOWN:
        camY = -sin(orbitAng) * radious;
        camZ = -cos(orbitAng) * radious;
        orbitAng -= 0.1;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void orbitCamara2(int key, int, int) {
    switch (key)
    {
    case GLUT_KEY_LEFT:
        angleY -= cameraSpeed;
        break;
    case GLUT_KEY_RIGHT:
        angleY += cameraSpeed;
        break;
    case GLUT_KEY_UP:
        angleX += cameraSpeed;
        break;
    case GLUT_KEY_DOWN:
        angleX -= cameraSpeed;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void display3D() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float camPosX = radious * sin(angleY) * cos(angleX);
    float camPosZ = radious * cos(angleY) * cos(angleX);
    float campPosY = radious * sin(angleX);
    float upY = 1.0;
    if (angleX > M_PI / 2 && angleX < 3 * M_PI / 2)
        upY = -1;
    if (angleX < -M_PI / 2 && angleX > -3 * M_PI / 2)
        upY = -1;
    gluLookAt(camPosX, campPosY, camPosZ, centerX, centerY, 0, 0, upY, 0);

    glColor3f(1, 0, 0);
    glutSolidSphere(1, 60, 60); //Dibuja una esfera
    
    
    
    
    glPushMatrix();


   //glTranslatef(-5.0f, 0.0f, 0.0f);
    glScalef(5.0f, 5.0f, 5.0f);
    glRotatef(rotAng, 1, 0, 1);
    dibujarCuboColoridoTexturisado();
    glPopMatrix();

   
    glutSwapBuffers();
    rotAng += 1.5f;
    if (angleX >= 2 * M_PI)
        angleX = 0;
    if (angleX <= -2 * M_PI)
        angleX = 0;
}

void timer(int valor) {
    glutPostRedisplay();
    glutTimerFunc(refreshRate, timer, 0);
}




void dibujarCuboColoridoTexturisado() {
    Texture miTextura("image_0.jpg", GL_RGB);
    miTextura.bind(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    
    //Izq

    glTexCoord2f(0, 0); glColor3f(0, 0, 0);  glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0); glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 1); glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
    glTexCoord2f(0, 1); glColor3f(1, 1, 1); glVertex3f(-1, 1, -1);
    glEnd();
    miTextura.unbind(GL_TEXTURE_2D);

    Texture miTextura2("image_1.jpg", GL_RGB);
    miTextura2.bind(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    //Der

    glTexCoord2f(0, 0); glColor3f(1, 0, 0); glVertex3f(1, -1, -1);
    glTexCoord2f(1, 0); glColor3f(1, 0, 1); glVertex3f(1, -1, 1);
    glTexCoord2f(1, 1); glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1); glColor3f(1, 1, 0); glVertex3f(1, 1, -1);
    
    glEnd();
    miTextura2.unbind(GL_TEXTURE_2D);



    Texture miTextura3("image_2.jpg", GL_RGB);
    miTextura3.bind(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    //Abajo
    glTexCoord2f(0, 0); glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0); glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 1); glColor3f(1, 0, 1); glVertex3f(1, -1, 1);
    glTexCoord2f(0, 1); glColor3f(1, 0, 0); glVertex3f(1, -1, -1);
    
    glEnd();
    miTextura3.unbind(GL_TEXTURE_2D);

    Texture miTextura4("image_3.jpg", GL_RGB);
    miTextura4.bind(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    //Arriba
    glTexCoord2f(0, 0); glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);
    glTexCoord2f(1, 0);  glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
    glTexCoord2f(1, 1); glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1); glColor3f(1, 1, 0); glVertex3f(1, 1, -1);
    glEnd();
    miTextura4.unbind(GL_TEXTURE_2D);

    
    Texture miTextura5("image_4.jpg", GL_RGB);
    miTextura5.bind(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    //Atr�s

    glTexCoord2f(0, 0); glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0); glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);
    glTexCoord2f(1, 1); glColor3f(1, 1, 0); glVertex3f(1, 1, -1);
    glTexCoord2f(0, 1); glColor3f(1, 0, 0); glVertex3f(1, -1, -1);
    glEnd();
    miTextura5.unbind(GL_TEXTURE_2D);


    Texture miTextura6("image_5.png", GL_RGB);
    miTextura6.bind(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    //Frontal



    glTexCoord2f(0, 0); glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 0); glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
    glTexCoord2f(1, 1); glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1); glColor3f(1, 0, 1); glVertex3f(1, -1, 1);
    glEnd();
    miTextura6.unbind(GL_TEXTURE_2D);
}
