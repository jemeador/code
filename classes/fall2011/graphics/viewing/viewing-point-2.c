/* viewing-point-2.c maps the eye space pointer vector into world space,      */
/* which enables direct interaction with the world itself.                    */

#include <math.h>

#include "gl.h"
#include "key.h"
#include "cube.h"
#include "plane.h"

/*----------------------------------------------------------------------------*/

int      last_time;

GLdouble distance_near;
GLdouble distance_far;

GLdouble zoom;
GLdouble rotation_x;
GLdouble rotation_y;
GLdouble position_x;
GLdouble position_y;
GLdouble position_z;

GLdouble keyboard_dx;
GLdouble keyboard_dy;
GLdouble keyboard_dz;

GLdouble cube_x;                                                               \
GLdouble cube_y;                                                               \
GLdouble cube_z;                                                               \

GLdouble click_rotation_x;
GLdouble click_rotation_y;
GLdouble click_nx;
GLdouble click_ny;

cube  *C;
plane *P;

void startup(void)
{
    last_time   = 0;

    distance_near =   1.0;
    distance_far  = 100.0;

    zoom        = 0.5;
    rotation_x  = 0.0;
    rotation_y  = 0.0;

    position_x  = 0.0;
    position_y  = 2.0;
    position_z  = 5.0;
    
    keyboard_dx = 0.0;
    keyboard_dy = 0.0;
    keyboard_dz = 0.0;
    
    cube_x      = 0.0;                                                         \
    cube_y      = 1.0;                                                         \
    cube_z      = 0.0;                                                         \
    
    C =  cube_create();
    P = plane_create(20);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

/*----------------------------------------------------------------------------*/

void keyboardup(unsigned char key, int x, int y)
{
    switch (key)
    {
        case KEY_L: keyboard_dx += 1.0; break;
        case KEY_R: keyboard_dx -= 1.0; break;
        case KEY_D: keyboard_dy += 1.0; break;
        case KEY_U: keyboard_dy -= 1.0; break;
        case KEY_F: keyboard_dz += 1.0; break;
        case KEY_B: keyboard_dz -= 1.0; break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case KEY_L: keyboard_dx -= 1.0; break;
        case KEY_R: keyboard_dx += 1.0; break;
        case KEY_D: keyboard_dy -= 1.0; break;
        case KEY_U: keyboard_dy += 1.0; break;
        case KEY_F: keyboard_dz -= 1.0; break;
        case KEY_B: keyboard_dz += 1.0; break;
    }
}

/*----------------------------------------------------------------------------*/

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void display(void)
{
    GLdouble tb = zoom;
    GLdouble lr = zoom * glutGet(GLUT_WINDOW_WIDTH)
                       / glutGet(GLUT_WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-lr, lr, -tb, tb, distance_near, distance_far);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotated(rotation_x, 1.0, 0.0, 0.0);
    glRotated(rotation_y, 0.0, 1.0, 0.0);
    glTranslated(-position_x, -position_y, -position_z);

    glPushMatrix();
    {
        glDisable(GL_LIGHTING);
        plane_render(P);

        glTranslated(cube_x, cube_y, cube_z);                                  \

        glEnable(GL_LIGHTING);
        cube_render(C);
    }
    glPopMatrix();
    
    glutSwapBuffers();
}

/*----------------------------------------------------------------------------*/

void click(int x, int y)                                                       \
{                                                                              \
    GLdouble tb = zoom;                                                        \
    GLdouble lr = zoom * glutGet(GLUT_WINDOW_WIDTH)                            \
                       / glutGet(GLUT_WINDOW_HEIGHT);                          \
                                                                               \
    GLdouble M[16], k;                                                         \
    GLdouble ex, ey, ez;                                                       \
    GLdouble vx, vy, vz;                                                       \
                                                                               \
    /* Compute the eye space pointer vector. */                                \
                                                                               \
    ex =  (2.0 * x / glutGet(GLUT_WINDOW_WIDTH)  - 1.0) * lr;                  \
    ey = -(2.0 * y / glutGet(GLUT_WINDOW_HEIGHT) - 1.0) * tb;                  \
    ez = -distance_near;                                                       \
                                                                               \
    k = sqrt(ex * ex + ey * ey + ez * ez);                                     \
    ex /= k;                                                                   \
    ey /= k;                                                                   \
    ez /= k;                                                                   \
                                                                               \
    /* Compute the world space pointer vector. */                              \
                                                                               \
    glGetDoublev(GL_MODELVIEW_MATRIX, M);                                      \
                                                                               \
    vx = ex * M[ 0] + ey * M[ 1] + ez * M[ 2];                                 \
    vy = ex * M[ 4] + ey * M[ 5] + ez * M[ 6];                                 \
    vz = ex * M[ 8] + ey * M[ 9] + ez * M[10];                                 \
                                                                               \
    /* Compute the intersection of the pointer vector with the ground plane. */\
                                                                               \
    k = -position_y / vy;                                                      \
                                                                               \
    cube_x = position_x + vx * k;                                              \
    cube_z = position_z + vz * k;                                              \
}                                                                              \

void motion(int x, int y)
{
    GLdouble nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);
    GLdouble ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);

    GLdouble dx = nx - click_nx;
    GLdouble dy = ny - click_ny;

    rotation_x = click_rotation_x +  90.0 * dy * zoom;
    rotation_y = click_rotation_y + 180.0 * dx * zoom;

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

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)                     \
        click(x, y);                                                           \
}

/*----------------------------------------------------------------------------*/

void idle(void)
{
    GLdouble M[16], speed = 3.0;

    int curr_time = glutGet(GLUT_ELAPSED_TIME);

    GLdouble dt = (curr_time - last_time) / 1000.0;
    GLdouble kx = keyboard_dx * dt * speed;
    GLdouble ky = keyboard_dy * dt * speed;
    GLdouble kz = keyboard_dz * dt * speed;

    last_time = curr_time;

    glGetDoublev(GL_MODELVIEW_MATRIX, M);

    position_x += kx * M[ 0] + ky * M[ 1] + kz * M[ 2];
    position_y += kx * M[ 4] + ky * M[ 5] + kz * M[ 6];
    position_z += kx * M[ 8] + ky * M[ 9] + kz * M[10];

    glutPostRedisplay();
}

/*----------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInit(&argc, argv);

    glutCreateWindow(argv[0]);

    glutKeyboardUpFunc(keyboardup);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    
    glutIgnoreKeyRepeat(1);

    if (glewInit() == GLEW_OK)
    {
        startup();
        glutMainLoop();
    }
    return 0;
}
