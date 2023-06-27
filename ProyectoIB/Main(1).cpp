#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void display();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);



/*Define la estructura Point, que representa un punto en coordenadas x e y*/
typedef struct Point {
    int x;
    int y;
} Point;

int windowWidth = 800;
int windowHeight = 600;

bool isDrawing = false;
Point* points = NULL;
int numPoints = 0;

float pointColorRed = 1.0;
float pointColorGreen = 1.0;
float pointColorBlue = 1.0;


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Dibujar figura con el mouse");
    glClearColor(0.0, 0.0, 0.0, 0.0); // Color de fondo negro
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

    glColor3f(pointColorRed, pointColorGreen, pointColorBlue);
    glPointSize(5.0);

    /*Dibuja cada punto almacenado en la lista points en la ventana OpenGL*/
    glBegin(GL_POINTS);
      /* points[i].x representa la coordenada x del punto actual en la iteración*/
     /* windowHeight - points[i].y se utiliza para invertir la coordenada y del punto actual en la iteración*/  
    for (int i = 0; i < numPoints; i++)
    {
        glVertex2i(points[i].x, windowHeight - points[i].y);
    }
    glEnd();

    glFlush();
}


/*Cambia los colores*/
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r': // Tecla 'r' para cambiar a color rojo
        pointColorRed = 1.0;
        pointColorGreen = 0.0;
        pointColorBlue = 0.0;
        break;
    case 'g': // Tecla 'g' para cambiar a color verde
        pointColorRed = 0.0;
        pointColorGreen = 1.0;
        pointColorBlue = 0.0;
        break;
    case 'b': // Tecla 'b' para cambiar a color azul
        pointColorRed = 0.0;
        pointColorGreen = 0.0;
        pointColorBlue = 1.0;
        break;
    case 'w': // Tecla 'w' para cambiar a color blanco
        pointColorRed = 1.0;
        pointColorGreen = 1.0;
        pointColorBlue = 1.0;
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
        points = (Point*)realloc(points, numPoints * sizeof(Point));//Redimensiona dinámicamente el arreglo de puntos points
        points[numPoints - 1].x = x; //Se asignan las coordenadas x actuales del mouse al último punto en la lista points
        points[numPoints - 1].y = y; //Se asignan las coordenadas y actuales del mouse al último punto en la lista points
    }

    glutPostRedisplay();
}