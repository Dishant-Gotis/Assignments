// ============================================================
//  THE LAST LIGHT  –  VERSION 1: Basic Lines
// ============================================================
//  Computer Graphics Algorithms demonstrated:
//    • DDA Line Drawing Algorithm
//    • Bresenham's Line Drawing Algorithm
//
//  Scenes (press SPACE or ENTER to advance):
//    1. Lumen Village
//    2. Dark Forest
//    3. Abandoned Shrine
//
//  Controls:
//    SPACE / ENTER  – Next scene
//    ESC            – Quit
// ============================================================

#include <graphics.h>
#include <cmath>
#include <cstring>
#include <cstdlib>

// ────────────────────────────────────────────────────────────
//  Window / layout constants
// ────────────────────────────────────────────────────────────
const int WIN_W  = 900;
const int WIN_H  = 620;
const int HUD_H  = 50;          // top HUD strip height
const int LEGEND = 160;         // right-side legend width

// Playfield boundaries (inside HUD + legend)
const int PF_X1 = 0;
const int PF_Y1 = HUD_H;
const int PF_X2 = WIN_W - LEGEND;
const int PF_Y2 = WIN_H;

// ────────────────────────────────────────────────────────────
//  Colour palette (WinBGIm colour indices)
// ────────────────────────────────────────────────────────────
// We rely on RGB() where available; fall back to standard
// BGI colors for broad compatibility.
#define COL_BG_VILLAGE  COLOR(30 , 50 , 20)
#define COL_BG_FOREST   COLOR(10 , 30 , 10)
#define COL_BG_SHRINE   COLOR(30 , 25 , 35)
#define COL_HUD         COLOR(15 , 15 , 25)
#define COL_LEGEND_BG   COLOR(10 , 10 , 20)
#define COL_TEXT        WHITE
#define COL_DDA         COLOR(80 , 200, 120)   // green  – DDA objects
#define COL_BRES        COLOR(200, 150,  80)   // amber  – Bresenham objects
#define COL_ROAD        COLOR(120, 100,  60)
#define COL_HOUSE       COLOR(160,  80,  40)
#define COL_ROOF        COLOR(180,  60,  40)
#define COL_CRYSTAL     COLOR(100, 200, 255)
#define COL_PLAYER      COLOR(230, 210, 160)
#define COL_SWORD       COLOR(200, 220, 240)
#define COL_TREE_T      COLOR( 80,  55,  30)
#define COL_TREE_L      COLOR( 30, 100,  30)
#define COL_BRIDGE      COLOR(140, 110,  70)
#define COL_SHRINE      COLOR(130, 120, 140)
#define COL_GUARDIAN    COLOR(160,  40,  40)
#define COL_SHARD       COLOR(255, 240, 100)
#define COL_BOUNDARY    COLOR(60 ,  55,  80)

// ────────────────────────────────────────────────────────────
//  DDA Line Drawing Algorithm
// ────────────────────────────────────────────────────────────
void drawDDA(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    if (steps == 0) {
        putpixel(x1, y1, getcolor());
        return;
    }

    float xInc = (float)dx / steps;
    float yInc = (float)dy / steps;

    float x = (float)x1;
    float y = (float)y1;

    for (int i = 0; i <= steps; ++i) {
        putpixel((int)(x + 0.5f), (int)(y + 0.5f), getcolor());
        x += xInc;
        y += yInc;
    }
}

// ────────────────────────────────────────────────────────────
//  Bresenham's Line Drawing Algorithm
// ────────────────────────────────────────────────────────────
void drawBresenhamLine(int x1, int y1, int x2, int y2)
{
    int dx =  abs(x2 - x1);
    int dy =  abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        putpixel(x1, y1, getcolor());
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 <  dx) { err += dx; y1 += sy; }
    }
}

// ────────────────────────────────────────────────────────────
//  Convenience wrappers that set colour then draw
// ────────────────────────────────────────────────────────────
void ddaLine(int x1,int y1,int x2,int y2,int col)
{
    setcolor(col);
    drawDDA(x1,y1,x2,y2);
}

void bresLine(int x1,int y1,int x2,int y2,int col)
{
    setcolor(col);
    drawBresenhamLine(x1,y1,x2,y2);
}

// Thick line helper (draws multiple parallel lines)
void ddaThick(int x1,int y1,int x2,int y2,int col,int t=2)
{
    setcolor(col);
    for(int i=-t/2;i<=t/2;i++){
        int dy=abs(y2-y1), dx=abs(x2-x1);
        if(dx>=dy){ drawDDA(x1,y1+i,x2,y2+i); }
        else       { drawDDA(x1+i,y1,x2+i,y2); }
    }
}

void bresThick(int x1,int y1,int x2,int y2,int col,int t=2)
{
    setcolor(col);
    for(int i=-t/2;i<=t/2;i++){
        int dy=abs(y2-y1), dx=abs(x2-x1);
        if(dx>=dy){ drawBresenhamLine(x1,y1+i,x2,y2+i); }
        else       { drawBresenhamLine(x1+i,y1,x2+i,y2); }
    }
}

// Rectangle outline via DDA
void ddaRect(int x1,int y1,int x2,int y2,int col,int t=1)
{
    ddaThick(x1,y1,x2,y1,col,t);
    ddaThick(x2,y1,x2,y2,col,t);
    ddaThick(x2,y2,x1,y2,col,t);
    ddaThick(x1,y2,x1,y1,col,t);
}

// Rectangle outline via Bresenham
void bresRect(int x1,int y1,int x2,int y2,int col,int t=1)
{
    bresThick(x1,y1,x2,y1,col,t);
    bresThick(x2,y1,x2,y2,col,t);
    bresThick(x2,y2,x1,y2,col,t);
    bresThick(x1,y2,x1,y1,col,t);
}

// ────────────────────────────────────────────────────────────
//  HUD
// ────────────────────────────────────────────────────────────
void drawHUD(const char* scene, int sceneNum)
{
    setfillstyle(SOLID_FILL, COL_HUD);
    bar(0, 0, WIN_W, HUD_H - 1);

    // Title
    setcolor(COL_CRYSTAL);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(10, 10, (char*)"THE LAST LIGHT");

    // Version tag
    setcolor(COL_DDA);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(220, 8,  (char*)"VERSION 1");
    outtextxy(220, 22, (char*)"DDA + BRESENHAM LINE");

    // Scene
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    char buf[80];
    sprintf(buf, "Scene %d/3 : %s", sceneNum, scene);
    outtextxy(440, 18, buf);

    // Controls hint
    setcolor(COL_BRES);
    outtextxy(650, 8,  (char*)"[SPACE] Next");
    outtextxy(650, 22, (char*)"[ESC]   Quit");

    // Separator
    bresLine(0, HUD_H-1, WIN_W, HUD_H-1, COL_BOUNDARY);
}

// ────────────────────────────────────────────────────────────
//  Right-side algorithm legend
// ────────────────────────────────────────────────────────────
void drawLegend()
{
    int lx = PF_X2 + 5;

    setfillstyle(SOLID_FILL, COL_LEGEND_BG);
    bar(PF_X2, HUD_H, WIN_W, WIN_H);

    // Vertical separator
    bresLine(PF_X2, HUD_H, PF_X2, WIN_H, COL_BOUNDARY);

    // Title
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(lx, HUD_H+8, (char*)"ALGORITHM");
    outtextxy(lx, HUD_H+20,(char*)"LEGEND");
    bresLine(PF_X2, HUD_H+34, WIN_W, HUD_H+34, COL_BOUNDARY);

    int y = HUD_H + 44;

    // DDA entry
    setcolor(COL_DDA);
    outtextxy(lx, y, (char*)"[DDA LINE]");
    y += 14;
    setcolor(WHITE);
    outtextxy(lx, y, (char*)" Houses"); y+=12;
    outtextxy(lx, y, (char*)" Roads");  y+=12;
    outtextxy(lx, y, (char*)" Village"); y+=12;
    outtextxy(lx, y, (char*)" boundary"); y+=12;
    outtextxy(lx, y, (char*)" Player");  y+=12;
    outtextxy(lx, y, (char*)" outline");  y+=18;

    bresLine(PF_X2, y, WIN_W, y, COL_BOUNDARY); y+=8;

    // Bresenham entry
    setcolor(COL_BRES);
    outtextxy(lx, y, (char*)"[BRESENHAM]"); y+=14;
    setcolor(WHITE);
    outtextxy(lx, y, (char*)" Trees");    y+=12;
    outtextxy(lx, y, (char*)" Crystal");  y+=12;
    outtextxy(lx, y, (char*)" frame");    y+=12;
    outtextxy(lx, y, (char*)" Bridge");   y+=12;
    outtextxy(lx, y, (char*)" Shrine");   y+=12;
    outtextxy(lx, y, (char*)" walls");    y+=12;
    outtextxy(lx, y, (char*)" Paths");    y+=18;

    bresLine(PF_X2, y, WIN_W, y, COL_BOUNDARY); y+=8;

    // F1 hint
    setcolor(COL_CRYSTAL);
    outtextxy(lx, y, (char*)"Algorithms"); y+=12;
    outtextxy(lx, y, (char*)"visibly used"); y+=12;
    outtextxy(lx, y, (char*)"in game world");
}

// ────────────────────────────────────────────────────────────
//  Helper: fill background rectangle
// ────────────────────────────────────────────────────────────
void clearPlayfield(int bgCol)
{
    setfillstyle(SOLID_FILL, bgCol);
    bar(PF_X1, PF_Y1, PF_X2, PF_Y2);
}

// ────────────────────────────────────────────────────────────
//  DDA-drawn house (outline only)
// ────────────────────────────────────────────────────────────
//  bx,by = bottom-left corner; w=width; h=body height; rh=roof height
void drawHouse(int bx, int by, int w, int h, int rh)
{
    // Body  — DDA
    ddaRect(bx, by-h, bx+w, by, COL_HOUSE, 2);

    // Door  — DDA
    int dx = bx + w/2 - 6;
    ddaRect(dx, by-18, dx+12, by, COL_BRES, 1);

    // Window — DDA
    ddaRect(bx+5, by-h+8, bx+5+14, by-h+8+12, COL_DDA, 1);

    // Roof (triangle) — Bresenham (diagonal lines)
    int mx = bx + w/2;
    int ry = by - h - rh;
    bresThick(bx,    by-h, mx, ry,      COL_ROOF, 2);
    bresThick(bx+w,  by-h, mx, ry,      COL_ROOF, 2);
    bresThick(bx,    by-h, bx+w, by-h,  COL_ROOF, 1);
}

// ────────────────────────────────────────────────────────────
//  Bresenham-drawn tree
// ────────────────────────────────────────────────────────────
void drawTree(int cx, int ty, int tw, int th, int trkH)
{
    // Trunk — Bresenham vertical
    int tkx = cx - 4;
    bresRect(tkx, ty+th, tkx+8, ty+th+trkH, COL_TREE_T, 2);

    // Foliage triangle — Bresenham diagonals
    int top = ty;
    int left  = cx - tw/2;
    int right = cx + tw/2;
    bresThick(left,  ty+th, cx,    top,      COL_TREE_L, 2);
    bresThick(right, ty+th, cx,    top,      COL_TREE_L, 2);
    bresThick(left,  ty+th, right, ty+th,    COL_TREE_L, 1);
}

// ────────────────────────────────────────────────────────────
//  Player character outline — DDA
// ────────────────────────────────────────────────────────────
void drawPlayer(int cx, int cy)
{
    // Body rect — DDA
    ddaRect(cx-8,  cy-20, cx+8, cy+10, COL_PLAYER, 2);
    // Head circle approximated with DDA lines (octagon)
    int r=10;
    int ox=cx, oy=cy-30;
    int pts[8][2]={
        {ox-r,oy-4},{ox-4,oy-r},{ox+4,oy-r},{ox+r,oy-4},
        {ox+r,oy+4},{ox+4,oy+r},{ox-4,oy+r},{ox-r,oy+4}
    };
    for(int i=0;i<8;i++){
        int nx=(i+1)%8;
        ddaLine(pts[i][0],pts[i][1],pts[nx][0],pts[nx][1],COL_PLAYER);
    }
    // Sword — Bresenham diagonal line
    bresThick(cx+8, cy-10, cx+24, cy-26, COL_SWORD, 2);
    // Sword guard crosspiece — DDA
    ddaLine(cx+13,cy-15,cx+19,cy-21,COL_SWORD);
}

// ────────────────────────────────────────────────────────────
//  Light Crystal frame — Bresenham diamond
// ────────────────────────────────────────────────────────────
void drawCrystal(int cx, int cy, int r)
{
    // Diamond frame — Bresenham
    bresThick(cx,    cy-r,  cx+r,  cy,    COL_CRYSTAL, 2);
    bresThick(cx+r,  cy,    cx,    cy+r,  COL_CRYSTAL, 2);
    bresThick(cx,    cy+r,  cx-r,  cy,    COL_CRYSTAL, 2);
    bresThick(cx-r,  cy,    cx,    cy-r,  COL_CRYSTAL, 2);
    // Inner lines — Bresenham
    bresLine(cx, cy-r, cx,   cy+r, COL_CRYSTAL);
    bresLine(cx-r, cy, cx+r, cy,   COL_CRYSTAL);
    // Glow lines — DDA
    setcolor(COL_DDA);
    for(int a=0;a<360;a+=45){
        float rad=(float)a*3.14159f/180.f;
        int ex=cx+(int)((r+10)*cosf(rad));
        int ey=cy+(int)((r+10)*sinf(rad));
        drawDDA(cx,cy,ex,ey);
    }
}

// ────────────────────────────────────────────────────────────
//  Bridge — DDA planks + Bresenham rails
// ────────────────────────────────────────────────────────────
void drawBridge(int bx, int by, int bw, int bh)
{
    // Side rails — Bresenham
    bresThick(bx, by,    bx+bw, by,    COL_BRIDGE, 3);
    bresThick(bx, by+bh, bx+bw, by+bh, COL_BRIDGE, 3);
    // Planks — DDA verticals
    for(int x=bx+6;x<bx+bw;x+=10){
        ddaLine(x, by+2, x, by+bh-2, COL_BRIDGE);
    }
}

// ────────────────────────────────────────────────────────────
//  SCENE 1 — Lumen Village
// ────────────────────────────────────────────────────────────
void drawVillage()
{
    clearPlayfield(COL_BG_VILLAGE);

    // ── Village boundary wall — DDA ──
    ddaRect(PF_X1+10, PF_Y1+10, PF_X2-10, PF_Y2-10, COL_DDA, 2);

    // ── Dirt roads — DDA ──
    // Horizontal main road
    ddaThick(PF_X1+20, 340, PF_X2-20, 340, COL_ROAD, 28);
    // Vertical road to crystal
    ddaThick(370, PF_Y1+20, 370, 340, COL_ROAD, 22);

    // ── Houses — body DDA, roof Bresenham ──
    drawHouse(60,  320, 80, 70, 30);
    drawHouse(180, 290, 90, 70, 35);
    drawHouse(490, 310, 80, 65, 28);
    drawHouse(590, 320, 85, 70, 32);

    // ── Fence posts — DDA ──
    for(int x=PF_X1+15;x<PF_X2-15;x+=20){
        ddaThick(x, PF_Y2-22, x, PF_Y2-10, COL_BRES, 2);
    }
    // Fence top rail — DDA
    ddaLine(PF_X1+15, PF_Y2-18, PF_X2-15, PF_Y2-18, COLOR(100,70,30));

    // ── Lamp posts — Bresenham ──
    for(int lx : {150, 310, 440, 560}) {
        bresThick(lx, 280, lx, 340, COLOR(160,140,80), 2);
        bresLine(lx-8, 280, lx+8, 280, COLOR(160,140,80));
        bresLine(lx, 280, lx, 272, COLOR(200,190,100));
        // Lamp glow — DDA star
        setcolor(COLOR(240,220,100));
        for(int a=0;a<360;a+=60){
            float rad=(float)a*3.14159f/180.f;
            drawDDA(lx,(int)272, lx+(int)(8*cosf(rad)), 272+(int)(8*sinf(rad)));
        }
    }

    // ── Light Crystal — center ──
    drawCrystal(370, 200, 38);

    // ── Trees (small, decorative) — Bresenham ──
    drawTree(120, 140, 50, 50, 20);
    drawTree(620, 150, 50, 50, 20);
    drawTree( 80, 440, 44, 44, 18);
    drawTree(640, 450, 44, 44, 18);

    // ── Forest exit sign — DDA + Bresenham ──
    ddaRect(330, PF_Y2-48, 415, PF_Y2-28, COLOR(80,60,30), 2);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(335, PF_Y2-43, (char*)"FOREST >");
    bresThick(370, PF_Y2-28, 370, PF_Y2-12, COLOR(140,110,70), 2);

    // ── Elder NPC — DDA ──
    ddaRect(400, 270, 418, 310, COLOR(180,150,100), 2); // body
    ddaLine(404, 268, 414, 268, COLOR(200,170,120));     // head base
    ddaLine(409, 260, 409, 268, COLOR(200,170,120));     // head up
    // Staff — DDA
    ddaThick(418, 270, 430, 315, COLOR(140,100,60), 2);
    bresLine(426, 270, 434, 270, COLOR(140,100,60));     // staff top

    // ── Player ──
    drawPlayer(280, 310);

    // ── Labels — DDA algorithm markers ──
    setcolor(COL_DDA);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(62,  220, (char*)"[DDA] House");
    outtextxy(490, 240, (char*)"[DDA] House");
    outtextxy(310,  70, (char*)"[DDA] Boundary");
    setcolor(COL_BRES);
    outtextxy(80,  100, (char*)"[B] Tree");
    outtextxy(300, 155, (char*)"[B] Crystal");
    outtextxy(140, 250, (char*)"[B] Lamp");
}

// ────────────────────────────────────────────────────────────
//  SCENE 2 — Dark Forest
// ────────────────────────────────────────────────────────────
void drawForest()
{
    clearPlayfield(COL_BG_FOREST);

    // ── Forest boundary — DDA ──
    ddaRect(PF_X1+10, PF_Y1+10, PF_X2-10, PF_Y2-10, COL_DDA, 2);

    // ── Ground path — DDA ──
    ddaThick(PF_X1+20, 500, 420, 500, COL_ROAD, 22);
    ddaThick(420, 500, 420, PF_Y1+20, COL_ROAD, 22);

    // ── Many trees — Bresenham ──
    int treePosX[] = { 60, 130, 220, 310, 510, 570, 620, 670, 50, 100, 200, 650, 700};
    int treePosY[] = {120, 180, 110, 160, 130, 200, 100, 170, 280, 360, 400, 280, 360};
    int treeSzW[]  = { 56,  48,  60,  52,  58,  46,  54,  50,  50,  44,  52,  48,  54};
    int treeSzH[]  = { 60,  50,  64,  54,  60,  48,  56,  52,  50,  44,  52,  48,  54};
    int treeTrk[]  = { 24,  20,  26,  22,  24,  20,  22,  22,  20,  18,  22,  20,  22};
    for(int i=0;i<13;i++){
        drawTree(treePosX[i], treePosY[i], treeSzW[i], treeSzH[i], treeTrk[i]);
    }

    // ── Bridge — DDA planks + Bresenham rails ──
    drawBridge(200, 455, 220, 30);

    // ── River banks — Bresenham ──
    bresThick(PF_X1+20, 455, PF_X2-20, 455, COLOR(40,60,130), 3);
    bresThick(PF_X1+20, 487, PF_X2-20, 487, COLOR(40,60,130), 3);
    // River fill lines — DDA
    for(int y=458;y<485;y+=3){
        ddaLine(PF_X1+20, y, PF_X2-20, y, COLOR(30,50,110));
    }

    // ── Rocks — DDA octagons ──
    auto drawRock=[](int rx,int ry,int rs){
        int p[8][2]={
            {rx-rs,ry-rs/2},{rx-rs/2,ry-rs},{rx+rs/2,ry-rs},{rx+rs,ry-rs/2},
            {rx+rs,ry+rs/2},{rx+rs/2,ry+rs},{rx-rs/2,ry+rs},{rx-rs,ry+rs/2}
        };
        for(int i=0;i<8;i++){
            int n=(i+1)%8;
            ddaLine(p[i][0],p[i][1],p[n][0],p[n][1],COLOR(100,90,90));
        }
    };
    drawRock(160, 400, 16);
    drawRock(340, 380, 14);
    drawRock(520, 430, 18);

    // ── Enemy creatures — DDA body outline ──
    // Simple slime-like shapes
    auto drawEnemy=[](int ex,int ey){
        // Body — DDA rectangle
        ddaRect(ex-16,ey-14,ex+16,ey+14,COLOR(140,40,140),2);
        // Eyes — DDA
        ddaLine(ex-7,ey-6,ex-3,ey-6,COLOR(255,100,100));
        ddaLine(ex+3,ey-6,ex+7,ey-6,COLOR(255,100,100));
        // Mouth — DDA
        ddaLine(ex-6,ey+4,ex+6,ey+4,COLOR(255,80,80));
    };
    drawEnemy(140, 300);
    drawEnemy(350, 310);
    drawEnemy(500, 320);

    // ── Mysterious traveler — DDA ──
    ddaRect(560, 430, 578, 470, COLOR(80,80,160), 2);
    ddaLine(565, 428, 573, 428, COLOR(80,80,160));
    ddaLine(569, 420, 569, 428, COLOR(80,80,160));
    // Traveler's cloak — Bresenham diagonals
    bresThick(560, 430, 554, 470, COLOR(60,60,140), 2);
    bresThick(578, 430, 584, 470, COLOR(60,60,140), 2);

    // ── Shrine entrance arrow — Bresenham ──
    bresThick(580, 120, 620, 120, COLOR(200,200,80), 2);
    bresThick(610, 112, 622, 120, COLOR(200,200,80), 2);
    bresThick(610, 128, 622, 120, COLOR(200,200,80), 2);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(570, 100, (char*)"SHRINE");

    // ── Labels ──
    setcolor(COL_DDA);
    outtextxy(200, PF_Y1+15, (char*)"[DDA] Path / Boundary");
    outtextxy(140, 380,      (char*)"[DDA] Rock");
    setcolor(COL_BRES);
    outtextxy( 55, 75,       (char*)"[B] Tree");
    outtextxy(200, 438,      (char*)"[B] Bridge Rails");
    outtextxy( 30, 440,      (char*)"[B] River");
}

// ────────────────────────────────────────────────────────────
//  SCENE 3 — Abandoned Shrine
// ────────────────────────────────────────────────────────────
void drawShrine()
{
    clearPlayfield(COL_BG_SHRINE);

    // ── Outer stone floor — DDA ──
    ddaRect(PF_X1+10, PF_Y1+10, PF_X2-10, PF_Y2-10, COL_DDA, 2);

    // ── Floor grid lines — DDA ──
    for(int x=PF_X1+30;x<PF_X2-20;x+=40){
        ddaLine(x, PF_Y1+20, x, PF_Y2-20, COLOR(50,45,60));
    }
    for(int y=PF_Y1+30;y<PF_Y2-20;y+=40){
        ddaLine(PF_X1+20, y, PF_X2-20, y, COLOR(50,45,60));
    }

    // ── Shrine walls — Bresenham ──
    bresRect(60, PF_Y1+40, PF_X2-70, PF_Y2-40, COL_SHRINE, 4);

    // ── Inner room — Bresenham ──
    bresRect(120, PF_Y1+80, PF_X2-130, PF_Y2-80, COL_SHRINE, 3);

    // ── Door arch — Bresenham ──
    // Vertical door sides
    bresThick(310, PF_Y2-80, 310, PF_Y2-40, COLOR(80,70,90), 3);
    bresThick(430, PF_Y2-80, 430, PF_Y2-40, COLOR(80,70,90), 3);
    // Door lintel
    bresThick(310, PF_Y2-80, 430, PF_Y2-80, COLOR(80,70,90), 3);
    // Arch diagonal — Bresenham
    bresThick(310, PF_Y2-80, 370, PF_Y2-100, COLOR(80,70,90), 2);
    bresThick(430, PF_Y2-80, 370, PF_Y2-100, COLOR(80,70,90), 2);

    // ── Decorative cross pattern on wall — DDA ──
    for(int i=0;i<3;i++){
        int px = 150 + i*200;
        ddaLine(px,   PF_Y1+100, px,   PF_Y1+160, COL_DDA);
        ddaLine(px-30,PF_Y1+130, px+30,PF_Y1+130, COL_DDA);
    }

    // ── Columns — DDA rectangles ──
    ddaRect(120,  PF_Y1+80,  160, PF_Y1+160, COLOR(100,95,110), 2);
    ddaRect(580,  PF_Y1+80,  620, PF_Y1+160, COLOR(100,95,110), 2);
    ddaRect(120,  PF_Y2-160, 160, PF_Y2-80,  COLOR(100,95,110), 2);
    ddaRect(580,  PF_Y2-160, 620, PF_Y2-80,  COLOR(100,95,110), 2);

    // ── Guardian — Bresenham large frame ──
    int gx=370, gy=250;
    bresRect(gx-40,gy-60,gx+40,gy+40, COL_GUARDIAN, 3);  // body
    bresRect(gx-24,gy-88,gx+24,gy-60, COL_GUARDIAN, 3);  // head
    // Guardian horns — Bresenham
    bresThick(gx-24, gy-88, gx-34, gy-110, COL_GUARDIAN, 2);
    bresThick(gx+24, gy-88, gx+34, gy-110, COL_GUARDIAN, 2);
    // Guardian eyes — DDA
    ddaLine(gx-15, gy-78, gx-7,  gy-78, COLOR(255,80,80));
    ddaLine(gx+ 7, gy-78, gx+15, gy-78, COLOR(255,80,80));
    // Guardian arms — Bresenham
    bresThick(gx-40, gy-30, gx-70, gy,    COL_GUARDIAN, 3);
    bresThick(gx+40, gy-30, gx+70, gy,    COL_GUARDIAN, 3);
    // Weapon — Bresenham
    bresThick(gx+70, gy, gx+90, gy-40, COLOR(180,100,100), 3);

    // ── Light Shard — DDA star ──
    int sx=370, sy=420;
    setcolor(COL_SHARD);
    for(int a=0;a<360;a+=36){
        float sr1=24.f, sr2=12.f;
        float angle1=(float)a*3.14159f/180.f;
        float angle2=(float)(a+18)*3.14159f/180.f;
        int px1=sx+(int)(sr1*cosf(angle1)), py1=sy+(int)(sr1*sinf(angle1));
        int px2=sx+(int)(sr2*cosf(angle2)), py2=sy+(int)(sr2*sinf(angle2));
        drawDDA(sx,sy,px1,py1);
        drawDDA(px1,py1,px2,py2);
    }
    // Shard border — Bresenham diamond
    bresThick(sx,    sy-24, sx+16, sy,    COL_SHARD, 2);
    bresThick(sx+16, sy,    sx,    sy+24, COL_SHARD, 2);
    bresThick(sx,    sy+24, sx-16, sy,    COL_SHARD, 2);
    bresThick(sx-16, sy,    sx,    sy-24, COL_SHARD, 2);

    // ── Labels ──
    setcolor(COL_DDA);
    outtextxy(PF_X1+15, PF_Y1+15, (char*)"[DDA] Floor / Boundary");
    outtextxy(122,       PF_Y1+84, (char*)"[DDA] Columns");
    outtextxy(sx-12,    sy+28,    (char*)"[DDA] Shard");
    setcolor(COL_BRES);
    outtextxy(62,  PF_Y1+44, (char*)"[B] Shrine Walls");
    outtextxy(gx-38, gy-106, (char*)"[B] Guardian");
}

// ────────────────────────────────────────────────────────────
//  Main
// ────────────────────────────────────────────────────────────
int main()
{
    initwindow(WIN_W, WIN_H, "The Last Light — V1: Basic Lines");
    setbkcolor(BLACK);
    cleardevice();

    // Scene names
    const char* scenes[3] = { "Lumen Village", "Dark Forest", "Abandoned Shrine" };
    int currentScene = 0;

    // ── Draw loop ──
    bool running = true;
    while (running)
    {
        cleardevice();

        // Draw the current scene
        switch (currentScene)
        {
            case 0: drawVillage(); break;
            case 1: drawForest();  break;
            case 2: drawShrine();  break;
        }

        // Overlay HUD and legend on top
        drawHUD(scenes[currentScene], currentScene + 1);
        drawLegend();

        // Flush to screen
        // (WinBGIm double-buffer is not always available; use delay to
        //  avoid tearing on single-buffer mode)
        delay(16);

        // ── Input ──
        if (kbhit())
        {
            int key = getch();

            if (key == 27)  // ESC
            {
                running = false;
            }
            else if (key == 32 || key == 13)  // SPACE or ENTER
            {
                currentScene = (currentScene + 1) % 3;
            }
            else if (key == 0 || key == 0xE0)  // Extended key
            {
                key = getch();
                if (key == 77)      // Right arrow
                    currentScene = (currentScene + 1) % 3;
                else if (key == 75) // Left arrow
                    currentScene = (currentScene + 2) % 3;
            }
        }
    }

    closegraph();
    return 0;
}
