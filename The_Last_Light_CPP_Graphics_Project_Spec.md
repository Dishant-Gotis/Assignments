# The Last Light — C++ `graphics.h` 2D RPG Implementation Specification

## Purpose

Build a small **top-down 2D RPG/adventure game in C++ using `graphics.h`** as an academic Computer Graphics project.

The game is inspired by the presentation and top-down adventure feel of **Eastward**, but it must be an original, much smaller project.

The key requirement is **progressive development across five independent versions**.

Each version must:

- Compile and run independently.
- Contain its own source code.
- Preserve the previous version's working behavior.
- Add only the new concepts assigned to that version.
- Demonstrate the required Computer Graphics algorithms inside the actual game.
- Avoid replacing the required algorithms with built-in `graphics.h` drawing functions.

The final result should be a short, visually coherent RPG taking roughly **5–10 minutes to complete**.

---

# 1. Story: The Last Light

## Setting

The game takes place in a small village called **Lumen**, surrounded by a dark forest.

At the center of the village is an ancient **Light Crystal**. Its light protects the village from creatures in the forest.

One evening, the crystal suddenly goes dark.

Without its light, strange creatures begin appearing around the village.

## Main Character

The player controls **Kai**, a young traveler from Lumen.

## Objective

The village elder tells Kai:

> "The crystal has lost its light. Find the lost Light Shard in the forest and bring it back."

Kai takes his sword and enters the forest.

## Forest

Kai explores a small forest area, encounters a few creatures, crosses a bridge, and meets a mysterious traveler.

The traveler reveals that the **Light Shard** is inside an abandoned shrine deeper in the forest.

## Shrine

Kai enters the shrine and encounters its Guardian.

After defeating the Guardian, Kai obtains the Light Shard.

## Ending

Kai returns to Lumen and places the shard inside the Light Crystal.

The village becomes bright again.

For a moment, a strange symbol appears inside the crystal.

The screen fades to black.

### THE END

The story should remain intentionally short. Do not add side quests, shops, crafting systems, large inventories, procedural generation, or a large open world.

---

# 2. Game World

There are exactly three main gameplay scenes.

```text
+-------------------+
|   LUMEN VILLAGE   |
|                   |
|      LIGHT        |
|     CRYSTAL       |
|                   |
|      KAI          |
|                   |
|   FOREST EXIT     |
+---------+---------+
          |
          v
+-------------------+
|      FOREST       |
|                   |
|  TREES            |
|      ENEMIES      |
|                   |
|  BRIDGE           |
|          SHRINE → |
+-------------------+
          |
          v
+-------------------+
|  ABANDONED SHRINE |
|                   |
|    GUARDIAN       |
|                   |
|   LIGHT SHARD     |
+-------------------+
          |
          v
      RETURN HOME
          |
          v
    CRYSTAL RESTORED
          |
          v
         END
```

---

# 3. Visual Style

Use a simple **top-down 2D / pixel-art-inspired** style.

Do not depend on large external sprite packs.

Prefer procedural geometric construction using:

- Points
- Lines
- Circles
- Rectangles
- Triangles
- Polygons
- Transformations
- Filling algorithms

Suggested appearance:

- Dark green forest
- Warm village lighting
- Stone-gray shrine
- Bright central crystal
- Simple cute enemy creatures
- Simple player character with a visible sword
- Minimal HUD

The project is primarily a **Computer Graphics algorithm demonstration**, so geometric/procedural graphics are preferred over bitmap assets.

---

# 4. Technical Constraints

## Language

C++

## Graphics library

`graphics.h`

Target the environment available to the student, such as WinBGIm / compatible `graphics.h` implementation.

Do not assume modern game engines such as:

- SDL
- SFML
- Unity
- Unreal
- OpenGL frameworks

unless explicitly required by the environment.

## Code philosophy

Keep the implementation:

- Modular
- Readable
- Commented
- Beginner-friendly
- Easy to demonstrate during a viva

Use functions/classes where they clearly improve organization, but avoid unnecessary architecture.

---

# 5. Required Computer Graphics Concepts

The final project must demonstrate all of the following:

## Line Algorithms

- DDA Line Drawing Algorithm
- Bresenham's Line Drawing Algorithm

## Circle Algorithms

- Bresenham's Circle Drawing Algorithm
- Midpoint Circle Drawing Algorithm

## Transformations

- Translation
- Scaling
- Rotation
- Shearing
- Composite Transformation

## Filling

- Seed / Boundary Fill
- Scan-Line Fill

---

# 6. IMPORTANT IMPLEMENTATION RULE

For objects intended to demonstrate an algorithm, **do not call the equivalent built-in drawing primitive instead**.

Examples:

Do not use:

```cpp
line(...)
```

as the implementation of the DDA/Bresenham demonstration.

Do not use:

```cpp
circle(...)
```

for circles that are supposed to demonstrate Bresenham Circle or Midpoint Circle.

Do not use:

```cpp
floodfill(...)
```

for the custom seed/boundary-fill demonstration.

Do not use a built-in polygon fill as a replacement for the custom scan-line fill algorithm.

Built-in primitives may be used sparingly for simple UI elements if necessary, but the core demonstrable game objects must use the implemented algorithms.

---

# 7. VERSIONED DEVELOPMENT PLAN

The project must be split into five stages.

## V1 — Basic Lines

### Goal

Create the first visual prototype using only line-based construction.

### Required algorithms

1. DDA Line Drawing
2. Bresenham Line Drawing

### Suggested custom functions

```cpp
void drawDDA(int x1, int y1, int x2, int y2);
void drawBresenhamLine(int x1, int y1, int x2, int y2);
```

### What the game should show

Create rough versions of the three areas:

### Village

- House outlines
- Roads
- Village boundary
- Crystal frame
- Player outline

### Forest

- Tree trunks/branches
- Map boundary
- Bridge
- Paths

### Shrine

- Shrine outline
- Walls
- Door
- Crystal/shard outline

Use DDA for some objects and Bresenham Line for others.

The implementation should make the use of both algorithms obvious.

### Gameplay

V1 does not need to be a full game.

A simple static scene or basic scene switching is sufficient.

### UI

Display:

```text
THE LAST LIGHT
VERSION 1
DDA + BRESENHAM LINE
```

Optionally show an on-screen legend identifying representative objects drawn with each algorithm.

---

# 8. VERSION 2 — Circle Algorithms

### Goal

Continue from V1 and add circular geometry.

### Required algorithms

1. Bresenham Circle
2. Midpoint Circle

### Suggested functions

```cpp
void drawBresenhamCircle(int xc, int yc, int r);
void drawMidpointCircle(int xc, int yc, int r);
```

### Use them in the actual game

Examples:

### Village

- Crystal glow rings
- Lamps
- Character eyes
- Decorative stones

### Forest

- Enemy bodies/heads
- Small environmental details
- Attack indicators

### Shrine

- Guardian eyes
- Circular shrine symbols
- Light Shard glow

Both circle algorithms must actually appear in game objects.

### UI

```text
THE LAST LIGHT
VERSION 2
LINES + CIRCLES
```

---

# 9. VERSION 3 — Transformations + Controls

### Goal

Turn the prototype into a basic playable game.

Add:

- Translation
- Scaling
- Rotation
- Shearing
- Composite transformations
- Keyboard input
- Player movement
- Basic collision
- Scene state

## Controls

Support:

```text
W / UP       = Move Up
S / DOWN     = Move Down
A / LEFT     = Move Left
D / RIGHT    = Move Right

E            = Interact / Talk
SPACE        = Attack
ESC          = Exit
```

Arrow keys are preferred in addition to WASD if practical.

## Translation

Use object position/state and translate objects when they move.

Player movement should be implemented through translation rather than merely redrawing unrelated hardcoded coordinates.

Example conceptual transformation:

```text
x' = x + tx
y' = y + ty
```

## Scaling

Use scaling for a visible effect such as:

- Crystal pulse
- Attack impact
- Hit effect
- Character interaction effect

Example:

```text
1.0 → 1.2 → 1.0
```

## Rotation

Use rotation for:

- Sword
- Attack direction
- Character-facing indicator

The sword should rotate depending on player direction.

## Shearing

Use a subtle visual effect, for example:

- Walking squash/skew
- Grass movement
- Attack effect
- Crystal energy effect

Make the effect visibly demonstrable but not disruptive.

## Composite transformation

Use multiple transformations on one object.

Recommended sword pipeline:

```text
Local sword geometry
        ↓
Scaling
        ↓
Rotation
        ↓
Translation to player's hand
```

The order should be deliberate and implemented in code.

---

# 10. V3 Gameplay

At minimum:

```text
TITLE
  ↓
VILLAGE
  ↓
Walk around
  ↓
Forest entrance
  ↓
FOREST
  ↓
Explore
  ↓
SHRINE
```

Add basic collision with:

- Map boundaries
- Houses
- Trees
- Shrine walls

Enemies can exist as simple moving/static obstacles.

Do not overbuild combat yet.

---

# 11. VERSION 4 — Filling + Visual Upgrade

### Goal

Keep all V3 behavior working, but make the world look substantially better.

Add:

- Custom Seed / Boundary Fill
- Custom Scan-Line Fill
- More colors
- Filled character
- Filled trees
- Filled houses
- Better terrain
- Better shrine
- Better crystal
- Better HUD

### IMPORTANT

V4 must be an **incremental upgrade**.

Do not rewrite the project into a different architecture that breaks V3 functionality.

All previously working:

- Movement
- Transformations
- Collision
- Scene switching

must continue to work.

---

# 12. Seed / Boundary Fill

Implement manually.

Example:

```cpp
void boundaryFill(int x, int y, int fillColor, int boundaryColor);
```

Use it for closed regions such as:

- Character clothing
- House interiors
- Crystal
- Enemy body
- Small decorative objects

Do not use `floodfill()` as the core implementation.

Because recursive flood-fill can overflow the stack, an iterative stack/queue-based implementation is acceptable and preferred if needed.

---

# 13. Scan-Line Fill

Implement a custom scan-line polygon filling algorithm.

Example conceptual API:

```cpp
void scanLineFill(const std::vector<Point>& polygon, int fillColor);
```

Use it for polygonal objects such as:

- Roofs
- Trees
- Shrine decorations
- Character body
- Large terrain shapes

Do not use `fillpoly()` as a replacement for the custom algorithm.

---

# 14. VERSION 4 VISUAL DESIGN

## Lumen Village

Should contain:

- Grass ground
- Dirt/stone paths
- 2–4 houses
- Trees
- Lamps
- Central Light Crystal
- Elder NPC
- Player
- Forest exit

## Forest

Should contain:

- Grass/forest ground
- Many trees
- Rocks
- Bridge
- 2–4 enemies
- Mysterious traveler
- Shrine entrance

## Shrine

Should contain:

- Stone floor
- Stone walls
- Decorative patterns
- Guardian
- Light Shard
- Glowing circular effects

---

# 15. VERSION 5 — FINAL GAME

### Goal

Turn V4 into the complete short RPG.

Everything from V1–V4 must remain functional.

Add:

- Complete story progression
- Dialogue system
- NPC interaction
- Enemy collision
- Basic combat
- Guardian battle
- Light Shard pickup
- Return objective
- Crystal restoration
- Ending sequence
- Title screen
- Game-over state if desired
- Restart option
- HUD
- Simple animations

---

# 16. FINAL GAMEPLAY FLOW

```text
TITLE SCREEN
     |
     v
LUMEN VILLAGE
     |
     | Talk to Elder
     v
Objective:
"Find the Light Shard."
     |
     v
FOREST
     |
     | Explore
     | Fight small enemies
     | Cross bridge
     | Talk to traveler
     v
ABANDONED SHRINE
     |
     | Fight Guardian
     v
LIGHT SHARD ACQUIRED
     |
     v
RETURN TO VILLAGE
     |
     v
INTERACT WITH LIGHT CRYSTAL
     |
     v
CRYSTAL RESTORED
     |
     v
STRANGE SYMBOL APPEARS
     |
     v
FADE / END SCREEN
```

---

# 17. Dialogue

Keep dialogue very short.

Example:

### Elder

```text
Elder:
"The Light Crystal has gone dark."

Elder:
"Without it, the forest creatures will reach us."

Elder:
"Find the Light Shard in the old shrine."
```

### Traveler

```text
Traveler:
"The shrine lies beyond the bridge."

Traveler:
"But its Guardian still protects the shard."
```

### After Guardian

```text
Kai:
"So this is the Light Shard..."
```

### Ending

```text
Kai:
"Lumen is safe again."

[The crystal flashes.]

[Strange symbol appears.]

THE END
```

Do not implement a complex branching dialogue system.

---

# 18. Combat

Keep combat extremely simple.

Player has:

```text
HP: 100
```

Enemies have small HP values.

Suggested controls:

```text
SPACE = attack
```

Attack can be:

- A rotated sword polygon/line structure
- A short-range hitbox
- A small visual impact effect

Use the transformation system for sword positioning and rotation.

Enemies should be simple enough that collision and damage are easy to understand.

---

# 19. Guardian

The Guardian should be the only real boss.

Keep it simple:

- Larger body
- Higher HP
- Slow movement
- Simple attack or contact damage

When its HP reaches zero:

```text
Guardian defeated
      ↓
Light Shard appears
      ↓
Player can collect it
```

---

# 20. Scene Management

Use a simple enum/state system.

Example:

```cpp
enum GameState {
    TITLE,
    VILLAGE,
    FOREST,
    SHRINE,
    ENDING,
    GAME_OVER
};
```

Do not make a complicated engine.

A simple loop is preferred:

```text
input
  ↓
update
  ↓
draw
  ↓
repeat
```

---

# 21. Suggested Code Organization

Even though every version must be independent, organize the final code into logical modules/functions.

Possible final structure:

```text
V5_Final_Game/
│
├── main.cpp
└── Makefile
```

Inside `main.cpp`, organize roughly as:

```cpp
// Configuration
// Data structures
// Global game state
// Pixel/primitive helpers
// DDA
// Bresenham line
// Bresenham circle
// Midpoint circle
// Transformations
// Seed / boundary fill
// Scan-line fill
// Drawing helpers
// Player
// Enemies
// NPCs
// Collision
// Input
// Dialogue
// Scene drawing
// Game update
// Main loop
```

If the implementation becomes too large, helper `.cpp/.h` files are allowed, but the folder must remain self-contained and independently buildable.

---

# 22. Makefiles

Each version folder must have its own `Makefile`.

The build system should be simple and should not require copying files from another version.

Because `graphics.h` installations differ, keep compiler/linker flags easy to edit.

A typical WinBGIm-style configuration may resemble:

```make
CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall
LDFLAGS := -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

TARGET := game
SRC := main.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
```

Do not assume these exact libraries are correct for every machine.

If the target environment requires different `graphics.h` linking flags, make the variables easy to modify.

Each version must support:

```text
make
make run
make clean
```

where supported by the environment.

---

# 23. Version Independence

This requirement is critical.

Each version must be a **snapshot of the project at that development stage**.

For example:

### V1

Only line algorithms and primitive line-based scenery.

### V2

V1 + circle algorithms.

### V3

V2 + transformations + keyboard controls + playability.

### V4

V3 + filling + visual polish.

### V5

V4 + complete story + combat + dialogue + ending.

Do not make V5 the only real code and create fake copies for V1–V4.

The earlier versions must genuinely represent earlier development stages.

---

# 24. Suggested File Layout

```text
The_Last_Light_CPP_Graphics/
│
├── README.md
├── The_Last_Light_CPP_Graphics_Project_Spec.md
│
├── V1_Basic_Lines/
│   ├── main.cpp
│   ├── Makefile
│   └── README.md
│
├── V2_Circles/
│   ├── main.cpp
│   ├── Makefile
│   └── README.md
│
├── V3_Transformations_Playable/
│   ├── main.cpp
│   ├── Makefile
│   └── README.md
│
├── V4_Filling/
│   ├── main.cpp
│   ├── Makefile
│   └── README.md
│
└── V5_Final_Game/
    ├── main.cpp
    ├── Makefile
    └── README.md
```

---

# 25. README Requirements for Each Version

Each version README should contain:

1. Version objective
2. New algorithms added
3. Controls, if applicable
4. What changed from previous version
5. How to build
6. How to run
7. Expected visual result
8. Computer Graphics concepts demonstrated

Example:

```text
## V3

### Added
- Translation
- Scaling
- Rotation
- Shearing
- Composite transformation
- Keyboard controls
- Collision

### Run
make
make run

### Controls
WASD / Arrow Keys = movement
SPACE = attack
E = interact
ESC = exit
```

---

# 26. Demonstration / Viva-Friendly Requirements

The project should make it easy to explain the algorithms.

Add an optional small debug overlay that can be toggled with a key such as `F1`.

The overlay can show:

```text
DDA LINE: USED
BRESENHAM LINE: USED
BRESENHAM CIRCLE: USED
MIDPOINT CIRCLE: USED

TRANSLATION: ACTIVE
SCALING: ACTIVE
ROTATION: ACTIVE
SHEARING: ACTIVE
COMPOSITE: ACTIVE

BOUNDARY FILL: USED
SCAN-LINE FILL: USED
```

This should not replace the actual in-game use of the algorithms.

It is only a demonstration aid.

---

# 27. Performance / Simplicity

The game is intentionally small.

Prioritize:

- Stable frame/update loop
- Correct drawing
- Readable code
- Simple collision
- No unnecessary external dependencies
- No asset pipeline
- No network
- No save system
- No procedural world generation

The final project should run comfortably on a normal student laptop.

---

# 28. Final Acceptance Checklist

The final project is complete only when:

## Graphics Algorithms

- [ ] DDA line implemented manually
- [ ] Bresenham line implemented manually
- [ ] Bresenham circle implemented manually
- [ ] Midpoint circle implemented manually
- [ ] Boundary/seed fill implemented manually
- [ ] Scan-line polygon fill implemented manually

## Transformations

- [ ] Translation implemented
- [ ] Scaling implemented
- [ ] Rotation implemented
- [ ] Shearing implemented
- [ ] Composite transformation implemented

## Game

- [ ] Title screen
- [ ] Village
- [ ] Forest
- [ ] Shrine
- [ ] Player movement
- [ ] Collision
- [ ] NPC interaction
- [ ] Dialogue
- [ ] Enemy
- [ ] Guardian
- [ ] Sword attack
- [ ] Light Shard
- [ ] Return to village
- [ ] Crystal restoration
- [ ] Ending

## Progressive Versions

- [ ] V1 independently runs
- [ ] V2 independently runs
- [ ] V3 independently runs
- [ ] V4 independently runs
- [ ] V5 independently runs
- [ ] Every version genuinely reflects its intended development stage

---

# 29. Instruction to the Coding Agent

When implementing this project:

1. Start with V1.
2. Do not skip directly to V5.
3. Make every version independently compilable.
4. Reuse conceptual geometry/code from the previous version only by copying it forward into the next version.
5. Do not retroactively add later algorithms to earlier versions.
6. Keep all required algorithms visibly used in actual game elements.
7. Preserve functionality between versions.
8. Prefer simple procedural graphics over external sprites.
9. Keep the story short.
10. Keep the code easy to explain in a college viva.
11. Comment the important algorithms and transformations.
12. Do not use built-in functions as hidden replacements for required algorithms.
13. Avoid overengineering.
14. Provide a `README.md` in the root and a `README.md` in every version folder.
15. Provide a working `Makefile` in every version folder.
16. At the end, ensure V5 is a complete playable game.

The objective is not to make a commercial-quality RPG. The objective is to produce a **small, polished, academically demonstrable 2D RPG whose visual evolution clearly shows the application of Computer Graphics algorithms and transformations.**
