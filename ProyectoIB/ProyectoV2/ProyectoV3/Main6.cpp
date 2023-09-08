#define _USE_MATH_DEFINES 
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#define GRID_SIZE 20 // Tamaño de la cuadrícula en píxeles
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct Pixel {
    bool isPainted;
    float red;
    float green;
    float blue;
};

Pixel grid[WINDOW_WIDTH / GRID_SIZE][WINDOW_HEIGHT / GRID_SIZE]; // Cuadrícula para pintar

float currentColorRed = 0.0;
float currentColorGreen = 0.0;
float currentColorBlue = 0.0;

bool isDrawing = false;
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
void drawPixelAsCube(int x, int y) {
    // Dibuja un pequeño cubo en 3D para representar el pixel
    glColor3f(grid[x][y].red, grid[x][y].green, grid[x][y].blue);
    glPushMatrix();
    glTranslatef(x * GRID_SIZE - (WINDOW_WIDTH / 2), y * GRID_SIZE - (WINDOW_HEIGHT / 2), -GRID_SIZE / 2.0);
    glutSolidCube(GRID_SIZE);
    glPopMatrix();
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

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            // Acercar la cámara en Z (tecla "+")
            radious -= 5.0;
            break;
        case '-':
            // Alejar la cámara en Z (tecla "-")
            radious += 5.0;
            break;
        case 'r':
            currentColorRed = 1.0;
            currentColorGreen = 0.0;
            currentColorBlue = 0.0;
            break;
        case 'g':
            currentColorRed = 0.0;
            currentColorGreen = 1.0;
            currentColorBlue = 0.0;
            break;
        case 'b':
            currentColorRed = 0.0;
            currentColorGreen = 0.0;
            currentColorBlue = 1.0;
            break;
        case 'k':
            currentColorRed = 0.0;
            currentColorGreen = 0.0;
            currentColorBlue = 0.0;
            break;
        case 'm':
            currentColorRed = 1.0;
            currentColorGreen = 1.0;
            currentColorBlue = 0.0;
            break;
        case 'w':
            currentColorRed = 1.0;
            currentColorGreen = 1.0;
            currentColorBlue = 1.0;
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

void mouse(int button, int state, int x, int y) {
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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Añadir GLUT_DEPTH para habilitar el búfer de profundidad
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    mainWindow = glutCreateWindow("Pixel Art");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
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

