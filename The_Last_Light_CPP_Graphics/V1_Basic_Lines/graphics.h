// ===========================================================================
//  Cross-Platform / Linux Native BGI (graphics.h) Implementation
//  Targeting Linux (X11 / WSLg) with fallback to Windows MinGW WinBGIm
// ===========================================================================

#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef _WIN32
// When compiling with MinGW on native Windows, use winbgim if available
#include <windows.h>
#include "winbgim.h"

#else
// Native Linux X11 Implementation of BGI / graphics.h

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <vector>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cstdint>
#include <chrono>
#include <thread>

// ── Color Constants ────────────────────────────────────────────────────────
#define BLACK           0x000000
#define BLUE            0x0000AA
#define GREEN           0x00AA00
#define CYAN            0x00AAAA
#define RED             0xAA0000
#define MAGENTA         0xAA00AA
#define BROWN           0xAA5500
#define LIGHTGRAY       0xAAAAAA
#define DARKGRAY        0x555555
#define LIGHTBLUE       0x5555FF
#define LIGHTGREEN      0x55FF55
#define LIGHTCYAN       0x55FFFF
#define LIGHTRED        0xFF5555
#define LIGHTMAGENTA    0xFF55FF
#define YELLOW          0xFFFF55
#define WHITE           0xFFFFFF

#define COLOR(r, g, b)  ((((r) & 0xFF) << 16) | (((g) & 0xFF) << 8) | ((b) & 0xFF))

// ── Styles & Fonts ─────────────────────────────────────────────────────────
#define SOLID_FILL      1
#define DEFAULT_FONT    0
#define BOLD_FONT       1
#define HORIZ_DIR       0
#define VERT_DIR        1

// ── Extended Key Codes ─────────────────────────────────────────────────────
#define KEY_HOME        71
#define KEY_UP          72
#define KEY_PGUP        73
#define KEY_LEFT        75
#define KEY_CENTER      76
#define KEY_RIGHT       77
#define KEY_END         79
#define KEY_DOWN        80
#define KEY_PGDN        81
#define KEY_F1          59

namespace bgi_internal {

// 8x8 font data for ASCII 32 to 127
static const uint8_t FONT_8X8[96][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 32 ' '
    {0x18,0x3C,0x3C,0x18,0x18,0x00,0x18,0x00}, // 33 '!'
    {0x66,0x66,0x24,0x00,0x00,0x00,0x00,0x00}, // 34 '"'
    {0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00}, // 35 '#'
    {0x18,0x3E,0x60,0x3C,0x06,0x7C,0x18,0x00}, // 36 '$'
    {0x00,0x66,0xA6,0xD4,0x2B,0x65,0x66,0x00}, // 37 '%'
    {0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00}, // 38 '&'
    {0x18,0x18,0x30,0x00,0x00,0x00,0x00,0x00}, // 39 '\''
    {0x0C,0x18,0x30,0x30,0x30,0x18,0x0C,0x00}, // 40 '('
    {0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x00}, // 41 ')'
    {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00}, // 42 '*'
    {0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00}, // 43 '+'
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30}, // 44 ','
    {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00}, // 45 '-'
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00}, // 46 '.'
    {0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00}, // 47 '/'
    {0x7C,0xC6,0xCE,0xD6,0xE6,0xC6,0x7C,0x00}, // 48 '0'
    {0x18,0x38,0x18,0x18,0x18,0x18,0x7E,0x00}, // 49 '1'
    {0x7C,0xC6,0x06,0x1C,0x30,0x66,0xFE,0x00}, // 50 '2'
    {0x7C,0xC6,0x06,0x3C,0x06,0xC6,0x7C,0x00}, // 51 '3'
    {0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x1E,0x00}, // 52 '4'
    {0xFE,0xC0,0xFC,0x06,0x06,0xC6,0x7C,0x00}, // 53 '5'
    {0x78,0x0C,0xC0,0xFC,0xC6,0xC6,0x7C,0x00}, // 54 '6'
    {0xFE,0xC6,0x0C,0x18,0x30,0x30,0x30,0x00}, // 55 '7'
    {0x7C,0xC6,0xC6,0x7C,0xC6,0xC6,0x7C,0x00}, // 56 '8'
    {0x7C,0xC6,0xC6,0x7E,0x06,0x0C,0x78,0x00}, // 57 '9'
    {0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x00}, // 58 ':'
    {0x00,0x18,0x18,0x00,0x18,0x18,0x30,0x00}, // 59 ';'
    {0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00}, // 60 '<'
    {0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00}, // 61 '='
    {0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x00}, // 62 '>'
    {0x7C,0xC6,0x0C,0x18,0x18,0x00,0x18,0x00}, // 63 '?'
    {0x7C,0xC6,0xDE,0xDE,0xDC,0xC0,0x7C,0x00}, // 64 '@'
    {0x38,0x6C,0xC6,0xFE,0xC6,0xC6,0xC6,0x00}, // 65 'A'
    {0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00}, // 66 'B'
    {0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00}, // 67 'C'
    {0xF8,0x6C,0x66,0x66,0x66,0x6C,0xF8,0x00}, // 68 'D'
    {0xFE,0x62,0x68,0x78,0x68,0x62,0xFE,0x00}, // 69 'E'
    {0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00}, // 70 'F'
    {0x3C,0x66,0xC0,0xC0,0xCE,0x66,0x3E,0x00}, // 71 'G'
    {0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00}, // 72 'H'
    {0x7E,0x18,0x18,0x18,0x18,0x18,0x7E,0x00}, // 73 'I'
    {0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00}, // 74 'J'
    {0xE6,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00}, // 75 'K'
    {0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00}, // 76 'L'
    {0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0x00}, // 77 'M'
    {0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00}, // 78 'N'
    {0x7C,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00}, // 79 'O'
    {0xFC,0x66,0x66,0x7C,0x60,0x60,0xF0,0x00}, // 80 'P'
    {0x7C,0xC6,0xC6,0xC6,0xD6,0xDE,0x7C,0x06}, // 81 'Q'
    {0xFC,0x66,0x66,0x7C,0x6C,0x66,0xE6,0x00}, // 82 'R'
    {0x7C,0xC6,0x60,0x38,0x0C,0xC6,0x7C,0x00}, // 83 'S'
    {0x7E,0x7E,0x18,0x18,0x18,0x18,0x18,0x00}, // 84 'T'
    {0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00}, // 85 'U'
    {0xC6,0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x00}, // 86 'V'
    {0xC6,0xC6,0xD6,0xFE,0xFE,0xEE,0xC6,0x00}, // 87 'W'
    {0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00}, // 88 'X'
    {0x66,0x66,0x66,0x3C,0x18,0x18,0x18,0x00}, // 89 'Y'
    {0xFE,0xC6,0x0C,0x18,0x30,0x63,0xFE,0x00}, // 90 'Z'
    {0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00}, // 91 '['
    {0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00}, // 92 '\'
    {0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00}, // 93 ']'
    {0x10,0x38,0x6C,0xC6,0x00,0x00,0x00,0x00}, // 94 '^'
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF}, // 95 '_'
    {0x30,0x18,0x0C,0x00,0x00,0x00,0x00,0x00}, // 96 '`'
    {0x00,0x00,0x78,0x0C,0x7C,0xCC,0x76,0x00}, // 97 'a'
    {0xE0,0x60,0x7C,0x66,0x66,0x66,0x7C,0x00}, // 98 'b'
    {0x00,0x00,0x78,0xCC,0xC0,0xCC,0x78,0x00}, // 99 'c'
    {0x1C,0x0C,0x7C,0xCC,0xCC,0xCC,0x76,0x00}, // 100 'd'
    {0x00,0x00,0x78,0xCC,0xFC,0xC0,0x78,0x00}, // 101 'e'
    {0x38,0x6C,0x60,0xF0,0x60,0x60,0xF0,0x00}, // 102 'f'
    {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0xF8}, // 103 'g'
    {0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00}, // 104 'h'
    {0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00}, // 105 'i'
    {0x06,0x00,0x0E,0x06,0x06,0x66,0x66,0x3C}, // 106 'j'
    {0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00}, // 107 'k'
    {0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, // 108 'l'
    {0x00,0x00,0xEC,0xFE,0xD6,0xD6,0xD6,0x00}, // 109 'm'
    {0x00,0x00,0xDC,0x66,0x66,0x66,0x66,0x00}, // 110 'n'
    {0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7C,0x00}, // 111 'o'
    {0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0}, // 112 'p'
    {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x1E}, // 113 'q'
    {0x00,0x00,0xDC,0x76,0x60,0x60,0xF0,0x00}, // 114 'r'
    {0x00,0x00,0x7C,0xC0,0x78,0x0C,0xF8,0x00}, // 115 's'
    {0x10,0x30,0x7C,0x30,0x30,0x34,0x18,0x00}, // 116 't'
    {0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x76,0x00}, // 117 'u'
    {0x00,0x00,0xC6,0xC6,0xC6,0x6C,0x38,0x00}, // 118 'v'
    {0x00,0x00,0xC6,0xD6,0xFE,0xFE,0x6C,0x00}, // 119 'w'
    {0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00}, // 120 'x'
    {0x00,0x00,0xC6,0xC6,0xCE,0x76,0x06,0xFC}, // 121 'y'
    {0x00,0x00,0xFE,0xCC,0x18,0x32,0xFE,0x00}, // 122 'z'
    {0x0E,0x18,0x18,0x70,0x18,0x18,0x0E,0x00}, // 123 '{'
    {0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00}, // 124 '|'
    {0x70,0x18,0x18,0x0E,0x18,0x18,0x70,0x00}, // 125 '}'
    {0x76,0xDC,0x00,0x00,0x00,0x00,0x00,0x00}, // 126 '~'
    {0x00,0x70,0xD8,0xD8,0x70,0x00,0x00,0x00}  // 127 degree / block
};

struct BgiState {
    Display* display = nullptr;
    Window window = 0;
    GC gc = nullptr;
    XImage* ximage = nullptr;
    std::vector<uint32_t> buffer;
    int width = 0;
    int height = 0;
    uint32_t fg_color = WHITE;
    uint32_t bg_color = BLACK;
    uint32_t fill_color = WHITE;
    int text_font = DEFAULT_FONT;
    int text_dir = HORIZ_DIR;
    int text_size = 1;
    std::queue<int> key_queue;
    Atom wm_delete_window = 0;
    bool is_open = false;
};

static BgiState g_bgi;

inline void process_events() {
    if (!g_bgi.is_open || !g_bgi.display) return;
    while (XPending(g_bgi.display) > 0) {
        XEvent ev;
        XNextEvent(g_bgi.display, &ev);
        if (ev.type == KeyPress) {
            KeySym ks;
            char buf[16];
            int count = XLookupString(&ev.xkey, buf, sizeof(buf), &ks, NULL);
            if (ks == XK_Escape) {
                g_bgi.key_queue.push(27);
            } else if (ks == XK_Return || ks == XK_KP_Enter) {
                g_bgi.key_queue.push(13);
            } else if (ks == XK_space) {
                g_bgi.key_queue.push(32);
            } else if (ks == XK_Left) {
                g_bgi.key_queue.push(0);
                g_bgi.key_queue.push(KEY_LEFT);
            } else if (ks == XK_Right) {
                g_bgi.key_queue.push(0);
                g_bgi.key_queue.push(KEY_RIGHT);
            } else if (ks == XK_Up) {
                g_bgi.key_queue.push(0);
                g_bgi.key_queue.push(KEY_UP);
            } else if (ks == XK_Down) {
                g_bgi.key_queue.push(0);
                g_bgi.key_queue.push(KEY_DOWN);
            } else if (ks == XK_F1) {
                g_bgi.key_queue.push(0);
                g_bgi.key_queue.push(KEY_F1);
            } else if (count > 0) {
                g_bgi.key_queue.push((uint8_t)buf[0]);
            }
        } else if (ev.type == ButtonPress) {
            // Left click advances scene like SPACE
            g_bgi.key_queue.push(32);
        } else if (ev.type == ClientMessage) {
            if ((Atom)ev.xclient.data.l[0] == g_bgi.wm_delete_window) {
                g_bgi.key_queue.push(27); // ESC to quit
            }
        }
    }
}

inline void flush_screen() {
    if (!g_bgi.is_open || !g_bgi.display || !g_bgi.ximage) return;
    XPutImage(g_bgi.display, g_bgi.window, g_bgi.gc, g_bgi.ximage, 0, 0, 0, 0, g_bgi.width, g_bgi.height);
    XFlush(g_bgi.display);
}

} // namespace bgi_internal

// ── BGI Public API Functions ───────────────────────────────────────────────

inline void initwindow(int width, int height, const char* title = "Graphics Window") {
    using namespace bgi_internal;
    
    // Auto-detect display (prefer current DISPLAY, fallback to :1 for WSLg, then :0)
    Display* d = XOpenDisplay(NULL);
    if (!d) d = XOpenDisplay(":1");
    if (!d) d = XOpenDisplay(":0");
    if (!d) {
        fprintf(stderr, "Error: Could not open X11 Display. Is DISPLAY=:1 or X server running?\n");
        exit(1);
    }
    
    g_bgi.display = d;
    g_bgi.width = width;
    g_bgi.height = height;
    g_bgi.buffer.assign(width * height, BLACK);

    int screen = DefaultScreen(d);
    Visual* visual = DefaultVisual(d, screen);
    int depth = DefaultDepth(d, screen);

    XSetWindowAttributes attrs;
    attrs.background_pixel = BlackPixel(d, screen);
    attrs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask | ButtonPressMask;

    g_bgi.window = XCreateWindow(d, RootWindow(d, screen), 50, 50, width, height, 0,
                                 depth, InputOutput, visual, CWBackPixel | CWEventMask, &attrs);

    XSelectInput(d, g_bgi.window, ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask | ButtonPressMask);

    XStoreName(d, g_bgi.window, title);

    g_bgi.wm_delete_window = XInternAtom(d, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(d, g_bgi.window, &g_bgi.wm_delete_window, 1);

    g_bgi.gc = XCreateGC(d, g_bgi.window, 0, NULL);

    g_bgi.ximage = XCreateImage(d, visual, depth, ZPixmap, 0,
                                (char*)g_bgi.buffer.data(), width, height, 32, 0);

    XMapWindow(d, g_bgi.window);

    // Wait until window is mapped
    XEvent ev;
    do {
        XNextEvent(d, &ev);
    } while (ev.type != MapNotify && ev.type != Expose);

    g_bgi.is_open = true;
    flush_screen();
}

inline void closegraph() {
    using namespace bgi_internal;
    if (!g_bgi.is_open) return;
    if (g_bgi.ximage) {
        g_bgi.ximage->data = nullptr; // do not free buffer memory through XDestroyImage
        XDestroyImage(g_bgi.ximage);
        g_bgi.ximage = nullptr;
    }
    if (g_bgi.gc) { XFreeGC(g_bgi.display, g_bgi.gc); g_bgi.gc = nullptr; }
    if (g_bgi.window) { XDestroyWindow(g_bgi.display, g_bgi.window); g_bgi.window = 0; }
    if (g_bgi.display) { XCloseDisplay(g_bgi.display); g_bgi.display = nullptr; }
    g_bgi.is_open = false;
}

inline void setcolor(int color) {
    bgi_internal::g_bgi.fg_color = (uint32_t)(color & 0x00FFFFFF);
}

inline int getcolor() {
    return (int)bgi_internal::g_bgi.fg_color;
}

inline void setbkcolor(int color) {
    bgi_internal::g_bgi.bg_color = (uint32_t)(color & 0x00FFFFFF);
}

inline void setfillstyle(int /*pattern*/, int color) {
    bgi_internal::g_bgi.fill_color = (uint32_t)(color & 0x00FFFFFF);
}

inline void putpixel(int x, int y, int color) {
    using namespace bgi_internal;
    if (x >= 0 && x < g_bgi.width && y >= 0 && y < g_bgi.height) {
        g_bgi.buffer[y * g_bgi.width + x] = (uint32_t)(color & 0x00FFFFFF);
    }
}

inline int getpixel(int x, int y) {
    using namespace bgi_internal;
    if (x >= 0 && x < g_bgi.width && y >= 0 && y < g_bgi.height) {
        return (int)(g_bgi.buffer[y * g_bgi.width + x] & 0x00FFFFFF);
    }
    return 0;
}

inline void cleardevice() {
    using namespace bgi_internal;
    uint32_t bg = g_bgi.bg_color;
    for (size_t i = 0; i < g_bgi.buffer.size(); ++i) {
        g_bgi.buffer[i] = bg;
    }
}

inline void bar(int left, int top, int right, int bottom) {
    using namespace bgi_internal;
    int x1 = (left < right) ? left : right;
    int x2 = (left < right) ? right : left;
    int y1 = (top < bottom) ? top : bottom;
    int y2 = (top < bottom) ? bottom : top;

    if (x1 < 0) x1 = 0;
    if (x2 >= g_bgi.width) x2 = g_bgi.width - 1;
    if (y1 < 0) y1 = 0;
    if (y2 >= g_bgi.height) y2 = g_bgi.height - 1;

    uint32_t col = g_bgi.fill_color;
    for (int y = y1; y <= y2; ++y) {
        int row_offset = y * g_bgi.width;
        for (int x = x1; x <= x2; ++x) {
            g_bgi.buffer[row_offset + x] = col;
        }
    }
}

inline void settextstyle(int font, int direction, int charsize) {
    using namespace bgi_internal;
    g_bgi.text_font = font;
    g_bgi.text_dir = direction;
    g_bgi.text_size = (charsize > 0) ? charsize : 1;
}

inline void outtextxy(int x, int y, const char* text) {
    using namespace bgi_internal;
    if (!text) return;
    bool bold = (g_bgi.text_font == BOLD_FONT);

    int cx = x;
    int cy = y;
    uint32_t col = g_bgi.fg_color;

    for (size_t c = 0; c < strlen(text); ++c) {
        unsigned char ch = (unsigned char)text[c];
        if (ch < 32 || ch > 127) ch = '?';
        const uint8_t* glyph = FONT_8X8[ch - 32];

        for (int row = 0; row < 8; ++row) {
            uint8_t bits = glyph[row];
            for (int col_i = 0; col_i < 8; ++col_i) {
                if (bits & (0x80 >> col_i)) {
                    putpixel(cx + col_i, cy + row, col);
                    if (bold) {
                        putpixel(cx + col_i + 1, cy + row, col);
                    }
                }
            }
        }
        cx += 8 + (bold ? 1 : 0);
    }
}

inline void delay(int ms) {
    bgi_internal::flush_screen();
    bgi_internal::process_events();
    if (ms > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
    bgi_internal::process_events();
}

inline int kbhit() {
    bgi_internal::process_events();
    return !bgi_internal::g_bgi.key_queue.empty();
}

inline int getch() {
    while (!kbhit()) {
        delay(10);
    }
    int k = bgi_internal::g_bgi.key_queue.front();
    bgi_internal::g_bgi.key_queue.pop();
    return k;
}

#endif // _WIN32
#endif // GRAPHICS_H
