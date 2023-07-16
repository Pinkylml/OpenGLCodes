#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "dibujar.h"
#include <iostream>
using namespace std;

void display();

int windowWidth = 800;
int windowHeight = 600;


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Dibujar figura con el mouse");
    glClearColor(1.0, 1.0, 1.0, 1.0); // Color de fondo negro
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  
   
    draw(windowHeight); // Llama a la función draw existente
 

    // Dibuja la cuadrícula
    glColor3f(0.5, 0.5, 0.5); // Color de las líneas de la cuadrícula
    glLineWidth(1.0); // Grosor de las líneas de la cuadrícula

    // Dibuja líneas horizontales
    for (int y = 0; y < windowHeight; y += 20) // Ajusta el espaciado de las líneas horizontales
    {
        glBegin(GL_LINES);
        glVertex2i(0, y);
        glVertex2i(windowWidth, y);
        glEnd();
    }

    // Dibuja líneas verticales
    for (int x = 0; x < windowWidth; x += 20) // Ajusta el espaciado de las líneas verticales
    {
        glBegin(GL_LINES);
        glVertex2i(x, 0);
        glVertex2i(x, windowHeight);
        glEnd();
    }
    glFlush();

}
