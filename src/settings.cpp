//standards
#include <iostream>
#include <thread>
#include <vector>
//imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
//src
#include "settings.h"

ImGuiWindowFlags flags_minimize_and_exit_window =
    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
    | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus
    | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
// ImGuiWindowFlags flags_minimize_and_exit_window = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings 
//     | ImGuiWindowFlags_NoTitleBar;    
ImGuiWindowFlags flags_login_window = 0; // oppure i flag che vuoi
ImGuiWindowFlags flags_show_my_window = 0; // oppure i flag che vuoi

// Frame_window
GLFWwindow* frame_window = nullptr;
int frame_window_width_setting = 1280;
int frame_window_heigth_setting = 720;
std::string frame_window_title_setting = "Alberus Project";
GLFWmonitor *frame_window_monitor_setting;
GLFWwindow *frame_window_share_setting;

bool minimize_and_exit_window_bool = true;
bool show_demo_window              = false;
bool show_my_window                = true;
bool window1                       = false;
bool showRenderLoginForm           = true;

// Impostazioni Window 1 
float value1 =  0.1f;
int value2 = 1;
std::vector<const char*> items = {"item1", "item2", "item3"};
int current = 0;
//
bool esperimenti_window = false;
float my_float = 0.0f;
int my_int = 0;
