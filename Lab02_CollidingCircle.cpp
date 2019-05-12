#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

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

int EuclideanDistance(int x1, int y1, int x2, int y2)
{
	int dx = x1 - x2;
	int dy = y1 - y2;
	int r = dx * dx + dy * dy;
	int d = (int)sqrt((double)r);
	return d;
}

void drawMovingCircle()
{
	int r1 = 80;
	int a1 = r1;
	int b1 = 0;

	int r2 = 80;
	int a2 = -r2;
	int b2 = 0;

	int stepX1 = 1, stepY1 = 2;
	int stepX2 = 1, stepY2 = 2;

	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 1, 0);
		drawCircle(a1, b1, r1);
		glColor3f(0, 0, 1);
		drawCircle(a2, b2, r2);
		glutSwapBuffers();
		// circle 1
		if (a1 + r1 > 319 || a1 - r1 < -320)
		{
			stepX1 = stepX1 * -1;
		}
		if (b1 + r1 > 239 || b1 - r1 < -240)
		{
			stepY1 = stepY1 * -1;
		}
		a1 += stepX1;
		b1 += stepY1;
		// circle 2
		if (a2 + r2 > 319 || a2 - r2 < -320)
		{
			stepX2 = stepX2 * -1;
		}
		if (b2 + r2 > 239 || b2 - r2 < -240)
		{
			stepY2 = stepY2 * -1;
		}
		a2 -= stepX2;
		b2 -= stepY2;
		// colliding circles
		if (EuclideanDistance(a1, b1, a2, b2) <= (r1 + r2))
		{
			stepX1 = stepX1 * -1;
			stepY1 = stepY1 * -1;
			stepX2 = stepX2 * -1;
			stepY2 = stepY2 * -1;
		}
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
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Colliding Circle");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}