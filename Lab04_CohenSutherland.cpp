#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void draw_boundary()
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(-160, -120);
    glVertex2i(-160, 120);
    glVertex2i(160, 120);
    glVertex2i(160, -120);
    glEnd();
    glFlush();
}

void draw_point(int x, int y)
{
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_line(int x0, int y0, int x1, int y1)
{
    glBegin(GL_LINES);
    glVertex2i(x0, y0);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
}

int xmax = 160, xmin = -160, ymax = 120, ymin = -120;
int TOP = 8, BOTTOM = 4, RIGHT = 2, LEFT = 1;

int makeCode(int x, int y)
{
    int code = 0;
    if (y > ymax)
        code += TOP;
    else if (y < ymin)
        code += BOTTOM;
    if (x > xmax)
        code += RIGHT;
    else if (x < xmin)
        code += LEFT;
    return code;
}

void clipLine(int x0, int y0, int x1, int y1)
{
    int x, y;
    int u0 = x0, v0 = y0, u1 = x1, v1 = y1;
    int code;
    int code0 = makeCode(x0, y0);
    int code1 = makeCode(x1, y1);
    int flag = 0;
    while (1)
    {
        if (!(code0 | code1))
        {
            flag = 1;
            glColor3f(0, 1, 1); // c1
            draw_point(x0, y0);
            draw_point(x1, y1);
            draw_line(x0, y0, x1, y1);
            break;
        }
        else if (code0 & code1)
        {
            glColor3f(1, 0, 1); // c2
            draw_point(x0, y0);
            draw_point(x1, y1);
            draw_line(x0, y0, x1, y1);
            break;
        }
        else
        {
            code = code0 ? code0 : code1;
            if (code & TOP)
            {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            }
            else if (code & BOTTOM)
            {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            }
            else if (code & RIGHT)
            {
                x = xmax;
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
            }
            else
            {
                x = xmin;
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
            }

            if (code == code0)
            {
                x0 = x;
                y0 = y;
                code0 = makeCode(x0, y0);
            }
            else
            {
                x1 = x;
                y1 = y;
                code1 = makeCode(x1, y1);
            }
        }
    }
    if (code0 != 0 && code1 != 0)
    {
        glColor3f(1, 0, 1); // c2
        draw_point(u0, v0);
        draw_point(u1, v1);
        draw_line(u0, v0, u1, v1);
    }
}

void display()
{
    glOrtho(-320, 319, -240, 239, -1, 1);
    draw_boundary();

    int N = 50;
    int x0, x1, y0, y1;
    for (int i = 0; i < N; i++)
    {
        x0 = rand() % 640 - 320;
        y0 = rand() % 480 - 240;
        x1 = rand() % 640 - 320;
        y1 = rand() % 480 - 240;
        glColor3f(1, 1, 0); // c3
        draw_point(x0, y0);
        draw_point(x1, y1);
        draw_line(x0, y0, x1, y1);
        clipLine(x0, y0, x1, y1);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(240, 240);
    glutCreateWindow("Cohen-Sutherland LCA");
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
