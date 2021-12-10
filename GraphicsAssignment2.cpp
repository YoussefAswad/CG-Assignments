#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include <string>
using namespace std;

float rotAng;
double floorX = 7;
double floorZ = 8;
double playerX = 0;
double playerZ = 0;
double playerAng = 0;
double presentAng = 0;
double treeScale = 1;
double snowManAng = 0;
double torriGateScale = 1.1;
double camX = 0;
double camY = 0;
double camZ = 0;
bool collected[] = {false, false, false};
int timer = 30;

void drawFloor()
{
	glPushMatrix();
	glScaled(floorX, 0.02, floorZ);
	glColor3d(0.0, 1.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawTorus(int numc, int numt)
{
	int i, j, k;
	double s, t, x, y, z, twopi;

	twopi = 2 * 3.14;
	for (i = numc / 2; i < numc; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for (j = numt / 2; j <= numt; j++)
		{
			for (k = 1; k >= 0; k--)
			{
				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = ((1 + .1 * cos(s * twopi / numc)) * cos(t * twopi / numt)) + 1;
				y = (1 + .1 * cos(s * twopi / numc)) * sin(t * twopi / numt);
				z = .1 * sin(s * twopi / numc);
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
}

void drawToriiGate(double scale)
{

	glPushMatrix();

	glTranslated(0, 0, -(floorZ / 2));
	glScaled(scale, scale, scale);
	glColor3f(0.7, 0, 0);

	glPushMatrix();

	glTranslated(-0.7, 2, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.15, 0.15, 2, 800, 800);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.7, 2, 0);
	glRotated(90, 1, 0, 0);
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.15, 0.15, 2, 800, 800);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.6, 0);
	glScaled(1.4, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.1, 2.4, 0);
	glScaled(1.1, 0.5, 0.5);
	drawTorus(500, 140);
	glPopMatrix();

	glPopMatrix();
}

void drawSanta(double x, double z, double ang)
{

	glPushMatrix();

	glTranslated(x, 0, z);

	glRotated(ang, 0, 1, 0);

	glScaled(0.8, 0.8, 0.8);

	glPushMatrix();
	glTranslated(-0.25, 1, 0);
	glRotated(90, 1, 0, 0);
	glColor3d(1, 0, 0);
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.1, 0.1, 1, 800, 800);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 1, 0);
	glRotated(90, 1, 0, 0);
	glColor3d(1, 0, 0);
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.1, 0.1, 1, 800, 800);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.3, 0.1);
	glScaled(0.1, 1, 0.2);
	glColor3d(0, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.3, 0);
	glScaled(0.9, 1, 0.3);
	glColor3d(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2, 0);
	glColor3d(1, 1, 1);
	glutSolidSphere(0.26, 800, 800);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2.2, 0);
	glRotated(-90, 1, 0, 0);
	glColor3f(1, 0, 0);
	glutSolidCone(0.2, 0.5, 300, 300);
	glPopMatrix();
	glPopMatrix();
}

void drawTree(double x, double z, double scale)
{

	glPushMatrix();
	glTranslated(x, 0, z);
	glScaled(scale, scale, scale);
	glPushMatrix();
	glTranslated(0, 1, 0);
	glRotated(90, 1, 0, 0);
	glColor3f(0.7, 0, 0);
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.1, 0.1, 1, 800, 800);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.5, 0);
	glRotated(-90, 1, 0, 0);
	glColor3f(0, 0.9, 0);
	glutSolidCone(0.35, 0.7, 300, 300);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.7, 0);
	glRotated(-90, 1, 0, 0);
	glColor3f(0, 0.8, 0);
	glutSolidCone(0.3, 0.7, 300, 300);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1, 0);
	glRotated(-90, 1, 0, 0);
	glColor3f(0, 0.9, 0);
	glutSolidCone(0.2, 0.5, 300, 300);
	glPopMatrix();

	glPopMatrix();
}

void drawPresent(double x, double z, double ang)
{

	glPushMatrix();
	glTranslated(x, 0, z);
	glRotated(ang, 0, 1, 0);
	glScaled(0.7, 0.7, 0.7);

	glPushMatrix();
	glTranslated(0, 0.25, 0);
	glScaled(1, 0.5, 1);
	glColor3d(1.0, 0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, 0.75, 0);
	glScaled(0.5, 0.3, 1);
	glColor3d(0, 0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 0.75, 0);
	glScaled(0.5, 0.3, 1);
	glColor3d(0, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.05, 0);
	glScaled(0.5, 0.3, 1);
	glColor3d(0, 0.5, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
}

void drawFence(double x, double z)
{
	glPushMatrix();
	glTranslated(x, 0, z);
	glScaled(0.2, 2, 0.5);
	glColor3d(1.0, 1.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawSnowMan(double x, double z, double ang)
{
	glPushMatrix();

	glTranslated(x, 0, z);

	glRotated(ang, 0, 1, 0);

	glScaled(0.7, 0.7, 0.7);

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0, 0.25, 0);
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0, 0.8, 0);
	glutSolidSphere(0.35, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0, 1.2, 0);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glRotated(30, 0, 1, 0);
	glTranslated(0, 1.1, 0.1);
	glColor3f(0.6, 0.5, 0);
	glutSolidCone(0.1, 0.2, 300, 300);
	glPopMatrix();
	glPopMatrix();
}
void drawFenceRotateX(double x, double z)
{
	glPushMatrix();
	glTranslated(x, 0.5, z);
	glRotated(90, 1, 0, 0);
	glScaled(0.2, 2, 0.5);
	glColor3d(1.0, 1.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawFences()
{
	drawFence((floorX / 2.0f) - 0.1, -((floorZ / 2.0f) - 0.25));
	drawFence(-(floorX / 2.0f) + 0.1, -((floorZ / 2.0f) - 0.25));

	drawFenceRotateX((floorX / 2.0f) - 0.1, (floorZ / 3.0f));

	drawFence((floorX / 2.0f) - 0.1, -(floorZ / 4.0f));
	drawFence(-(floorX / 2.0f) + 0.1, -(floorZ / 4.0f));

	drawFence((floorX / 2.0f) - 0.1, 0);
	drawFence(-(floorX / 2.0f) + 0.1, 0);

	drawFence((floorX / 2.0f) - 0.1, (floorZ / 4.0f));
	drawFence(-(floorX / 2.0f) + 0.1, (floorZ / 4.0f));

	drawFence((floorX / 2.0f) - 0.1, (floorZ / 2.0f) - 0.25);
	drawFence(-(floorX / 2.0f) + 0.1, (floorZ / 2.0f) - 0.25);
}

void AnimPresent()
{
	presentAng += 5;

	glutPostRedisplay();
}

void AnimSnowMan()
{
	snowManAng -= 4;

	glutPostRedisplay();
}

void AnimTree()
{
	if (treeScale >= 0.5 && treeScale < 1)
	{
		treeScale += 0.1;
	}
	else if (treeScale <= 1 && treeScale > 0.5)
	{
		treeScale -= 0.1;
	}

	glutPostRedisplay();
}

void AnimGate()
{

	if (torriGateScale >= 0.5 && torriGateScale < 1.1)
	{
		torriGateScale += 0.1;
	}
	else if (torriGateScale <= 1.1 && torriGateScale > 0.5)
	{
		torriGateScale -= 0.1;
	}

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	float d = 0.1;

	switch (key)
	{
	case 'w':
		if ((playerZ - 0.15) >= -(floorZ / 2) + 0.3)
		{
			playerZ -= 0.5;
			playerAng = 180;
		}
		break;
	case 's':
		if ((playerZ + 0.15) <= +(floorZ / 2) - 0.3)
		{
			playerZ += 0.5;
			playerAng = 0;
		}
		break;
	case 'a':
		if ((playerX - 0.15) >= -(floorX / 2) + 0.5)
		{
			playerX -= 0.5;
			playerAng = -90;
		}
		break;
	case 'd':
		if ((playerX + 0.15) <= +(floorX / 2) - 0.5)
		{
			playerX += 0.5;
			playerAng = 90;
		}
		break;
	case 'p':
		glutIdleFunc(AnimPresent);
		snowManAng = 0;
		treeScale = 1;
		torriGateScale = 1.1;
		break;
	case 'm':
		glutIdleFunc(AnimSnowMan);
		treeScale = 1;
		presentAng = 0;
		torriGateScale = 1.1;
		break;
	case 't':
		glutIdleFunc(AnimTree);
		snowManAng = 0;
		presentAng = 0;
		torriGateScale = 1.1;
		break;
	case 'g':
		glutIdleFunc(AnimGate);
		snowManAng = 0;
		presentAng = 0;
		treeScale = 1;
		break;
	case 'z':
		camZ -= 0.5;
		break;
	case 'x':
		camZ += 0.5;
		break;
	case '1':
		camX = 0;
		camY = -4;
		camZ = 0;
		break;
	case '2':
		camX = 8;
		camY = 0;
		camZ = -8;
		break;
	case '3':
		camY = 8;
		camX = 0;
		camZ = 0;
		break;
	}

	/*
	* 0.7 0.7
	drawPresent(-2, -3, presentAng);
	drawPresent(0, 3, presentAng);
	drawPresent(2.5, -3, presentAng);
	*/

	if (playerX < (-2 + 0.35) && playerX > (-2 - 0.35))
	{
		if (playerZ < (-3 + 0.35) && playerZ > (-3 - 0.35))
		{
			collected[0] = true;
		}
	}

	if (playerX < (0 + 0.35) && playerX > (0 - 0.35))
	{
		if (playerZ < (3 + 0.35) && playerZ > (3 - 0.35))
		{
			collected[1] = true;
		}
	}

	if (playerX < (2.5 + 0.35) && playerX > (2.5 - 0.35))
	{
		if (playerZ < (-3 + 0.35) && playerZ > (-3 - 0.35))
		{
			collected[2] = true;
		}
	}

	glutPostRedisplay();
}

void drawText(int x, int y, string s)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glColor3f(1, 0, 0);
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = s.length();

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	}
}

void Timer(int)
{
	glutPostRedisplay();
	timer -= 1;
	printf(timer + "");
	glutTimerFunc(1000, Timer, 0);
}

void setupCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1);
	gluPerspective(45.0f, 1.77777778, 0.1f, 300.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0 + camX, 5.0 + camY, 8.0 + camZ, 0.0, 0.0, 0.0, 0, 2.0, 0);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setupCamera();
	drawFences();
	drawSnowMan(2.5, 3, snowManAng);
	if (!collected[0])
	{
		drawPresent(-2, -3, presentAng);
	}

	if (!collected[1])
	{
		drawPresent(0, 3, presentAng);
	}
	if (!collected[2])
	{
		drawPresent(2.5, -3, presentAng);
	}
	drawToriiGate(torriGateScale);
	drawTree(-2, 0, treeScale);
	drawTree(-2, 2.5, treeScale);
	drawSanta(playerX, playerZ, playerAng);

	if (collected[0] && collected[1] && collected[2])
	{

		drawText(0, 0, "You Won!");
	}

	else if (timer <= 0)
	{
		drawText(0, 0, "You Lost!");
	}

	//drawText(3, 3, "Time Left" + timer);

	drawFloor();
	glFlush();
}

void Special(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_UP:
		camY += 0.5;
		break;
	case GLUT_KEY_DOWN:
		camY -= 0.5;
		break;
	case GLUT_KEY_LEFT:
		camX -= 0.5;
		camZ -= 0.5;
		break;
	case GLUT_KEY_RIGHT:
		camX += 0.5;
		camZ -= 0.5;
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("OpenGL - 3D Template");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	glutTimerFunc(0, Timer, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}
