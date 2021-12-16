//  Includes

#include <stdio.h>
#include <random>
#include <string>
#include <algorithm>
#include <GL/glut.h>
#include <iostream>

using namespace std;
//-----------------

//  Methods Signatures
void display();
void reshape(int, int);
void Key(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void timer(int);
void drawRect(int x, int y, int w, int h);
void drawCircle(int x, int y, float r);
//-----------------

//  Global Variables
int t = 0;

float s = 10;
float playerX = 28;
float playerY = 0;
float xpos = 180;

bool win = false;
bool lose = false;
bool power = false;
float powerT = 0;
int powerP;
float powerX;

int lives = 3;

float pipes[3][3] = {{90, 120, 150}, {150, 120, 90}, {100, 100, 100}};
int p[3] = {0, 1, 2};

float pipeColor[3] = {0, 1, 0};
float pipeColorAlt[3] = {1, 0, 0};
//-----------------

struct RNG
{
	int operator()(int n)
	{
		return std::rand() / (1.0 + RAND_MAX) * n;
	}
};

int main(int argc, char **argr)
{
	glutInit(&argc, argr);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	std::random_device r;
	std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
	std::mt19937 eng(seed);

	std::shuffle(std::begin(p), std::end(p), eng);
	srand(time(0));
	powerP = (rand() % 2) + 1;
	powerX = powerP * 200;
	for (auto a : p)
		cout << a;

	cout << powerX;
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Flappy Bird");

	glutDisplayFunc(display);

	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);

	glutTimerFunc(0, timer, 0);
	glutReshapeFunc(reshape);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();
}

void drawRect(float x, float y, float w, float h, float color[3])
{
	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	glVertex2f(x, y);
	glVertex2f(x, y - h);
	glVertex2f(x + w, y - h);
	glVertex2f(x + w, y);
	glEnd();
}

void drawPower(float s)
{

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(powerX + xpos - s / 2, -(3 * s / 2));
	glVertex2f(powerX + xpos + s / 2, -(3 * s / 2));
	glVertex2f(powerX + xpos + s / 2, +(3 * s / 2));
	glVertex2f(powerX + xpos - s / 2, +(3 * s / 2));
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(powerX + xpos - (3 * s / 2), -s / 2);
	glVertex2f(powerX + xpos + (3 * s / 2), -s / 2);
	glVertex2f(powerX + xpos + (3 * s / 2), +s / 2);
	glVertex2f(powerX + xpos - (3 * s / 2), +s / 2);
	glEnd();

	if (playerX <= powerX + xpos + (3 * s / 2) && playerX >= powerX + xpos - (3 * s / 2))
	{
		if (playerY <= (3 * s / 2) && playerY >= -(3 * s / 2))
		{
			power = true;
			powerT = 3000;
		}
	}
}

void drawCircle(float x, float y, float r, float color[3])
{
	glPushMatrix();
	glColor3f(color[0], color[1], color[2]);
	glTranslatef(x, y, 0);
	GLUquadric *quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}
/*
void drawPlayer()
{
	float r = 10;
	float color[3] = {1,0.6,1};
	drawCircle(playerX,playerY,r,color);
	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	glVertex2f(playerX+r-2,playerY+5);
	glVertex2f(playerX+r-2, playerY-5);
	glVertex2f(playerX+r+ 5, playerY);
	glEnd();

}
*/

void drawPlayer()
{

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.3, 0.6);
	glVertex2f(playerX + s, playerY + s);
	glVertex2f(playerX + s, playerY - s);
	glVertex2d(playerX - s, playerY + s / 5);
	glColor3f(1, 0.7, 0);
	glVertex2f(playerX + s, playerY + s);
	glVertex2f(playerX + s, playerY + s / 3);
	glVertex2d(playerX + (5 * s) / 3, playerY + (2 * s) / 3);
	glEnd();

	glBegin(GL_LINES);
	//glLineWidth(1000);
	glColor3f(0, 0, 0);
	glVertex2f(playerX + s, playerY + (2 * s) / 3);
	glVertex2f(playerX + (5 * s) / 3, playerY + (2 * s) / 3);
	glEnd();
	float black[3] = {0, 0, 0};
	drawCircle(playerX + 4, playerY + 5, 2, black);
}

void drawPipeDown(float x, float h, float color[3])
{
	drawRect(x, -180 + h, 40, h, color);

	drawRect(x - 5, -180 + 15 + h, 50, 15, color);
}

void drawPipeUp(float x, float h, float color[3])
{
	drawRect(x, 180, 40, h, color);

	drawRect(x - 5, 180 - h, 50, 15, color);
}

void drawPipeDou(float x, float h, float color[3])
{
	drawPipeDown(x, h, color);
	drawPipeUp(x, 260 - h, color);

	//360 = 290-2h

	//float gapMid = (180-h+15) + (-180 -h +15 );

	float gb = 360 - h;
	float gt = gb + 35;
	float gapBottom;
	float gapTop;
	if (gb >= 0)
	{
		gapBottom = h - 180 + 15;
	}
	else
	{
		gapBottom = -h - 15;
	}

	if (gt >= 0)
	{
		gapTop = h - 180 + 85;
	}
	else
	{
		gapTop = -h + 85;
	}

	/*
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0,0,0);
	glVertex2d(x , gapTop);
	glVertex2d(x , gapBottom);
	glEnd();
	*/
	float currentLeft = playerX + (5 * s) / 3;
	float currentRight = playerX - s;
	float currntTop = playerY + s;
	float currentBottom = playerY - s;

	if (x - 5 <= currentLeft && x + 45 >= currentRight && !power)
	{
		if (gapBottom > currentBottom)
		{
			playerY += (gapBottom - currentBottom) + 15;
			lives--;
			//power=true;
		}
		else if (gapTop < currntTop)
		{
			lives--;
			playerY -= 10;
			//power = true;
		}
	}
}

void drawAllPipes()
{
	float dist = 0;
	for (int i = 0; i < 3; i++)
	{
		//float current[4] = pipes[i];
		int pos = xpos + dist;
		for (int j = 0; j < 3; j++)
		{

			if (power)
				drawPipeDou(pos, pipes[p[i]][j], pipeColorAlt);
			else
				drawPipeDou(pos, pipes[p[i]][j], pipeColor);
			pos += 130;
		}
		dist += 700;
	}
}

void print(int x, int y, string s)
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

void timer(int)
{
	glutPostRedisplay();

	if (playerY + s >= 180)
	{
		return;
		lose = true;
		playerY -= 20;
	}
	else if (playerY - s <= -180)
	{
		return;
		lose = true;
		playerY += 20;
	}
	else
	{
		playerY -= 1;
	}
	if (xpos < -1700)
		return;
	if (lives <= 0)
		return;

	if (powerT >= 0)
	{
		powerT -= (1000 / 60);
	}
	else
	{
		power = false;
	}
	glutTimerFunc(1000 / 60, timer, 0);
	t += 5;
	xpos -= 1.6;
}

void Key(unsigned char key, int x, int y)
{

	if (key == ' ')
	{
		playerY += 20;
		/*
		for (int i = 0; i < 1000; i++)
		{
			playerY += 0.1;
			glutPostRedisplay();
		}
		*/
	}
}

void KeyUp(unsigned char key, int x, int y)
{
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, -180.0, 180.0);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	if (xpos > -450)
	{
		glClearColor(0.329412f, 0.329412f, 0.329412f, 0.0f);
	}
	else if (xpos > -920)
	{
		glClearColor(0.0f, 0.3f, 0.3f, 0.0f);
		//glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		glClearColor(1, 1, 1, 0);
	}

	drawAllPipes();

	drawPower(10);

	print(580, 170, "Lives: " + to_string(lives));
	print(580, 160, "Score: " + to_string(t));
	drawPlayer();
	glutSwapBuffers();
}
