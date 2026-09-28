# ============================================================
#  The Last Light — V1: Basic Lines
#  Cross-Platform Makefile (Linux / WSLg & Windows MinGW)
# ============================================================

CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wno-unused-result

# Detect OS
ifeq ($(OS),Windows_NT)
    # Windows MinGW configuration
    INCPATH := ../../WinBGIm_Library6_0_Nov2005
    LIBPATH := ../../WinBGIm_Library6_0_Nov2005
    LDFLAGS := -L$(LIBPATH) -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
    TARGET  := game.exe
    RM_CMD  := del $(TARGET) 2>nul || rm -f $(TARGET)
else
    # Linux (X11 / WSLg) configuration
    INCPATH := .
    LDFLAGS := -lX11 -lpthread
    TARGET  := game
    RM_CMD  := rm -f $(TARGET) game.exe
endif

SRC      := main.cpp

# ───────────────────────────────────────────────────────────
all: $(TARGET)

$(TARGET): $(SRC) graphics.h
	$(CXX) $(CXXFLAGS) -I. -I$(INCPATH) $(SRC) -o $(TARGET) $(LDFLAGS)

run: all
	@if [ -z "$$DISPLAY" ] || [ "$$DISPLAY" = ":0" ]; then \
		if [ -e /tmp/.X11-unix/X1 ]; then export DISPLAY=:1; fi; \
	fi; \
	./$(TARGET)

clean:
	$(RM_CMD)

.PHONY: all run clean
