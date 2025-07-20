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
  
ImGuiWindowFlags flags_login_window = 0; 
ImGuiWindowFlags flags_my_window = 0; 
ImGuiWindowFlags flags_demo_window = 0;
ImGuiWindowFlags flags_esperimenti_window = 0; 
ImGuiWindowFlags flags_window1 = 0; 



// Frame_window
GLFWwindow* frame_window = nullptr;
int frame_window_width_setting = 1280;
int frame_window_heigth_setting = 720;
std::string frame_window_title_setting = "Alberus Project";
GLFWmonitor *frame_window_monitor_setting;
GLFWwindow *frame_window_share_setting;

bool bool_minimize_and_exit_window      = true;
bool bool_demo_window                   = true;
bool bool_my_window                     = true;
bool bool_window1                       = true;
bool bool_login_window                  = true;
bool bool_esperimenti_window            = true;



// Impostazioni Window 1 
float value1 =  0.1f;
int value2 = 1;
std::vector<const char*> items = {"item1", "item2", "item3"};
int current = 0;
//
bool esperimenti_window = false;
float my_float = 0.0f;
int my_int = 0;


const std::string username = "admin";
const std::string password = "password";