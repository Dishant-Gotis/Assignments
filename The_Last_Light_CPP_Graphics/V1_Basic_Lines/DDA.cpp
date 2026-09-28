#include <graphics.h>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

void DDA(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = max(abs(dx), abs(dy));

    float xIncrement = (float)dx / steps;
    float yIncrement = (float)dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++)
    {
        putpixel(round(x), round(y), WHITE);

        x += xIncrement;
        y += yIncrement;
    }
}

int main()
{
    int gd = DETECT;
    int gm;

    // Open graphics window
    initgraph(&gd, &gm, "");

    // Set background color
    setbkcolor(BLACK);
    cleardevice();

    // Draw DDA line
    DDA(100, 100, 500, 300);

    // Keep GUI window open
    getch();

    // Close graphics window
    closegraph();

    return 0;
}