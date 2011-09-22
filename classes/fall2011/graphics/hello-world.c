#include <GL/glew.h>
#include <GLUT/glut.h>

static void reshape(int w, int h)
{
    GLdouble x = 0.5 * (GLdouble) w / (GLdouble) h;
    GLdouble y = 0.5;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-x, x, -y, y, 1.0, 10.0);

    glViewport(0, 0, w, h);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -5.0);

    glutSolidTeapot(1.0);
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInit(&argc, argv);

    glutCreateWindow(argv[0]);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    if (glewInit() == GLEW_OK)
        glutMainLoop();

    return 0;
}
