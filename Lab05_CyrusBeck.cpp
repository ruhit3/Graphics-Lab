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

void draw_line(int x0, int y0, int x1, int y1)
{
    glBegin(GL_LINES);
    glVertex2i(x0, y0);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
}

void draw_point(int x, int y)
{
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

int xmax = 160, xmin = -160, ymax = 120, ymin = -120;

void CyrusBeck(int x0, int y0, int x1, int y1)
{
    glColor3f(255, 255, 255); // draw full white line
    draw_line(x0, y0, x1, y1);
    draw_point(x0, y0);
    draw_point(x1, y1);
    float t[5], tEmax = 0.0, tLmin = 1.0;
    if (x0 == x1 || y0 == y1)
    {
        printf("Parallel to axis\n");
        return;
    }
    // top
    t[0] = (ymax - y0) / ((float)y1 - y0);
    if (y1 >= y0)
    {
        if (t[0] < tLmin)
        {
            tLmin = t[0];
        }
    }
    else
    {
        if (t[0] > tEmax)
        {
            tEmax = t[0];
        }
    }
    // bottom
    t[1] = (ymin - y0) / ((float)y1 - y0);
    if (y1 < y0)
    {
        if (t[1] < tLmin)
        {
            tLmin = t[1];
        }
    }
    else
    {
        if (t[1] > tEmax)
        {
            tEmax = t[1];
        }
    }
    // right
    t[2] = (xmax - x0) / ((float)x1 - x0);
    if (x1 > x0)
    {
        if (t[2] < tLmin)
        {
            tLmin = t[2];
        }
    }
    else
    {
        if (t[2] > tEmax)
        {
            tEmax = t[2];
        }
    }
    //left
    t[3] = (xmin - x0) / ((float)x1 - x0);
    if (x1 < x0)
    {
        if (t[3] < tLmin)
        {
            tLmin = t[3];
        }
    }
    else
    {
        if (t[3] > tEmax)
        {
            tEmax = t[3];
        }
    }
    // draw_line
    if (tEmax == 0.0 && tLmin == 1.0)
    {
        glColor3f(0, 1, 0); // green
        draw_line(x0, y0, x1, y1);
        printf("Accepted\n");
    }
    else if (tEmax < tLmin)
    {
        int nx0, nx1, ny0, ny1;
        nx0 = (x0 + tEmax * (x1 - x0));
        ny0 = (y0 + tEmax * (y1 - y0));
        nx1 = (x0 + tLmin * (x1 - x0));
        ny1 = (y0 + tLmin * (y1 - y0));
        draw_point(nx0, ny0);
        draw_point(nx1, ny1);

        glColor3f(0, 1, 1); // red
        draw_line(nx0, ny0, nx1, ny1);
        printf("Cutting points:\ntEmax %.2f, tLmin %.2f\n", tEmax, tLmin);
        printf("(%d, %d), (%d, %d)\n", nx0, ny0, nx1, ny1);
    }
    else if (tEmax > tLmin)
    {
        glColor3f(0, 0, 1); // blue
        draw_line(x0, y0, x1, y1);
        printf("Rejected\n");
    }
}

void display()
{
    glOrtho(-320, 319, -240, 239, -1, 1);
    draw_boundary();
    CyrusBeck(-180, -180, 180, 180);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(240, 240);
    glutCreateWindow("Cyrus-Beck LCA");
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
