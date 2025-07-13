//standards
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
// imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
//src
#include "env.h"
#include "settings.h"

#include "custom_colors.h"

struct Notification;

// Funzione per creare stile personalizzaro
void style();

// Funzione modulo: Window Login Form
void RenderLoginForm();

// Funzione che prende una stringa colore come bde0fe o bde0fe80 e ritorna un ImVec4 corrispettivo
// Supporta stringhe da 6 o 8 caratteri
ImVec4 hexToImVec4(const std::string& hex);

void DrawGlowingRectangle();

// funzione che usa thread
void hardLoad();

int lavoro_lungo();

void esempio_future();

