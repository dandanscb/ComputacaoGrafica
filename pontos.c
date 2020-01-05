#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);

#define AZUL 0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO 1.0, 1.0, 0.0
#define VERDE 0.0, 1.0, 0.0
#define CYAN 1.0, 0.0, 1.0
#define LARANJA 0.8, 0.6, 0.1
#define ROSEO 0.7, 0.1, 0.6
#define CINZA 0.6, 0.6, 0.6
int numVertices = 36;
int numFaces = 12;
static GLfloat vertices[216];

static GLubyte robo[12][4];

void carregaArquivo()
{
  FILE *f = fopen("base.txt", "r");
  // printf("\n abriu \n");
  int i, j;
  for (i = 0; i < numVertices*numFaces; i++)
  {
    
      fscanf(f, "%f ", &vertices[i]);
    
  }
  // printf("passou aqui");
  for (i = 0; i < numFaces; i++)
  {
    for (j = 0; j < 4; j++)
    {
      fscanf(f, "%f ", &robo[i][j]);
    }
  }
  // for(i = 0 ; i < numVertices; i++){
  //   for(j = 0; j < 6; j++){
  //    printf("%f ", vertices[i][j]);
  //   }
  //   printf("\n");
  // }
  // for(i = 0 ; i < numFaces; i++){
  //   for(j = 0; j < 4; j++){
  //    printf("%f ", vertices[i][j]);
  //   }
  //   printf("\n");
  // }

  fclose(f);
}

static int eixoy, eixox;
int largura, altura;

int main(int argc, char **argv)
{
  carregaArquivo();
  int i;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(256, 256);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  largura = w;
  altura = h;
}

void display(void)
{
  glPushMatrix();
  glRotatef((GLfloat)eixoy, 0.0, 1.0, 0.0);
  glRotatef((GLfloat)eixox, 1.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int i;
  glColor3f(AZUL); /* frente */
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(6, GL_FLOAT, 0, vertices);
  for (i = 0; i < numFaces; i++)
  {
    glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, robo[i]);
  }

  // glColor3f (AMARELO); /* esquerda */
  // glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, esquerdaIndices);

  // glColor3f (VERMELHO); /* tras */
  // glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, trasIndices);

  // glColor3f (VERDE); /* direita */
  // glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, direitaIndices);

  // glColor3f (CYAN); /* topo */
  // glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, topoIndices);

  // glColor3f (LARANJA); /* fundo */
  // glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, fundoIndices);

  // glColor3f (CINZA); /* triangulo */
  // glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, trianguloIndices);

  glDisableClientState(GL_VERTEX_ARRAY);

  glPopMatrix();
  glutSwapBuffers();
}

void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glOrtho(-50, 50, -50, 50, -50, 50);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27:
    exit(0);
    break;
  case 'a':
    printf("%d, %d\n", x, y);
    break;
  case 'y':
    eixoy = (eixoy + 5) % 360;
    glutPostRedisplay();
    break;
  case 'Y':
    eixoy = (eixoy - 5) % 360;
    glutPostRedisplay();
    break;
  case 'x':
    eixox = (eixox + 5) % 360;
    glutPostRedisplay();
    break;
  case 'X':
    eixox = (eixox - 5) % 360;
    glutPostRedisplay();
    break;
  case 'p':
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)largura / (GLfloat)altura, 20.0, 120.0);
    gluLookAt(0, 0, -90, 0, 0, 0, 0, 1, 0);
    glutPostRedisplay();
    break;
  case 'o':
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -50, 50);
    glutPostRedisplay();
    break;
  }
}
