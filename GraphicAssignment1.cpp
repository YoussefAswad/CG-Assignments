//  Includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
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
float playerX = 28;
float playerY = 0;
float xpos = 180;
bool power = false;
float pipes[3][3] = {{140, 170, 100}, { 140, 170, 100}, { 140, 170, 100}};
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

void drawCircle(float x, float y, float r , float color[3])
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


void drawPlayer(){
	int r = 69;
	int g = 205;
	int b = 62;
	float color[3] = {0 , 0.3 , 0.7};
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.3, 0.6);
	glVertex2f(playerX + 15 ,playerY + 15);
	glVertex2f(playerX + 15 , playerY -15);
	glVertex2d(playerX-15 , playerY+3);
	glColor3f(1, 0.7, 0);
	glVertex2f(playerX + 15 ,playerY + 15);
	glVertex2f(playerX + 15 , playerY +5);
	glVertex2d(playerX+ 25 , playerY+10);
	glEnd();

	glBegin(GL_LINES);
	//glLineWidth(1000);
	glColor3f(0, 0, 0);
	glVertex2f(playerX + 15 ,playerY + 10);
	glVertex2f(playerX + 25 , playerY +10);
	glEnd();

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
	drawPipeUp(x, 280 - h, color);
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
				drawPipeDou(pos, pipes[i][j], pipeColorAlt);
			else
				drawPipeDou(pos, pipes[i][j], pipeColor);
			pos += 130;
		}
		dist += 700;
	}
}

void timer(int)
{
	glutPostRedisplay();
	t += 1000 / 60;
	playerY -= 1;
	glutTimerFunc(1000 / 60, timer, 0);

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
		glClearColor(0.7, 0, 0, 0);
	}
	else if(xpos > -950)
	{
		glClearColor(0, 0, 1, 0);
	}
	else{
		glClearColor(1, 1, 1, 0);
	}
	
	drawAllPipes();

	drawPlayer();
	glutSwapBuffers();
}
