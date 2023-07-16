#ifndef DIBUJAR_H
#define DIBUJAR_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>


void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void draw(int windowHeight);



typedef struct Point {
    int x;
    int y;
    float colorRed;
    float colorGreen;
    float colorBlue;
} Point;

bool isDrawing = false;
Point* points = NULL;
int numPoints = 0;

float defaultColorRed = 1.0;
float defaultColorGreen = 1.0;
float defaultColorBlue = 1.0;

float currentColorRed = 1.0;
float currentColorGreen = 1.0;
float currentColorBlue = 1.0;

void draw(int windowHeight)
{
    glPointSize(18.0);
    /*Dibuja cada punto almacenado en la lista points en la ventana OpenGL*/
    glBegin(GL_POINTS);
    for (int i = 0; i < numPoints; i++)
    {
        glColor3f(points[i].colorRed, points[i].colorGreen, points[i].colorBlue);
        glVertex2i(points[i].x, windowHeight - points[i].y);
    }
    glEnd();

}

/*Cambia los colores*/
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r': // Tecla 'r' para cambiar a color rojo
        currentColorRed = 1.0;
        currentColorGreen = 0.0;
        currentColorBlue = 0.0;
        break;
    case 'g': // Tecla 'g' para cambiar a color verde
        currentColorRed = 0.0;
        currentColorGreen = 1.0;
        currentColorBlue = 0.0;
        break;
    case 'b': // Tecla 'b' para cambiar a color azul
        currentColorRed = 0.0;
        currentColorGreen = 0.0;
        currentColorBlue = 1.0;
        break;
    case 'k': // Tecla 'k' para cambiar a color negro
        currentColorRed = 0.0;
        currentColorGreen = 0.0;
        currentColorBlue = 0.0;
        break;
    case 'm': // Tecla 'm' para cambiar a color amarillo
        currentColorRed = 1.0;
        currentColorGreen = 1.0;
        currentColorBlue = 0.0;
        break;
    case 'w': // Tecla 'w' para cambiar a color blanco
        currentColorRed = 1.0;
        currentColorGreen = 1.0;
        currentColorBlue = 1.0;
        break;

    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            isDrawing = true;
            motion(x, y);
        }
        else if (state == GLUT_UP)
        {
            isDrawing = false;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        numPoints = 0;
        free(points);
        points = NULL;
    }

    glutPostRedisplay();
}

void motion(int x, int y)
{
    if (isDrawing)
    {
        numPoints++;
        points = (Point*)realloc(points, numPoints * sizeof(Point)); // Redimensiona dinámicamente el arreglo de puntos points
        points[numPoints - 1].x = x; // Se asignan las coordenadas x actuales del mouse al último punto en la lista points
        points[numPoints - 1].y = y; // Se asignan las coordenadas y actuales del mouse al último punto en la lista points
        points[numPoints - 1].colorRed = currentColorRed; // Asigna el color actual al último punto en la lista points
        points[numPoints - 1].colorGreen = currentColorGreen;
        points[numPoints - 1].colorBlue = currentColorBlue;
    }

    glutPostRedisplay();
}



#endif
