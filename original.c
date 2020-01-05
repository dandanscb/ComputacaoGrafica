/*
*   Computação Gráfica
*
* José Renato de Souza
* Rogério Teixeira Buzzato
*
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "png_texture.h"

//inicialização das variáveis

#define PI 3.1415
#define TEXTURA_DA_BASE "montanhas.png"
#define TEXTURA_DO_BRACO "fundo.png"
#define TEXTURA_DA_MAO "mao.png"
#define TEXTURA_DOS_DEDOS "dedos.png"
GLuint textura_base;
GLuint textura_braco;
GLuint textura_mao;
GLuint textura_dedos;
GLshort texturas = 1;

GLdouble obsX = 0, obsY = 0, obsZ = 5, fy = 0, fx = 0, fz = 0;
float bx = 0, by = 0.45, bz = 0;
GLfloat obs[3] = {0.0, 0.0, 0.0};
GLfloat look[3] = {0.0, 3.0, 1.0};

GLfloat tetaxz = 0;
GLfloat raioxz = 6;

int elbow = -45, oy = 0, shoulder = 45, dedo1 = 0, dedo2 = 0;

void carregar_texturas(void)
{
  textura_base = png_texture_load(TEXTURA_DA_BASE, NULL, NULL);
  textura_braco = png_texture_load(TEXTURA_DO_BRACO, NULL, NULL);
  textura_mao = png_texture_load(TEXTURA_DA_MAO, NULL, NULL);
  textura_dedos = png_texture_load(TEXTURA_DOS_DEDOS, NULL, NULL);
}
void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  carregar_texturas();

  glEnable(GL_TEXTURE_2D);
}

void special(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_UP:
    obs[1] = obs[1] + 1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
    obs[1] = obs[1] - 1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT:
    tetaxz = tetaxz + 2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    tetaxz = tetaxz - 2;
    glutPostRedisplay();
    break;
  }
}

void display(void)
{
  glDisable(GL_BLEND);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  if (texturas)
  {
    glEnable(GL_TEXTURE_2D);
  }
  else
  {
    glDisable(GL_TEXTURE_2D);
  }
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  glTranslatef(bx, -2, bz);

  //observador

  obs[0] = raioxz * cos(2 * PI * tetaxz / 360);
  obs[2] = raioxz * sin(2 * PI * tetaxz / 360);
  gluLookAt(obs[0], obs[1], obs[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);
  glBindTexture(GL_TEXTURE_2D, textura_base);
  //desenhar a base
  glColor3f(1, 0, 0);
  glTranslatef(bx, by + 0.5, bz);
  glPushMatrix();
  glScalef(2.0, 0.4, 2.0);
  glutSolidCube(1.0);
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, textura_braco);
  //primeiro braço
  glColor3f(1, 0, 1);
  glTranslatef(bx, by, bz);
  glRotatef((GLfloat)oy, 0, 1.0, 0);
  glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
  glRotatef((GLfloat)0, 0.5, 0.0, 0.0);
  glTranslatef(1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef(2.0, 0.4, 1.0);
  glutSolidCube(1.0);
  glPopMatrix();
  glColor3f(0, 0, 1);
  glTranslatef(1.0, 0.0, 0.0);
  glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
  glTranslatef(1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef(2.0, 0.4, 1.0);
  glutSolidCube(1.0);
  glPopMatrix();

  //desenha a mão
glBindTexture(GL_TEXTURE_2D, textura_mao);
  glPushMatrix();
  glColor3f(1, 0, 0.5);
  glTranslatef(0.7, -0.3, 0);
  glRotatef((GLfloat)180 - (elbow + shoulder), 0, 0, 1); // put palm down
  glPushMatrix();
  glScalef(0.8, 0.2, 0.8);
  glutSolidCube(1.0);
  glPopMatrix();

  //dedo 1
  glBindTexture(GL_TEXTURE_2D, textura_dedos);
  glColor3f(0, 0, 0);
  glPushMatrix();

  glTranslatef(0.0, 0.0, 0.0);
  glRotatef((GLfloat)90, 0.0, 0.0, 1.0);
  glRotatef((GLfloat)dedo1, 0.0, 0.0, 1.0);
  glTranslatef(0.15, 0.15, -0.25);
  glPushMatrix();
  glScalef(0.3, 0.1, 0.25);
  obsX -= 0.10;
  fx -= 0.10;
  glutSolidCube(1.0);
  glPopMatrix();
  glPopMatrix();

  //dedo 2
  glPushMatrix();
  glTranslatef(.0, 0.0, 0.0);
  glRotatef((GLfloat)90, 0.0, 0.0, 1.0);
  glRotatef((GLfloat)dedo1, 0.0, 0.0, 1.0);

  glTranslatef(0.15, 0.15, 0.25);
  glPushMatrix();
  glScalef(0.3, 0.1, 0.25);
  glutSolidCube(1.0);
  glPopMatrix();
  glPopMatrix();

  //dedo 3
  glPushMatrix();
  glTranslatef(.0, 0.0, 0.0);
  glRotatef((GLfloat)90, 0.0, 0.0, 1.0);
  glRotatef((GLfloat)dedo2, 0.0, 0.0, 1.0);
  glTranslatef(0.15, -0.15, -0.0);
  glPushMatrix();
  glScalef(0.3, 0.1, 0.25);
  glutSolidCube(1.0);
  glPopMatrix();
  glPopMatrix();

  glPopMatrix();

  glPopMatrix();
  glutSwapBuffers();
}
void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -5.0);
}

int oldObsX = 0;
int oldfX = 0;
int oldX = 0;
int oldY = 0;
int flag = 1;
void movimento(int x, int y)
{
  if (flag)
  {
    oldX = x;
    oldY = y;
    flag = !flag;
  }
  if (oldX > x)
  {
    printf("\nesquerda\n ");
    tetaxz = tetaxz - 1;
    glutPostRedisplay();
  }
  if (oldX < x)
  {
    printf("\ndireita\n ");
    tetaxz = tetaxz + 1;
    glutPostRedisplay();
  }
  if (oldY > y)
  {
    printf("\ncima\n ");
    printf("valor de raioxz: %f \n", raioxz);
    if (raioxz < 14)
      raioxz = raioxz + 0.5;
    glutPostRedisplay();
  }
  if (oldY < y)
  {
    printf("\nbaixo\n ");
    printf("valor de raioxz: %f \n", raioxz);
    if (raioxz > -1)
      raioxz = raioxz - 0.5;
    glutPostRedisplay();
  }
  oldY = y;
  oldX = x;
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'w':
    if (shoulder < 90)
    {
      shoulder = (shoulder + 5) % 360;
      by = by - 0.006;
    }
    glutPostRedisplay();
    break;
  case 's':
    if (shoulder > 32)
    {
      shoulder = (shoulder - 5) % 360;
      by = by + 0.006;
    }
    glutPostRedisplay();
    break;
  case 'q':
    if (elbow + shoulder < 0)
      elbow = (elbow + 5) % 360;
    glutPostRedisplay();
    break;
  case 'e':
    if (elbow + shoulder > -35)
      elbow = (elbow - 5) % 360;
    glutPostRedisplay();
    break;
  case 'a':
    oy = oy + 10;
    break;
  case 'd':
    oy = oy - 10;
    break;
  case 'z':
    if (dedo1 < 27)
      dedo1 = (dedo1 + 3) % 360;
    if (dedo2 > -27)
      dedo2 = (dedo2 - 3) % 360;
    glutPostRedisplay();
    break;
  case 'x':
    if (dedo1 > -27)
      dedo1 = (dedo1 - 3) % 360;
    if (dedo2 < 27)
      dedo2 = (dedo2 + 3) % 360;
    glutPostRedisplay();
    break;
  case 't':
    texturas = !texturas;
    glutPostRedisplay();
    break;
  case 'r':
    if (raioxz < 14)
      raioxz = raioxz + 1;
    glutPostRedisplay();
    break;
  case 'R':
    raioxz = raioxz - 1;
    if (raioxz == 0)
    {
      raioxz = 1;
    }
    glutPostRedisplay();
    break;

  case 27:
    exit(0);
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutKeyboardFunc(keyboard);
  // glutMouseFunc(GerenciaMouse);
  glutMotionFunc(movimento);
  glutMainLoop();
  return 0;
}
