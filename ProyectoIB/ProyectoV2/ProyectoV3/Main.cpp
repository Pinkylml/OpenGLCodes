#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void display();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void draw();
void pixel(int x, int y);


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
    glClearColor(0.5, 0.5, 0.5, 0.5); // Color de fondo gris
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(pixel); 
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
    glPointSize(18.0);
    draw();
    glFlush();

}



void draw() {
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
    case 'v': // Tecla 'g' para cambiar a color verde
        currentColorRed = 0.0;
        currentColorGreen = 1.0;
        currentColorBlue = 0.0;
        break;
    case 'a': // Tecla 'b' para cambiar a color azul
        currentColorRed = 0.0;
        currentColorGreen = 0.0;
        currentColorBlue = 1.0;
        break;
    case 'n': // Tecla 'k' para cambiar a color negro
        currentColorRed = 0.0;
        currentColorGreen = 0.0;
        currentColorBlue = 0.0;
        break;
    case 'm': // Tecla 'm' para cambiar a color amarillo
        currentColorRed = 1.0;
        currentColorGreen = 1.0;
        currentColorBlue = 0.0;
        break;
    case 'b': // Tecla 'w' para cambiar a color blanco
        currentColorRed = 1.0;
        currentColorGreen = 1.0;
        currentColorBlue = 1.0;
        break;
    case 'g': // Tecla 'w' para cambiar a color gris
        currentColorRed = 0.5;
        currentColorGreen = 0.5;
        currentColorBlue = 0.5;
        break;
        
    case 'p': // Tecla 'w' para cambiar a color piel
        currentColorRed = 1.0;
        currentColorGreen = 0.855;
        currentColorBlue = 0.725;
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
            pixel(x, y);
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


void pixel(int x, int y)
{
    if (isDrawing)
    {
        // Verificar que las coordenadas estén dentro de la cuadrícula
        if (x >= 0 && x < windowWidth && y >= 0 && y < windowHeight)
        {
            // Calcular las coordenadas normalizadas
            int normalizedX = (x / 20) * 20; // Redondear al múltiplo de 20 más cercano
            int normalizedY = (y / 20) * 20; // Redondear al múltiplo de 20 más cercano

            // Actualizar las coordenadas en la lista de puntos
            numPoints++;
            points = (Point*)realloc(points, numPoints * sizeof(Point));
            points[numPoints - 1].x = normalizedX;
            points[numPoints - 1].y = normalizedY;
            points[numPoints - 1].colorRed = currentColorRed; // Asigna el color actual al último punto en la lista points
            points[numPoints - 1].colorGreen = currentColorGreen;
            points[numPoints - 1].colorBlue = currentColorBlue;
        }
    }

    glutPostRedisplay();
}
