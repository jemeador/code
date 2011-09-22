/* viewing-look-1.c takes inward-looking tumble and turns it outward, which   */
/* produces a more video-game-like look-around interaction.                   */

#include <math.h>

#include "gl.h"
#include "cube.h"
#include "plane.h"

/*----------------------------------------------------------------------------*/

GLdouble rotation_x;
GLdouble rotation_y;
GLdouble position_x;                                                           \
GLdouble position_y;                                                           \
GLdouble position_z;                                                           \

GLdouble click_rotation_x;
GLdouble click_rotation_y;
GLdouble click_nx;
GLdouble click_ny;

cube  *C;
plane *P;                                                                      \

void startup(void)
{
    rotation_x =  0.0;
    rotation_y =  0.0;

    position_x =  0.0;                                                         \
    position_y =  2.0;                                                         \
    position_z =  5.0;                                                         \

    C =  cube_create();
    P = plane_create(20);                                                      \

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

    glRotated(rotation_x, 1.0, 0.0, 0.0);                                      \
    glRotated(rotation_y, 0.0, 1.0, 0.0);                                      \
    glTranslated(-position_x, -position_y, -position_z);                       \

    glPushMatrix();                                                            \
    {                                                                          \
        glDisable(GL_LIGHTING);                                                \
        plane_render(P);                                                       \
                                                                               \
        glTranslated(0.0, 1.0, 0.0);                                           \
                                                                               \
        glEnable(GL_LIGHTING);                                                 \
        cube_render(C);                                                        \
    }                                                                          \
    glPopMatrix();                                                             \
    
    glutSwapBuffers();
}

/*----------------------------------------------------------------------------*/

void motion(int x, int y)
{
    GLdouble nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);
    GLdouble ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);

    GLdouble dx = nx - click_nx;
    GLdouble dy = ny - click_ny;

    rotation_x = click_rotation_x +  90.0 * dy;
    rotation_y = click_rotation_y + 180.0 * dx;

    if (rotation_x >   90.0) rotation_x  =  90.0;
    if (rotation_x <  -90.0) rotation_x  = -90.0;
    if (rotation_y >  180.0) rotation_y -= 360.0;
    if (rotation_y < -180.0) rotation_y += 360.0;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    click_nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);
    click_ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);

    click_rotation_x = rotation_x;
    click_rotation_y = rotation_y;
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
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    if (glewInit() == GLEW_OK)
    {
        startup();
        glutMainLoop();
    }
    return 0;
}
