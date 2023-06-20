#include <GL/freeglut.h>
#include <math.h>

// Variables para la órbita
float orbitRadius = 0.5f;
float orbitSpeed = 0.02f;
float orbitAngle = 0.0f;

// Variables para la pelota
float ballRadius = 0.05f;
float ballAngle = 0.0f;

void drawBall(float x, float y)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo

    // Centro de la pelota
    glVertex2f(x, y);

    // Puntos para dibujar la pelota (círculo)
    int numSegments = 100;
    float angleStep = 2.0f * 3.14159f / numSegments;

    for (int i = 0; i <= numSegments; ++i)
    {
        float angle = i * angleStep + ballAngle;
        float posX = ballRadius * cos(angle) + x;
        float posY = ballRadius * sin(angle) + y;
        glVertex2f(posX, posY);
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.0f); // Trasladar hacia el centro de la pantalla

    // Calcular la posición de la pelota en la órbita
    float ballX = orbitRadius * cos(orbitAngle);
    float ballY = orbitRadius * sin(orbitAngle);

    // Dibujar la pelota
    drawBall(ballX, ballY);

    // Actualizar el ángulo de la órbita y la rotación de la pelota
    orbitAngle += orbitSpeed;
    ballAngle += 0.05f; // Velocidad de rotación de la pelota

    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pelota en órbita con rotación");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display); // Llamar a display() continuamente cuando no hay eventos
    glutMainLoop();

    return 0;
}
