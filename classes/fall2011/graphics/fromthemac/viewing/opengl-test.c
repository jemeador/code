#include <stdio.h>
#include "gl.h"

/*----------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(100, 100);
    glutInit(&argc, argv);

    glutCreateWindow(argv[0]);

    printf("VENDOR     = %s\n", glGetString(GL_VENDOR));
    printf("RENDERER   = %s\n", glGetString(GL_RENDERER));
    printf("VERSION    = %s\n", glGetString(GL_VERSION));
    printf("EXTENSIONS = %s\n", glGetString(GL_EXTENSIONS));
    
    glutMainLoop();

    return 0;
}
