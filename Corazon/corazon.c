#include <GL/glut.h>
#include <math.h>

// Funciones para obtener los valores de f(x) y g(x) para un valor dado de x
float f(float x) {
    return sqrt(1 - pow(fabs(x) - 1, 2));
}

float g(float x) {
    return acos(1 - fabs(x)) - M_PI;
}

// Función para dibujar el corazón
void drawHeart() {
    glBegin(GL_POINTS);

    // Dividir el corazón en varios puntos para una mejor apariencia
    int points = 100;
    float step = 2.0 / points;

    for (float x = -1; x <= 1; x += step) {
        glVertex2f(x, f(x));
    }

    for (float x = 1; x >= -1; x -= step) {
        glVertex2f(x, g(x));
    }

    glEnd();
}

// Función de renderizado
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);  // Color rojo

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -5.0);  // Ajustar la posición de la forma

    // Dibujar el corazón
    drawHeart();

    glutSwapBuffers();
}

// Función principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Corazón en OpenGL");
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Color de fondo blanco
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);  // Establecer la región de visualización
    glutDisplayFunc(renderScene);
    glutMainLoop();

    return 0;
}
