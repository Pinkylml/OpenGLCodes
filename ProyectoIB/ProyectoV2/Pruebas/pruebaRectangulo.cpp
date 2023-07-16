#include <iostream>
#include <GL/glut.h>

struct Point {
    int x;
    int y;
};

Point vertex1, vertex2;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(vertex1.x, vertex1.y);
    glVertex2f(vertex2.x, vertex1.y);
    glVertex2f(vertex2.x, vertex2.y);
    glVertex2f(vertex1.x, vertex2.y);
    glEnd();
    glFlush();


}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        vertex1.x = x;
        vertex1.y = glutGet(GLUT_WINDOW_HEIGHT) - y;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        vertex2.x = x;
        vertex2.y = glutGet(GLUT_WINDOW_HEIGHT) - y;

        glutPostRedisplay();
    }
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Draw Rectangle");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
