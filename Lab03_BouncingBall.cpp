#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

void draw4way(int x, int y, int xc, int yc)
{
	glBegin(GL_POINTS);
	glVertex2i(+x + xc, +y + yc);
	glVertex2i(+x + xc, -y + yc);
	glVertex2i(-x + xc, +y + yc);
	glVertex2i(-x + xc, -y + yc);
	glEnd();
}

void drawEllipse(int a, int b, int xc, int yc)
{
	double d = (b * b) - a * a * (b - 0.25);
	double x = 0;
	double y = b;
	draw4way((int)x, (int)y, xc, yc);
	while (a * a * (y - 0.5) > b * b * (x + 1)) // Region 1
	{
		if (d < 0) // E
		{
			d += (b * b * (2 * x + 3));
		}
		else // SE
		{
			d += (b * b * (2 * x + 3) - a * a * (2 * y - 2));
			y--;
		}
		x++;
		draw4way((int)x, (int)y, xc, yc);
	}
	while (y > 0) // Region 2
	{
		if (d > 0) // S
		{
			d += (a * a * (3 - 2 * y));
		}
		else // SE
		{
			d += (a * a * (3 - 2 * y) + b * b * (2 * x + 2));
			x++;
		}
		y--;
		draw4way((int)x, (int)y, xc, yc);
	}
}

void makeEllipse(int A, int B, int Xc, int Yc)
{
	int N = 25;
	double d = A * sqrt(2.0); // to preserve ratio of a & b
	int a = A;
	int b = B;
	int xc = Xc;
	int yc = Yc;
	printf("------ELLIPSE------\n");
	for (int i = 1; i <= N; i++)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1, 1, 0);
		drawEllipse(b, a, xc, yc);
		b = b + 1;
		a = (int)sqrt(d * d - b * b);
		yc = yc - 1;
		glutSwapBuffers();
	}
	for (int i = 1; i <= N; i++)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 1, 1);
		drawEllipse(b, a, xc, yc);
		b = b - 1;
		a = (int)sqrt(d * d - b * b);
		yc = yc + 1;
		glutSwapBuffers();
	}
}

void drawMovingEllipse(int A, int B, int Xc, int Yc)
{
	int a = A;
	int b = B;
	int xc = Xc;
	int yc = Yc;

	int stepY = -1;
	int count = 0;
	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1, 0, 1);
		drawEllipse(a, b, xc, yc);
		glutSwapBuffers();

		if (yc >= 0) // top
		{
			stepY = 1;
			stepY = stepY * -1;
		}

		if (yc - b < -240) // bottom
		{
			stepY = -6;
			stepY = stepY * -1;
			makeEllipse(a, b, xc, yc);
		}

		yc += stepY;

		if (stepY < 0)
		{
			printf("Going Down\n");
			if ((-1 * yc) % 30 == 0)
			{
				stepY--;
				count++;
			}
		}

		if (stepY > 0)
		{
			printf("Going Up\n");
			if ((-1 * yc) % 30 == 0)
			{
				stepY--;
				count--;
			}
		}
		printf("Height: %d, Step: %d, Count: %d\n", yc, stepY, count);
	}
}

void display(void)
{
	glOrtho(-320, 319, -240, 239, -1, 1);
	drawMovingEllipse(60, 60, 0, 0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Bouncing Ball");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}