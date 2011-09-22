
#include <stdio.h>
#include <stdlib.h>
#include "gl.h"
#include "input.h"

struct model *m;
static float rotAngleY = 0.;
static float rotAngleX = 0.;
static float zoom = 1.0;
static GLdouble x,y;

void init(int argc, char **argv) {
  if (argc == 1) {
    printf("usage: %s <model.mesh>\n", argv[0]);
    exit(0);
  }

  m = malloc(sizeof(struct model));
  readModel(argv[1], m);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glGenBuffers(1, &(m->vbo));
  glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
  //glBufferData(GL_ARRAY_BUFFER, sizeof(struct vert) * m->numVerts, m->vn, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vert), m->vn, GL_STATIC_DRAW);

  glGenBuffers(1, &(m->ebo));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(struct elem) * m->numElems , m->e, GL_STATIC_DRAW);

  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);


  //glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

}

void renderModel(struct model *n) {
  const size_t sz = sizeof (GLfloat);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER,         n->vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, n->ebo);

  glVertexPointer(3, GL_FLOAT, sz * 6, (GLvoid *) 0);
  glNormalPointer(   GL_FLOAT, sz * 6, (GLvoid *) (sz * 3));

  //GLfloat md[] = { 0.8, 0.8, 0.8, 1.0 };
  //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, md);

  glDrawElements(GL_TRIANGLES, 3*n->numElems, GL_UNSIGNED_SHORT, (GLvoid *)0);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

static void reshape(int w, int h)
{
    x = 0.5 * (GLdouble) w / (GLdouble) h;
    y = 0.5;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-x, x, -y, y, 1.0, 100.0);

    glViewport(0, 0, w, h);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-x*zoom, x*zoom, -y*zoom, y*zoom, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(rotAngleY, 0.0, 0.1, 0.0);
    glRotatef(rotAngleX, 0.1, 0.0, 0.0);

    renderModel(m);

    glutSwapBuffers();
}

static void keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case 'a':
      rotAngleY += 20.;
      if (rotAngleY >= 360.) rotAngleY = 0.;
      glutPostRedisplay();   
      break;
    case 'd':
      rotAngleY -= 20.;
      if (rotAngleY <= 0.) rotAngleY = 360.;
      glutPostRedisplay();   
      break;
    case 'w':
      rotAngleX += 20.;
      if (rotAngleX >= 360.) rotAngleX = 0.;
      glutPostRedisplay();   
      break;
    case 's':
      rotAngleX -= 20.;
      if (rotAngleX <= 0.) rotAngleX = 360.;
      glutPostRedisplay();   
      break;
    case 27: /* Escape Key */
      exit(0);
      break;
    case '+':
    case '=':
      // Zoom in
      zoom -= 0.1;
      glutPostRedisplay();   
      break;
    case '-':
      // Zoom out
      zoom += 0.1;
      glutPostRedisplay();   
      break;
    default:
      printf("key: %d %c\n", key, key);
      fflush(stdout);
      break;
  }
}

static void motion(int x, int y)                                                      
{                                                                              
    GLdouble nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);                   
    GLdouble ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);                  
                                                                               
    rotAngleX =  90.0 * (2.0 * ny - 1.0);                                     
    rotAngleY = 180.0 * (2.0 * nx - 1.0);                                     
                                                                               
    glutPostRedisplay();                                                       
}

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInit(&argc, argv);

    glutCreateWindow(argv[0]);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);  


    if (glewInit() == GLEW_OK) {
      init(argc, argv);
      glutMainLoop();
    }

    return 0;
}
