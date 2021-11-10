//  Includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//-----------------

//  Methods Signatures
void display();
//void reshape(int , int);
void timer();
void drawRect(int x, int y, int w, int h);
void drawCircle(int x, int y, float r);
//-----------------

int main(int argc, char **argr)
{
	glutInit(&argc, argr);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Flappy Bird");

	glutDisplayFunc(display);
	//glutReshapeFunc(reshape)
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(-150.0, 150.0, -100.0, 100.0);

	glutMainLoop();
}

void drawRect(int x, int y, int w, int h) {
  glBegin(GL_POLYGON);
  glVertex2f(x, y);
  glVertex2f(x + w, y);
  glVertex2f(x + w, y + h);
  glVertex2f(x, y + h);
  glEnd();
}

void drawCircle(int x, int y, float r) {
  glPushMatrix();
  glTranslatef(x, y, 0);
  GLUquadric *quadObj = gluNewQuadric();
  gluDisk(quadObj, 0, r, 50, 50);
  glPopMatrix();
}

void timer()
{

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//glLoadIdentity();


	glFlush();
}

/*
void reshape(int w , int h)
{
	glViewport();
}
*/