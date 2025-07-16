#pragma once // serve a evitare che lo stesso header venga incluso più volte
//standard
#include <iostream>
#include <thread>
#include <vector>
//imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
//src
#include "env.h"

// frame che ospiterà le finestre

extern int frame_window_width_setting;
extern int frame_window_heigth_setting;
extern std::string frame_window_title_setting;
extern GLFWmonitor *frame_window_monitor_setting;
extern GLFWwindow *frame_window_share_setting;

extern bool minimize_and_exit_window_bool;
extern bool show_demo_window;
extern bool show_my_window;
extern bool window1;
extern bool showRenderLoginForm;

// Impostazioni Window 1 
extern float value1;
extern int value2;
extern std::vector<const char*> items;
extern int current;
//
extern bool esperimenti_window;
extern float my_float;
extern int my_int;