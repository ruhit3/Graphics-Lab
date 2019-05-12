#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

void midPointLine(int x0, int y0, int x1, int y1, int option);
void drawpixel(int x, int y, int option);
void cube(double x0, double y0, double z0, double d, double size);
void projection(double d);
const double pi = 3.1416;

typedef struct
{
    double x, y, z;
} point;

point p[8], m[8];

double cx, cy, cz;

void MyReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400, 400, -300, 300, -300, 300);
}

void MyInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // sets the clear color for the background
}

void DrawLine(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    if (abs(dx) >= abs(dy))
    {
        if (x1 >= x0 && y1 >= y0)
        {
            midPointLine(x0, y0, x1, y1, 0);
        }
        if (x1 >= x0 && y1 < y0)
        {
            midPointLine(x0, -y0, x1, -y1, 7);
        }
        if (x1 < x0 && y1 >= y0)
        {
            midPointLine(-x0, y0, -x1, y1, 3);
        }
        if (x1 < x0 && y1 < y0)
        {
            midPointLine(-x0, -y0, -x1, -y1, 4);
        }
    }
    else
    {
        if (y1 >= y0 && x1 >= x0)
        {
            midPointLine(y0, x0, y1, x1, 1);
        }
        if (y1 >= y0 && x1 < x0)
        {
            midPointLine(y0, -x0, y1, -x1, 2);
        }
        if (y1 < y0 && x1 > x0)
        {
            midPointLine(-y0, x0, -y1, x1, 6);
        }
        if (y1 < y0 && x1 <= x0)
        {
            midPointLine(-y0, -x0, -y1, -x1, 5);
        }
    }
}

void midPointLine(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int d = 2 * dy - dx;
    int delE = 2 * dy;
    int delNE = 2 * (dy - dx);
    int x = x0;
    int y = y0;

    drawpixel(x, y, zone);

    while (x <= x1)
    {
        if (d < 0)
        {
            d += delE;
            x++;
        }
        else
        {
            d += delNE;
            x++;
            y++;
        }
        drawpixel(x, y, zone);
    }
}

void drawpixel(int x, int y, int zone)
{
    switch (zone)
    {
    case 0:
        glVertex2i(x, y);
        break;
    case 3:
        glVertex2i(-x, y);
        break;
    case 4:
        glVertex2i(-x, -y);
        break;
    case 7:
        glVertex2i(x, -y);
        break;
    case 1:
        glVertex2i(y, x);
        break;
    case 2:
        glVertex2i(-y, x);
        break;
    case 5:
        glVertex2i(-y, -x);
        break;
    case 6:
        glVertex2i(y, -x);
        break;
    }
    return;
}

void MyDisplay()
{
    cx = 0;
    cy = 0;
    cz = 300;
    //clears buffers to preset values.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //sets the current matrix mode
    glMatrixMode(GL_MODELVIEW);
    //replace the current matrix with the identity matrix
    glLoadIdentity();
    //sets the point color
    glColor4f(0.0, 0.0, 1.0, 1.0);

    glPushMatrix();
    glBegin(GL_POINTS);

    cube(0, 0, 0, 100, 200);

    //end opengl drawing
    glEnd();

    //swap the drawing buffer with the output buffer after the completion
    glPopMatrix();
    glutSwapBuffers();
}

void cube(double x0, double y0, double z0, double d, double size)
{
    double N = size / 2.0;
    p[0].x = x0 - N;
    p[0].y = y0 - N;
    p[0].z = z0 - N;
    p[1].x = x0 - N;
    p[1].y = y0 - N;
    p[1].z = z0 + N;
    p[2].x = x0 - N;
    p[2].y = y0 + N;
    p[2].z = z0 - N;
    p[3].x = x0 - N;
    p[3].y = y0 + N;
    p[3].z = z0 + N;
    p[4].x = x0 + N;
    p[4].y = y0 - N;
    p[4].z = z0 - N;
    p[5].x = x0 + N;
    p[5].y = y0 - N;
    p[5].z = z0 + N;
    p[6].x = x0 + N;
    p[6].y = y0 + N;
    p[6].z = z0 - N;
    p[7].x = x0 + N;
    p[7].y = y0 + N;
    p[7].z = z0 + N;

    projection(d);

    glColor4f(1.0, 0.0, 0.0, 1.0);

    DrawLine(m[0].x, m[0].y, m[1].x, m[1].y);
    DrawLine(m[1].x, m[1].y, m[3].x, m[3].y);
    DrawLine(m[3].x, m[3].y, m[2].x, m[2].y);
    DrawLine(m[2].x, m[2].y, m[0].x, m[0].y);
    DrawLine(m[0].x, m[0].y, m[4].x, m[4].y);
    DrawLine(m[4].x, m[4].y, m[6].x, m[6].y);
    DrawLine(m[6].x, m[6].y, m[2].x, m[2].y);
    DrawLine(m[6].x, m[6].y, m[7].x, m[7].y);
    DrawLine(m[7].x, m[7].y, m[5].x, m[5].y);
    DrawLine(m[5].x, m[5].y, m[4].x, m[4].y);
    DrawLine(m[5].x, m[5].y, m[1].x, m[1].y);
    DrawLine(m[7].x, m[7].y, m[3].x, m[3].y);
}

//projection funtion

void projection(double d)
{
    double dx, dy, dz;
    double q = sqrt(cx * cx + cy * cy + (cz - d) * (cz - d));
    dx = cx / q;
    dy = cy / q;
    dz = (cz - d) / q;
    for (int i = 0; i < 8; i++)
    {
        m[i].x = (p[i].x - p[i].z * (dx / dz) + d * (dx / dz)) / (((d - p[i].z) / (q * dz)) + 1.0);
        m[i].y = (p[i].y - p[i].z * dy / dz + d * dy / dz) / (((d - p[i].z) / (q * dz)) + 1.0);
        m[i].z = d;
    }
}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Projection:Cube");
    glutReshapeFunc(MyReshape);
    MyInit();
    glutDisplayFunc(MyDisplay);

    glutMainLoop();
    glutSwapBuffers();

    return 0;
}
