#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define GRID_SIZE 20 // Tamaño de la cuadrícula en píxeles
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

bool is2DWindowOpen = true;

struct Cube {
    int x;
    int y;
    int size;
};

Cube cube = {2, 2, 5}; // Coordenadas y tamaño del cubo

float currentColorRed = 0.0;
float currentColorGreen = 0.0;
float currentColorBlue = 0.0;

bool isDrawing = false;

void drawCube() {
    glColor3f(currentColorRed, currentColorGreen, currentColorBlue);
    glBegin(GL_QUADS);
    // Cara frontal
    glVertex2i(cube.x * GRID_SIZE, cube.y * GRID_SIZE);
    glVertex2i((cube.x + cube.size) * GRID_SIZE, cube.y * GRID_SIZE);
    glVertex2i((cube.x + cube.size) * GRID_SIZE, (cube.y + cube.size) * GRID_SIZE);
    glVertex2i(cube.x * GRID_SIZE, (cube.y + cube.size) * GRID_SIZE);
    // Cara posterior
    glVertex2i(cube.x * GRID_SIZE, cube.y * GRID_SIZE);
    glVertex2i((cube.x + cube.size) * GRID_SIZE, cube.y * GRID_SIZE);
    glVertex2i((cube.x + cube.size) * GRID_SIZE, (cube.y - cube.size) * GRID_SIZE);
    glVertex2i(cube.x * GRID_SIZE, (cube.y - cube.size) * GRID_SIZE);
    // Conexiones entre caras
    glVertex2i(cube.x * GRID_SIZE, cube.y * GRID_SIZE);
    glVertex2i(cube.x * GRID_SIZE, (cube.y - cube.size) * GRID_SIZE);
    glVertex2i((cube.x + cube.size) * GRID_SIZE, (cube.y - cube.size) * GRID_SIZE);
    glVertex2i((cube.x + cube.size) * GRID_SIZE, cube.y * GRID_SIZE);
    glEnd();
}

void display2D() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Dibuja la cuadrícula
    glColor3f(0, 0, 0); // Establece el color de la cuadrícula (negro)
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
    
    // Dibuja el cuadrado
    drawCube();
    
    glutSwapBuffers(); // Utiliza glutSwapBuffers para evitar el parpadeo
}

void display3D() {
    // Configura la ventana en 3D y dibuja el cubo aquí
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0); // Configura una proyección en perspectiva
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Configura la posición de la cámara
    
    // Dibuja el cubo en 3D
    glPushMatrix();
    glColor3f(currentColorRed, currentColorGreen, currentColorBlue);
    glTranslatef(cube.x, cube.y, 0.0); // Traslada el cubo a las coordenadas deseadas
    glutSolidCube(cube.size); // Dibuja el cubo
    glPopMatrix();
    
    glutSwapBuffers();
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
        case 't':
            // Cambia entre la ventana 2D y 3D
            is2DWindowOpen = !is2DWindowOpen;
            if (is2DWindowOpen) {
                glutSetWindow(1); // Cambia a la ventana 2D
            } else {
                glutSetWindow(2); // Cambia a la ventana 3D
            }
            break;
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Agrega modo de profundidad
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Cuadrado en Perspectiva 2D");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display2D);
    glutKeyboardFunc(keyboard);
    
    // Crea una segunda ventana en 3D
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Cubo en Perspectiva 3D");
    glutDisplayFunc(display3D);
    
    glEnable(GL_DEPTH_TEST); // Habilita la prueba de profundidad
    
    glutMainLoop();
    
    return 0;
}
