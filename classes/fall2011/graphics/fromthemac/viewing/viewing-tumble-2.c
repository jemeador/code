/* viewing-tumble-2.c adds interactivity by mapping mouse drag events onto    */
/* relative changes to the orientation of the cube.                           */

#include <math.h>

#include "gl.h"
#include "cube.h"

/*----------------------------------------------------------------------------*/

GLdouble rotation_x;
GLdouble rotation_y;
GLdouble position_z;

GLdouble click_rotation_x;                                                     \
GLdouble click_rotation_y;                                                     \
GLdouble click_nx;                                                             \
GLdouble click_ny;                                                             \

cube *C;

void startup(void)
{
    rotation_x = 0.0;
    rotation_y = 0.0;
    position_z = 5.0;

    C = cube_create();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

/*----------------------------------------------------------------------------*/

void reshape(int w, int h)
{
    GLdouble tb = 0.5;
    GLdouble lr = 0.5 * (GLdouble) w / (GLdouble) h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-lr, lr, -tb, tb, 1.0, 100.0);

    glViewport(0, 0, w, h);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(0.0, 0.0, -position_z);
    glRotated(rotation_x, 1.0, 0.0, 0.0);
    glRotated(rotation_y, 0.0, 1.0, 0.0);

    cube_render(C);

    glutSwapBuffers();
}

/*----------------------------------------------------------------------------*/

void motion(int x, int y)
{
    GLdouble nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);
    GLdouble ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);

    GLdouble dx = nx - click_nx;                                               \
    GLdouble dy = ny - click_ny;                                               \
                                                                               \
    rotation_x = click_rotation_x +  90.0 * dy;                                \
    rotation_y = click_rotation_y + 180.0 * dx;                                \

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)                                \
{                                                                              \
    click_nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);                      \
    click_ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);                     \
                                                                               \
    click_rotation_x = rotation_x;                                             \
    click_rotation_y = rotation_y;                                             \
}                                                                              \

/*----------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInit(&argc, argv);

    glutCreateWindow(argv[0]);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);                                                      \

    if (glewInit() == GLEW_OK)
    {
        startup();
        glutMainLoop();
    }
    return 0;
}
