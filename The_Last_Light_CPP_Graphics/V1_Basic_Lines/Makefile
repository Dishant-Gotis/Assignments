# ============================================================
#  The Last Light — V1: Basic Lines
#  Makefile for WinBGIm / MinGW on Windows
# ============================================================
#
#  Adjust LIBPATH and INCPATH to match your WinBGIm install.
#  The defaults below assume the library lives two levels up
#  in  ../WinBGIm_Library6_0_Nov2005/
#
# ============================================================

CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wno-unused-result

# ── Paths ──────────────────────────────────────────────────
# Path to the folder containing graphics.h / winbgim.h
INCPATH  := ../../WinBGIm_Library6_0_Nov2005

# Path to the folder containing libbgi.a
LIBPATH  := ../../WinBGIm_Library6_0_Nov2005

# ── Linker flags for WinBGIm ───────────────────────────────
LDFLAGS  := -L$(LIBPATH) -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

# ── Targets ────────────────────────────────────────────────
TARGET   := game
SRC      := main.cpp

# ───────────────────────────────────────────────────────────
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -I. -I$(INCPATH) $(SRC) -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	del $(TARGET).exe 2>nul || rm -f $(TARGET)

.PHONY: all run clean
