/* viewing-hello-cube.c initializes GLUT and GLEW state and renders a cube    */
/* without any intertivity.                                                   */

#include <math.h>

#include "gl.h"
#include "cube.h"

/*----------------------------------------------------------------------------*/

cube *C;                                                                       \
                                                                               \
void startup(void)                                                             \
{                                                                              \
    C = cube_create();                                                         \
                                                                               \
    glEnable(GL_DEPTH_TEST);                                                   \
    glEnable(GL_LIGHTING);                                                     \
    glEnable(GL_LIGHT0);                                                       \
                                                                               \
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);                                      \
}                                                                              \

/*----------------------------------------------------------------------------*/

void reshape(int w, int h)
{
    GLdouble tb = 0.5;                                                         \
    GLdouble lr = 0.5 * (GLdouble) w / (GLdouble) h;                           \
                                                                               \
    glMatrixMode(GL_PROJECTION);                                               \
    glLoadIdentity();                                                          \
    glFrustum(-lr, lr, -tb, tb, 1.0, 100.0);                                   \
                                                                               \
    glViewport(0, 0, w, h);                                                    \
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -5.0);

    cube_render(C);                                                            \

    glutSwapBuffers();
}

/*----------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInit(&argc, argv);

    glutCreateWindow(argv[0]);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    if (glewInit() == GLEW_OK)                                                 \
    {                                                                          \
        startup();                                                             \
        glutMainLoop();                                                        \
    }                                                                          \
    return 0;
}
