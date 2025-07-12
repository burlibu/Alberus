# Makefile per progetto ImGui
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -Iinclude -Iexternal/imgui -Iexternal/imgui/backends -Iassets

# File sorgente del tuo progetto
PROJECT_SOURCES = src/main.cpp src/custom_colors.cpp

# File sorgente di Dear ImGui
IMGUI_SOURCES = external/imgui/imgui.cpp \
                external/imgui/imgui_demo.cpp \
                external/imgui/imgui_draw.cpp \
                external/imgui/imgui_tables.cpp \
                external/imgui/imgui_widgets.cpp

# Backend (scegli quello che preferisci)
BACKEND_SOURCES = external/imgui/backends/imgui_impl_glfw.cpp \
                  external/imgui/backends/imgui_impl_opengl3.cpp

# Tutti i file sorgente
SOURCES = $(PROJECT_SOURCES) $(IMGUI_SOURCES) $(BACKEND_SOURCES)

# Nome dell'eseguibile
EXE = alberus

# Librerie necessarie
LIBS = -lGL $(shell pkg-config --static --libs glfw3)

# Regole di compilazione
all: $(EXE)

$(EXE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

clean:
	rm -f $(EXE)

.PHONY: all clean