#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define GRID_SIZE 20 // Tamaño de la cuadrícula en píxeles
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

bool grid[WINDOW_WIDTH / GRID_SIZE][WINDOW_HEIGHT / GRID_SIZE] = {false}; // Cuadrícula para pintar

float currentColorRed = 0.0;
float currentColorGreen = 0.0;
float currentColorBlue = 0.0;

bool isDrawing = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Dibuja la cuadrícula
    glColor3f(0, 0, 0); // Establece el color de la cuadrícula (blanco)
    glLineWidth(1.0); // Grosor de las líneas de la cuadrícula
    
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
    
    // Dibuja el contenido de la cuadrícula
    for (int x = 0; x < WINDOW_WIDTH / GRID_SIZE; x++) {
        for (int y = 0; y < WINDOW_HEIGHT / GRID_SIZE; y++) {
            if (grid[x][y]) {
                glColor3f(currentColorRed, currentColorGreen, currentColorBlue);
                glBegin(GL_QUADS);
                glVertex2i(x * GRID_SIZE, y * GRID_SIZE);
                glVertex2i((x + 1) * GRID_SIZE, y * GRID_SIZE);
                glVertex2i((x + 1) * GRID_SIZE, (y + 1) * GRID_SIZE);
                glVertex2i(x * GRID_SIZE, (y + 1) * GRID_SIZE);
                glEnd();
            }
        }
    }
    
    glutSwapBuffers(); // Utiliza glutSwapBuffers para evitar el parpadeo
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
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
    }
    
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Calcula la celda en la cuadrícula según la posición del mouse
        int gridX = x / GRID_SIZE;
        int gridY = (WINDOW_HEIGHT - y) / GRID_SIZE;
        
        // Cambia el estado de la celda (pinta o borra)
        grid[gridX][gridY] = !grid[gridX][gridY];
        
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Cambia a modo de doble búfer para evitar el parpadeo
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Pixel Art");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    
    return 0;
}
