#define _USE_MATH_DEFINES 
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#define GRID_SIZE 20 // Tamaño de la cuadrícula en píxeles
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void display();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouse2(int button, int state, int x, int y);
void draw();
void pixel(int x, int y);
#define GRID_SIZE 20 // Tamaño de la cuadrícula en píxeles
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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
struct Pixel {
    bool isPainted;
    float red;
    float green;
    float blue;
};

bool is3DView = false;
int mainWindow, subWindow;
void timer(int valor);
void moverCamara(int key,int,int);
void orbitCamara(int key, int, int);
void orbitCamara2(int key, int, int);
int refreshRate = 5;
float rotAng = 0.0f;
float camX = 50.0f, camY = 50.0f, camZ= 50.0f;
float cameraSpeed = 0.1f;
float centerX = 150.0f, centerY = 150.0f;
float orbitAng = 0.0f;
float radious = 50.0;
float angleX = 0.0f, angleY = 0.0f;
Pixel grid[WINDOW_WIDTH / GRID_SIZE][WINDOW_HEIGHT / GRID_SIZE]; // Cuadrícula para pintar


void drawPixelAsCube(int x, int y) {
    // Dibuja un pequeño cubo en 3D para representar el pixel
    glColor3f(grid[x][y].red, grid[x][y].green, grid[x][y].blue);
    glPushMatrix();
    glTranslatef(x * GRID_SIZE - (WINDOW_WIDTH / 2), y * GRID_SIZE - (WINDOW_HEIGHT / 2), -GRID_SIZE / 2.0);
    glutSolidCube(GRID_SIZE);
    glPopMatrix();
}


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
    glutMouseFunc(mouse);
    glutMouseFunc(mouse2);
    glutSpecialFunc(orbitCamara2);

    // Crea la ventana 3D pero no la muestra inicialmente
        // Crea la ventana 3D pero no la muestra inicialmente
    subWindow = glutCreateWindow("Pixel Art 3D");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
     glutSpecialFunc(orbitCamara2);
    glutHideWindow(); // Oculta la ventana 3D inicialmente
    
    glutMainLoop();

    return 0;
}


void display() {
    if (is3DView) {
        // Configura la vista 3D
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 10000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float camPosX = radious * sin(angleY) * cos(angleX);
        float camPosZ = radious * cos(angleY) * cos(angleX);
        float campPosY = radious * sin(angleX);
        //gluLookAt(20.0, 20.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        float upY = 1.0;
        if (angleX > M_PI / 2 && angleX < 3 * M_PI / 2)
            upY = -1;
        if (angleX < -M_PI / 2 && angleX > -3 * M_PI / 2)
            upY = -1;
        gluLookAt(camPosX, campPosY, camPosZ, centerX, centerY, 0, 0, upY, 0);

        // Dibuja el contenido de la cuadrícula en 3D
        for (int x = 0; x < WINDOW_WIDTH / GRID_SIZE; x++) {
            for (int y = 0; y < WINDOW_HEIGHT / GRID_SIZE; y++) {
                if (grid[x][y].isPainted) {
                    drawPixelAsCube(x, y);
                }
            }
        }

        glutSwapBuffers();
    } else {
        // Configura la vista 2D
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Dibuja la cuadrícula en 2D
        glColor3f(0, 0, 0);
        glLineWidth(1.0);

        glBegin(GL_LINES);
        for (int x = 0; x <= WINDOW_WIDTH; x += GRID_SIZE) {
            glVertex2i(x, 0);
            glVertex2i(x, WINDOW_HEIGHT);
        }
        for (int y = 0; y <= WINDOW_HEIGHT; y += GRID_SIZE) {
            glVertex2i(0, y);
            glVertex2i(WINDOW_WIDTH, y);
        }
        glEnd();
        glPointSize(18.0);
        draw();
        glFlush();
        // Dibuja el contenido de la cuadrícula en 2D
        for (int x = 0; x < WINDOW_WIDTH / GRID_SIZE; x++) {
            for (int y = 0; y < WINDOW_HEIGHT / GRID_SIZE; y++) {
                if (grid[x][y].isPainted) {
                    glColor3f(grid[x][y].red, grid[x][y].green, grid[x][y].blue);
                    glBegin(GL_QUADS);
                    glVertex2i(x * GRID_SIZE, y * GRID_SIZE);
                    glVertex2i((x + 1) * GRID_SIZE, y * GRID_SIZE);
                    glVertex2i((x + 1) * GRID_SIZE, (y + 1) * GRID_SIZE);
                    glVertex2i(x * GRID_SIZE, (y + 1) * GRID_SIZE);
                    glEnd();
                }
            }
        }

        glutSwapBuffers();
    }
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
    case '+':
        // Acercar la cámara en Z (tecla "+")
        radious -= 5.0;
        break;
    case '-':
        // Alejar la cámara en Z (tecla "-")
        radious += 5.0;
        break;
    case 't':
            // Cambiar entre vista 2D y 3D aquí
            is3DView = !is3DView;
            glutSetWindow(subWindow);
            glutPostRedisplay();
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

void mouse2(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Calcula la celda en la cuadrícula según la posición del mouse
        int gridX = x / GRID_SIZE;
        int gridY = (WINDOW_HEIGHT - y) / GRID_SIZE;

        // Solo cambia el estado de la celda (pinta o borra) si no está pintada
        if (!grid[gridX][gridY].isPainted) {
            grid[gridX][gridY].isPainted = true;
            grid[gridX][gridY].red = currentColorRed;
            grid[gridX][gridY].green = currentColorGreen;
            grid[gridX][gridY].blue = currentColorBlue;
        }

        glutPostRedisplay();
    }
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
