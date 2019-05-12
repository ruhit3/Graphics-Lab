#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

using namespace std;

int Wi = 640, He = 480;

void myInit(void);
void display(void);
void reshape(int w, int h);
void draw_line_8_seg(int x0, int y0, int x1, int y1);
void drawLine(int x0, int y0, int x1, int y1);
double a = 25, b = 20, c = 100, d = 160;
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void GridDraw()
{
    glBegin(GL_LINES);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, 239);
    glVertex2i(0, -240);

    glEnd();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-Wi / 2, Wi / 2 - 1, -He / 2, He / 2 - 1); // size of projection plane (origin at the center)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    GridDraw();
    glBegin(GL_POINTS);

    for (int xx = 0; xx < 50; xx++)
    {
        a = -320 + rand() % 640;
        b = -240 + rand() % 480;
        c = -320 + rand() % 640;
        d = -240 + rand() % 480;
        draw_line_8_seg(a, b, c, d);
    }
    glEnd();
    glFlush();
}

int drawZone;

int getZone()
{
    return drawZone;
}
void setZone(int i)
{
    drawZone = i;
}

int zone(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    if (abs(dx) >= abs(dy) && (dx >= 0 && dy >= 0))
    {
        return 0;
    }
    else if (abs(dy) >= abs(dx) && (dx >= 0 && dy >= 0))
    {
        return 1;
    }
    else if (abs(dy) >= abs(dx) && (dx <= 0 && dy >= 0))
    {
        return 2;
    }
    else if (abs(dx) >= abs(dy) && (dx <= 0 && dy >= 0))
    {
        return 3;
    }
    else if (abs(dx) >= abs(dy) && (dx <= 0 && dy <= 0))
    {
        return 4;
    }
    else if (abs(dy) >= abs(dx) && (dx <= 0 && dy <= 0))
    {
        return 5;
    }
    else if (abs(dy) >= abs(dx) && (dx >= 0 && dy <= 0))
    {
        return 6;
    }
    else if (abs(dx) >= abs(dy) && (dx >= 0 && dy <= 0))
    {
        return 7;
    }
    return 8;
}

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    switch (getZone())
    {

    case 0:
        glVertex2i(x, y);
        break;
    case 1:
        glVertex2i(y, x);
        break;
    case 2:
        glVertex2i(-y, x);
        break;
    case 3:
        glVertex2i(-x, y);
        break;
    case 4:
        glVertex2i(-x, -y);
        break;
    case 5:
        glVertex2i(-y, -x);
        break;
    case 6:
        glVertex2i(y, -x);
        break;
    case 7:
        glVertex2i(x, -y);
        break;
    }
    glEnd();
}

void drawLine(int x0, int y0, int x1, int y1)
{
    printf("%d %d %d %d\n", x0, y0, x1, y1);
    int dy = y1 - y0;
    int dx = x1 - x0;
    int dint = 2 * dy - dx;
    int dE = 2 * dy;
    int dNE = 2 * (dy - dx);

    int x = x0, y = y0;
    drawPixel(x, y);

    while (x <= x1)
    {
        if (dint < 0)
        {
            x++;
            dint += dE;
        }
        else
        {
            x++;
            y++;
            dint += dNE;
        }
        drawPixel(x, y);
    }
}

void draw_line_8_seg(int x0, int y0, int x1, int y1)
{
    switch (zone(x0, y0, x1, y1))
    {
    case 0:
        printf("zone 0\n");
        setZone(0);
        glColor3f(1.0, 0.0, 0.0); ///Red
        drawLine(x0, y0, x1, y1);
        break;
    case 1:
        printf("zone 1\n");
        setZone(1);
        glColor3f(0.0, 1.0, 0.0); ///Green
        drawLine(y0, x0, y1, x1);
        break;
    case 2:
        printf("zone 2\n");
        setZone(2);
        glColor3f(0.0, 0.0, 1.0); ///Blue
        drawLine(y0, -x0, y1, -x1);
        break;
    case 3:
        printf("zone 3\n");
        setZone(3);
        glColor3f(1.0, 1.0, 0.0); ///Yellow
        drawLine(-x0, y0, -x1, y1);
        break;
    case 4:
        printf("zone 4\n");
        setZone(4);
        glColor3f(1.0, 0.1, 1.0); ///Purple
        drawLine(-x0, -y0, -x1, -y1);
        break;
    case 5:
        printf("zone 5\n");
        setZone(5);
        glColor3f(0, 1.0, 1.0); ///Cyan
        drawLine(-y0, -x0, -y1, -x1);
        break;
    case 6:
        printf("zone 6\n");
        setZone(6);
        glColor3f(1.0, 1.0, 1.0); ///White
        drawLine(-y0, x0, -y1, x1);
        break;
    case 7:
        printf("zone 7\n");
        setZone(7);
        glColor3f(1.0, 0.5, 0.0); ///Orange
        drawLine(x0, -y0, x1, -y1);
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                       // to initialize the toolkit;
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // sets the display mode
    glutInitWindowSize(Wi, He);                  // sets the window size
    glutInitWindowPosition(0, 0);                // sets the starting position for the window
    glutCreateWindow("Line Drawing");            // creates the window and sets the title
    myInit();                                    // additional initializations as necessary
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop(); // go into a loop until event occurs
    return 0;
}
