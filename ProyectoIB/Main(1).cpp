#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void display();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void draw();

/*Define la estructura Point, que representa un punto en coordenadas x e y*/
typedef struct Point {
    int x;
    int y;
    float colorRed;
    float colorGreen;
    float colorBlue;
} Point;

int windowWidth = 800;
int windowHeight = 600;

bool isDrawing = false;
Point* points = NULL;
int numPoints = 0;

float defaultColorRed = 1.0;
float defaultColorGreen = 1.0;
float defaultColorBlue = 1.0;

float currentColorRed = 1.0;
float currentColorGreen = 1.0;
float currentColorBlue = 1.0;

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

    draw();

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

void draw()
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
