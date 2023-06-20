#include <GL/freeglut.h>

using namespace std;

/* GLOBAL VARIABLES */
/* ------------------------------------------------------- */
GLfloat rotAngle = 0.0f;   // rotational angle attribute
int refreshRateanim = 5;       // refresh interval [milliseconds]

/* CALLING METHODS */
/* ------------------------------------------------------- */
void displayanim();
void initGLanim();
void reshapeanim(GLsizei width, GLsizei height);
void drawCube();
void myTimeranim(int value);

/* MAIN */
/* ------------------------------------------------------- */
int main(int argc, char** argv) {
    setenv("DISPLAY", ":0", false);
    /* Initializing glut */
    glutInit(&argc, argv);

    /* Use single color buffer instead of a depth buffer */
    glutInitDisplayMode(GLUT_DOUBLE);

    /* Windows dimensions - width and height */
    glutInitWindowSize(900, 480);

    /* Location of window - screen coordinates */
    glutInitWindowPosition(100, 100);

    /* Sets the window object name */
    glutCreateWindow("COMPUTER GRAPHICS - GR1COM");

    /* Register callback handler for window re-size event */
    glutReshapeFunc(reshapeanim);

    /* Redraws the window */
    glutDisplayFunc(displayanim);

    /* OpenGL initialization */
    initGLanim();

    /* Timer is called */
    glutTimerFunc(0, myTimeranim, 0);

    /* Render loop */
    glutMainLoop();         // The program closes when user closes the window

    return 0;

}

/* METHODS */
/* ------------------------------------------------------- */

/* Initialize OpenGL Graphics */
void initGLanim() {
    glClearColor(0.180f, 0.251f, 0.341f, 1.0f);            // sets background color
    glClearDepth(1.0f);                                                               // sets background depth to farthest
    glEnable(GL_DEPTH_TEST);                                                          // enables depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                                                           // sets the type of depth-test
    glShadeModel(GL_SMOOTH);                                                          // enables smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);                                // perspective corrections
}

/* Draws the image on screen */
void displayanim() {

    /* Clears color and depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Create transformations */
    glMatrixMode(GL_MODELVIEW);                     // to operate on model-view matrix

    /* Cubes */
    glLoadIdentity();                               // make sure to initialize matrix to identity matrix first
    glTranslatef(0.0f, 0.0f, -6.0f);                // moves the object to the desired location
    glRotatef(rotAngle, 0.0f, 1.0f, 1.0f);          // rotate about (0, 1, 1) axis
    glScalef(0.8f, 0.8f, 0.8f);                     // scales the object x0.8 times
    drawCube();

    glLoadIdentity();
    glTranslatef(3.0f, 0.0f, -7.0f);                // moves the object to the desired location
    glRotatef(rotAngle, 1.0f, 1.0f, 0.0f);          // rotate about (1, 1, 0) axis
    glScalef(0.5f, 0.5f, 0.5f);                     // scales the object x0.5 times
    drawCube();

    glLoadIdentity();
    glTranslatef(-4.0f, 1.0f, -9.0f);               // moves the object to the desired location
    glRotatef(rotAngle, 1.0f, 1.0f, 0.0f);          // rotate about (1, 1, 0) axis
    glScalef(0.9f, 0.9f, 0.9f);                     // scales the object x0.5 times
    drawCube();

    /* Swaps the front and back buffers */
    glutSwapBuffers();

    /* Updates the rotational angle after each refresh */
    rotAngle += 0.15f;
}

void drawCube(){
    /* CUBE DRAWING */
    /* Default coordinate system, in which x, y, and z are limited to the range -1 to 1 */

    glBegin(GL_QUADS);
    /* Top face */
    glColor3f(0.965f, 0.847f, 0.682f);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1,  1,  1);
    glVertex3f(-1,  1, -1);

    glColor3f(1.000f, 0.500f, 0.000f);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1,  1, -1);

    glColor3f(0.000f, 0.482f, 1.000f);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1,  1);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1, -1, -1);

    glColor3f(0.855f, 0.255f, 0.404f);
    glVertex3f(-1,  1, -1);
    glVertex3f(-1,  1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1,  1, -1);

    glColor3f(0.957f, 0.827f, 0.369f);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1,  1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f( 1, -1, -1);

    glColor3f(1.000f, 0.745f, 0.392f);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1,  1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1, -1,  1);
    glEnd();
}

/* Called when timer expired */
void myTimeranim(int value) {
    glutPostRedisplay();                        // activates displayanim as a new request
    glutTimerFunc(refreshRateanim, myTimeranim, 0);     // calls the next timer
}

/* Handler for window re-size event */
void reshapeanim(GLsizei width, GLsizei height) {
    /* Compute aspect ratio of the new window */
    if (height == 0) {
        height = 1;
    }

    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    /* Sets the viewport to cover the new window*/
    glViewport(0, 0, width, height);

    /* Sets the aspect ratio of the clipping volume to match the viewport*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Enable perspective projection with fovy, aspect, zNear and zFar */
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
