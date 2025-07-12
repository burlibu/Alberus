#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "env.h"
#include "settings.h"

#include "custom_colors.h"

// Funzione per creare stile personalizzaro
void style();

// Funzione modulo: Window Login Form
void RenderLoginForm();

ImVec4 hexToImVec4(const std::string& hex);