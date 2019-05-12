#include <GL/glut.h>
#include <stdio.h>
#include <unistd.h>

void draw4way(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(+x, +y);
	glVertex2i(+x, -y);
	glVertex2i(-x, +y);
	glVertex2i(-x, -y);
	glEnd();
}

void drawEllipse(double a, double b)
{
	double d = (b * b) - a * a * (b - 0.25);
	double x = 0;
	double y = b;
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
		draw4way((int)x, (int)y);
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
		draw4way((int)x, (int)y);
	}
}

void display(void)
{
	glOrtho(-320, 319, -240, 239, -1, 1);
	glColor3f(1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawEllipse(120, 80);
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(240, 240);
	glutCreateWindow("Ellipse");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}