#include <GL/freeglut.h>

void reshape(GLint w, GLint h);
void initGL();
void display3D();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ejercicio transformaciones 3D");
  
    glutDisplayFunc(display3D);
    glutReshapeFunc(reshape);
    initGL();
    glutMainLoop();

}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1, 5, 100);
}

void initGL() {
    glClearColor(0.8f,0.8f,0.8f,1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1, 5, 100);
}

void display3D() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    glScalef(2, 2, 2);
   // glTranslatef(-2, 0, 0);
    glBegin(GL_TRIANGLES);

    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glColor3f(1, 0, 1);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(1, 1, 0);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0, 1, 1);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0, 1, 0);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0, 1, 1);
    glVertex3f(1.0f, -1.0f, 1.0f);
    
    glEnd();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(2, 0, 0);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}
