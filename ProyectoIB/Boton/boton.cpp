#include <iostream>
#include <GL/freeglut.h>

bool opcion = false;
bool dibujandoRectangulo = false;
int punto1X, punto1Y, punto2X, punto2Y;

void display();
void reshape(GLint w, GLint h);
void mouse(int button, int state, int x, int y);

void dibujarRectangulo(int x1, int y1, int x2, int y2);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Botón y Rectángulo");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 640, 480, 0, -1, 1);

    if (opcion) {
        glColor3f(0.0f, 1.0f, 0.0f); // Opción activada: color verde
    } else {
        glColor3f(1.0f, 0.0f, 0.0f); // Opción desactivada: color rojo
    }

    // Dibujar un botón cuadrado en la esquina inferior derecha
    glBegin(GL_QUADS);
    glVertex2i(540, 380);
    glVertex2i(640, 380);
    glVertex2i(640, 480);
    glVertex2i(540, 480);
    glEnd();

    if (dibujandoRectangulo) {
        glColor3f(0.0f, 0.0f, 1.0f); // Color azul para el rectángulo dibujado
        dibujarRectangulo(punto1X, punto1Y, punto2X, punto2Y);
    }

    glFlush();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x >= 540 && x <= 640 && y >= 380 && y <= 480) {
            opcion = !opcion;
            dibujandoRectangulo = false;
            glutPostRedisplay();
        } else if (opcion && !dibujandoRectangulo) {
            punto1X = x;
            punto1Y = y;
            dibujandoRectangulo = true;
        } else if (opcion && dibujandoRectangulo) {
            punto2X = x;
            punto2Y = y;
            dibujandoRectangulo = false;
            glutPostRedisplay();
        }
    }
}

void dibujarRectangulo(int x1, int y1, int x2, int y2) {
    glBegin(GL_QUADS);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();
}

