#include <GL/glut.h>
#include <stdio.h>

void draw8way(int x, int y, int xc, int yc)
{
	glBegin(GL_POINTS);
	glVertex2i(+x + xc, +y + yc);
	glVertex2i(+x + xc, -y + yc);
	glVertex2i(-x + xc, +y + yc);
	glVertex2i(-x + xc, -y + yc);
	glVertex2i(+y + xc, +x + yc);
	glVertex2i(+y + xc, -x + yc);
	glVertex2i(-y + xc, +x + yc);
	glVertex2i(-y + xc, -x + yc);
	glEnd();
}

void drawCircle(int a, int b, int r)
{
	int x = 0;
	int y = r;
	int d = 5 - 4 * r;
	while (y > x)
	{
		if (d < 0)
		{
			d += (2 * x + 3) * 4;
		}
		else
		{
			d += (2 * x - 2 * y + 5) * 4;
			y--;
		}
		x++;
		draw8way(x, y, a, b);
	}
}

void drawMovingCircle()
{
	int centreX = 0, centreY = 0, radius = 60;
	int stepX = 1, stepY = 2;
	glColor3f(1, 0, 0);
	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		drawCircle(centreX, centreY, radius);
		glutSwapBuffers();
		if (centreX + radius > 319 || centreX - radius < -320)
		{
			stepX = stepX * -1;
		}
		if (centreY + radius > 239 || centreY - radius < -240)
		{
			stepY = stepY * -1;
		}
		centreX += stepX;
		centreY += stepY;
	}
}

void display(void)
{
	glOrtho(-320, 319, -240, 239, -1, 1);
	drawMovingCircle();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(240, 240);
	glutCreateWindow("Moving Circle");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}