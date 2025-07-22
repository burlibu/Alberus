//standard
#include <iostream>
//imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
//src
#include "custom_colors.h"
#include "functions.h"

const ImVec4 rosso = {1.0f, 0.0f, 0.0f, 1.0f};
const ImVec4 arancione = {1.0f, 0.5f, 0.0f, 1.0f};
const ImVec4 verde_giada = hexToImVec4("70e000"); //#70e000
const ImVec4 ciano = hexToImVec4("124559"); //#124559
const ImVec4 crema = hexToImVec4("fdf0d5"); //#fdf0d5
const ImVec4 blu = hexToImVec4("003566"); //#003566
const ImVec4 bianco = ImVec4(1,1,1,1); //#ffffff
const ImVec4 nero = ImVec4(0,0,0,1); //#000000
const ImVec4 rosa = hexToImVec4("ffc8dd"); //#ffc8dd
const ImVec4 viola = hexToImVec4("BE00FF"); //#BE00FF
const ImVec4 verde = hexToImVec4("00FF00"); //#00FF00
const ImVec4 blu_chiaro = hexToImVec4("00CFFF"); //#00CFFF
const ImVec4 arancione_chiaro = hexToImVec4("FFA500"); //#FFA500
const ImVec4 arancione_oscuro = hexToImVec4("FF7F00"); //#FF7F00
const ImVec4 blu_oscuro = hexToImVec4("003566"); //#003566
const ImVec4 rosa_chiaro = hexToImVec4("FFC8DD"); //#FFC8DD
const ImVec4 rosa_oscuro = hexToImVec4("FFA500"); //#FFA500
const ImVec4 viola_chiaro = hexToImVec4("BE00FF"); //#BE00FF
const ImVec4 viola_oscuro = hexToImVec4("800080"); //#800080
const ImVec4 verde_chiaro = hexToImVec4("00FF00"); //#00FF00
const ImVec4 verde_oscuro = hexToImVec4("008000"); //#008000

