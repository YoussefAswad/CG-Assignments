//  Includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//-----------------

//  Methods Signatures
void display();
//void reshape(int , int);
void timer(int);
void drawRect(int x, int y, int w, int h);
void drawCircle(int x, int y, float r);
//-----------------

//  Global Variables
int t = 0;
float playerX = 20;
float playerY = 0;
float xpos = 150;
float pipeColor[3] = {0, 1, 0};
float pipeColorAlt[3] = {1, 0, 0};
//-----------------

int main(int argc, char **argr)
{
	glutInit(&argc, argr);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Flappy Bird");

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	//glutReshapeFunc(reshape)
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0, 300.0, -100.0, 100.0);

	glutMainLoop();
}

void drawRect(int x, int y, int w, int h, float color[3])
{
	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	glVertex2f(x, y);
	glVertex2f(x, y - h);
	glVertex2f(x + w, y - h);
	glVertex2f(x + w, y);
	glEnd();
}

void drawCircle(int x, int y, float r)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric *quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

void drawPipeDown(int x, int h, float color[3])
{
	drawRect(x, -100 + h, 20, h, color);

	drawRect(x - 3, -100 + 10 + h, 26, 10, color);
}

void drawPipeUp(int x, int h, float color[3])
{
	drawRect(x, 100, 20, h, color);

	drawRect(x - 3, 100 - h, 26, 10, color);
}

void timer(int)
{
	glutPostRedisplay();
	t += 1000 / 60;
	glutTimerFunc(1000 / 60, timer, 0);

	xpos -= 0.5;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (xpos > 0)
	{
		glClearColor(1, 0, 0, 0);
	}
	else
	{
		glClearColor(0, 0, 1, 0);
	}

	drawCircle(playerX, playerY, 15);

	//glLoadIdentity();
	drawPipeDown(xpos, 40, pipeColor);

	drawPipeUp(xpos, 40, pipeColor);
	glutSwapBuffers();
}

/*
void reshape(int w , int h)
{
	glViewport();
}
*/