# V1 — Basic Lines

## Version Objective

Create the first visual prototype of *The Last Light* using only **line-based geometry**.

No circles, no fills, no keyboard interaction (scene switching only).  
Every visual element — houses, trees, roads, walls, characters — is drawn from lines alone.

---

## New Algorithms Added

| Algorithm | Function | Used For |
|---|---|---|
| **DDA Line** | `drawDDA()` | Houses, roads, village boundary, floor grid, player outline, rocks, paths |
| **Bresenham Line** | `drawBresenhamLine()` | Trees (trunk + foliage), crystal frame, bridge rails, shrine walls, guardian, lamp posts |

---

## Controls

| Key | Action |
|---|---|
| `SPACE` / `ENTER` | Advance to next scene |
| `← / →` Arrow Keys | Navigate scenes |
| `ESC` | Quit |

---

## What Changed From Previous Version

This is Version 1 — the starting point. No previous version.

---

## How to Build

> Requires **MinGW g++** and **WinBGIm** (`graphics.h` / `libbgi.a`).  
> The Makefile expects the library at `../../WinBGIm_Library6_0_Nov2005/`.  
> Edit `INCPATH` and `LIBPATH` in the Makefile if your setup differs.

```bash
make
```

Or manually:

```bash
g++ -std=c++17 -O2 -I../../WinBGIm_Library6_0_Nov2005 main.cpp -o game ^
    -L../../WinBGIm_Library6_0_Nov2005 -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

---

## How to Run

```bash
make run
```

Or directly:

```bash
./game
```

---

## Expected Visual Result

A **900 × 620** window divided into:

- **Top strip (HUD)**: Title, version label (`V1 — DDA + BRESENHAM LINE`), scene counter, controls hint
- **Main playfield**: One of three hand-drawn scenes
- **Right panel (Legend)**: Lists which objects use DDA vs. Bresenham

### Scene 1 — Lumen Village
Dark green ground, dirt road, 4 houses (DDA body, Bresenham roof), lamp posts, 4 decorative trees (Bresenham), central Light Crystal (Bresenham diamond + DDA glow rays), elder NPC, player with sword.

### Scene 2 — Dark Forest
Dense dark green, many trees (Bresenham), dirt path (DDA), bridge (DDA planks + Bresenham rails), river, rock outlines (DDA octagons), 3 enemies (DDA), mysterious traveler.

### Scene 3 — Abandoned Shrine
Stone-gray interior, floor grid (DDA), outer + inner walls (Bresenham), four columns (DDA), door arch (Bresenham), decorative cross patterns (DDA), Guardian (Bresenham), Light Shard star (DDA + Bresenham).

---

## Computer Graphics Concepts Demonstrated

- **DDA Line Drawing Algorithm** — incremental floating-point step line rasterization
- **Bresenham's Line Drawing Algorithm** — integer arithmetic error-correction line rasterization

Both algorithms implemented manually in `drawDDA()` and `drawBresenhamLine()`.  
No built-in `line()` calls are used for the demonstrated objects.
