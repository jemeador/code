
#include <stdlib.h>
#include <stdio.h>
#include "gl.h"
#include "time.h"

struct vert
{
  GLfloat v[3];
  GLfloat n[3];
  GLfloat c[3];
};

struct elem
{
  GLushort i[3];
};

struct vert * v;
struct elem * e;

size_t sizev, sizee;
GLuint vbo, ebo;

GLdouble rotation_x;
GLdouble rotation_y;
GLdouble position_z;

int click_button;     
int color_mode;
GLdouble click_rotation_x;
GLdouble click_rotation_y;
GLdouble click_position_z;
GLdouble click_nx;
GLdouble click_ny;


static void loadmesh(char * filename)
{
  FILE * fp;
  int a, b, j;
  fp = fopen(filename,"r");
  fscanf(fp, "%d %d\n", &a, &b);
  v = (struct vert *)malloc(a * sizeof(struct vert));
  e = (struct elem *)malloc(b * sizeof(struct elem));
  sizev= a;
  sizee = b;
  
  srand(time(NULL));
  for (j=0;j<a;j++)
  {
    fscanf(fp, "v %f %f %f %f %f %f\n", &(v[j].v[0]),&(v[j].v[1]),&(v[j].v[2]),&(v[j].n[0]),&(v[j].n[1]),&(v[j].n[2])); 
    //printf("v %f %f %f %f %f %f\n",  (v[j].v[0]), (v[j].v[1]),(v[j].v[2]),(v[j].n[0]),(v[j].n[1]),(v[j].n[2]));
    for (int l=0;l<3;l++)
      v[j].c[l] = 0.01f * (rand() % 100);
  }
  for (j=0;j<b;j++)
  {
    fscanf(fp, "t %hu %hu %hu\n", &(e[j].i[0]),&(e[j].i[1]),&(e[j].i[2]));
    //printf("t %hu %hu %hu\n", (e[j].i[0]),(e[j].i[1]),(e[j].i[2]));
  }
  fclose(fp);
}

static void reshape(int w, int h)
{
  GLdouble x = 0.5 * (GLdouble) w / (GLdouble) h;
  GLdouble y = 0.5;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-x, x, -y, y, 1.0, 10000.0);

  glViewport(0, 0, w, h);
}

static void display(void)
{
  size_t s = sizeof(GLfloat);
 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(0.0, 0.0, -position_z);
  glRotated(rotation_x, 1.0, 0.0, 0.0);
  glRotated(rotation_y, 0.0, 1.0, 0.0);

   
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glVertexPointer(3,GL_FLOAT,s*9,(GLvoid *)(0));
  glNormalPointer( GL_FLOAT,s*9,(GLvoid *)(s*3));
  glColorPointer(3,GL_FLOAT,s*9,(GLvoid *)(s*6));
  
  /*for (int j=0;j<sizee;j++)
  {
    glBegin(GL_TRIANGLES);
    for (int l=0;l<3;l++)
    {
      struct vert * vt = &v[e[j].i[l]];
      glColor3s(255/(l+1), 255/5, 255/(3-l));
      glVertex3f(vt->v[0],vt->v[1],vt->v[2]);
    }
    glEnd();
  }*/ 
  glDrawElements(GL_TRIANGLES, 3*sizee, GL_UNSIGNED_SHORT, 0);
  glutSwapBuffers();
}

void init(char * filename)
{ 
  rotation_x = 0.0;
  rotation_y = 0.0;
  position_z = 10.0;
  color_mode = 0;
  loadmesh(filename);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glGenBuffers(1,&vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vert) * sizev, v, GL_STATIC_DRAW);
  
  glGenBuffers(1,&ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(struct elem) * sizee, e, GL_STATIC_DRAW);
  /*glutSolidTeapot(1.0);*/
  /*glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);*/
}

/*----------------------------------------------------------------------------*/

void motion(int x, int y)
{
    GLdouble nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);
    GLdouble ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);

    GLdouble dx = nx - click_nx;
    GLdouble dy = ny - click_ny;

    if (click_button == GLUT_LEFT_BUTTON)                                      
    {                                                                          
        rotation_x = click_rotation_x +  90.0 * dy;                            
        rotation_y = click_rotation_y + 180.0 * dx;                            
                                                                              
        if (rotation_x >   90.0) rotation_x  =  90.0;                          
        if (rotation_x <  -90.0) rotation_x  = -90.0;                          
        if (rotation_y >  180.0) rotation_y -= 360.0;                          
        if (rotation_y < -180.0) rotation_y += 360.0;                          
    }                                                                          
    if (click_button == GLUT_RIGHT_BUTTON)                                     
    {                                                                         
        position_z = click_position_z + 5.0 * dy;                              
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    click_nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);
    click_ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);

    click_button     = button;                                                 \
    click_rotation_x = rotation_x;
    click_rotation_y = rotation_y;
    click_position_z = position_z;
}

void keyboard(unsigned char key, int x, int y)
{
  color_mode = (color_mode + 1)%5;
  glutPostRedisplay();
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
  glutKeyboardFunc(keyboard);

  if (glewInit() == GLEW_OK)
  {
    init(argv[1]);
    glutMainLoop();
  }

  return 0;
}
