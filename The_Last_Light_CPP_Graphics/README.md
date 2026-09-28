# The Last Light — C++ `graphics.h` 2D RPG

> A top-down 2D RPG built as a Computer Graphics academic project.  
> Demonstrates DDA, Bresenham, circle algorithms, 2D transformations, and filling algorithms progressively across five independently buildable versions.

---

## Story

The village of **Lumen** is protected by an ancient Light Crystal.  
One evening it goes dark.  
**Kai**, a young traveler, must venture into the dark forest, find a lost **Light Shard** inside an abandoned shrine, and restore the crystal before creatures take over the village.

---

## Project Structure

```
The_Last_Light_CPP_Graphics/
│
├── README.md                                  ← You are here
├── The_Last_Light_CPP_Graphics_Project_Spec.md
│
├── V1_Basic_Lines/           ← DDA + Bresenham Line
│   ├── main.cpp
│   ├── Makefile
│   └── README.md
│
├── V2_Circles/               ← + Bresenham Circle + Midpoint Circle
│   ├── main.cpp
│   ├── Makefile
│   └── README.md
│
├── V3_Transformations_Playable/   ← + Transformations + Keyboard
│   ├── main.cpp
│   ├── Makefile
│   └── README.md
│
├── V4_Filling/               ← + Boundary Fill + Scan-Line Fill
│   ├── main.cpp
│   ├── Makefile
│   └── README.md
│
└── V5_Final_Game/            ← Complete RPG
    ├── main.cpp
    ├── Makefile
    └── README.md
```

---

## Version Roadmap

| Version | Concepts Added | Status |
|---|---|---|
| **V1** | DDA Line, Bresenham Line | ✅ Done |
| **V2** | Bresenham Circle, Midpoint Circle | 🔜 Pending |
| **V3** | Translation, Scaling, Rotation, Shearing, Composite + Controls | 🔜 Pending |
| **V4** | Boundary/Seed Fill, Scan-Line Fill, Visual Polish | 🔜 Pending |
| **V5** | Full story, dialogue, combat, Guardian, ending | 🔜 Pending |

---

## Requirements

- **Compiler**: MinGW `g++` (C++17)
- **Graphics**: WinBGIm (`graphics.h` / `libbgi.a`) — included in `WinBGIm_Library6_0_Nov2005/`
- **OS**: Windows

---

## Quick Start (V1)

```bash
cd V1_Basic_Lines
make
make run
```

> Edit `INCPATH` / `LIBPATH` in the `Makefile` if your WinBGIm library is in a different location.

---

## Controls (V1)

| Key | Action |
|---|---|
| `SPACE` / `ENTER` | Next scene |
| `←` / `→` | Navigate scenes |
| `ESC` | Quit |

---

## CG Algorithm Checklist

### Lines
- [x] DDA Line — `drawDDA()`
- [x] Bresenham Line — `drawBresenhamLine()`

### Circles
- [ ] Bresenham Circle — `drawBresenhamCircle()`
- [ ] Midpoint Circle — `drawMidpointCircle()`

### Transformations
- [ ] Translation
- [ ] Scaling
- [ ] Rotation
- [ ] Shearing
- [ ] Composite

### Filling
- [ ] Boundary / Seed Fill — `boundaryFill()`
- [ ] Scan-Line Fill — `scanLineFill()`
