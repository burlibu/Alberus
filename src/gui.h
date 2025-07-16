#pragma once
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
#include "env.h"
#include "settings.h"
#include "functions.h"
#include "custom_colors.h"

namespace Gui {

class FrameWindowManager {
public:
    int frame_window_width;
    int frame_window_heigth;
    std::string title;
    GLFWmonitor *monitor;
    GLFWwindow *share;

    
    FrameWindowManager(int width, int heigth, const std::string& t, GLFWmonitor *mon, GLFWwindow *sha); // costruttore
    ~FrameWindowManager(); // distruttore
    /**
     * Funzione che genera la finestra principale del programma
     * `frame_window` : variabile in cui verrà messo il risultato della funzione
     * glfwCreateWindow()
     * se !main_window ritorna false
     */
    Error Create();

    GLFWwindow* getWindow() const;
    Error RenderFrame(const ImVec4& clear_color);
    void CleanUp();

private:
    GLFWwindow* frame_window = nullptr;
    

};

class Window { // inizio class Window
protected:
    std::string title;
    ImVec2 pos;
    ImVec2 size;
    bool isOpen;
    

public:
    Window(const std::string& t, ImVec2 p, ImVec2 s, GLFWwindow* win)
        : title(t), pos(p), size(s), isOpen(true), window_ptr(win) {}
        
    // distruttore virtuale che garantisce corretta distruzione nella gerarchia
    virtual ~Window() = default; 
    // Funzione virtuale pura: ogni finestra la implementa
    virtual void Render() = 0; 

    void SetPos(const ImVec2& p) {
        pos = p; 
    }
    void SetSize(const ImVec2& s) {
        size = s; 
    }
    void SetTitle(const std::string& t) {
        title = t; 
    }
    bool* GetOpenPtr() {
        return &isOpen;
    }
protected:
    GLFWwindow* window_ptr;
}; // fine class window
//^ LoginWindow ////////////////////////////////////////////////////////////////////////////////////////////////////

class LoginWindow : public Window { // inizio classe LoginWindow
private:
    char username[64] = "";
    char password[64] = "";
    bool login_success = false;
    bool login_failed = false;
    

public:
    LoginWindow(ImVec2 p, ImVec2 s, GLFWwindow* win); // costruttore della classe
    void Render() override;
}; // fine classe loginWindow
//^ ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//& ShowMyWindow /////////////////////////////////////////////////////////////////////////////////////////////////////

class ShowMyWindow : public Window {
public:
    ShowMyWindow(ImVec2 p, ImVec2 s, GLFWwindow* win); //il costruttore deve avere lo stesso nome della classe
    unsigned int count = 0; // counter del bottone clickMe
    void Render() override;
};
//& //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class SettingsWindow : public Window {
    // TODO da implementare
};
//! ///////////////////////////////////////////Minimize and exit window ///////////////////////////////////////////////
class MinimizeAndExitWindow : public Window {
public:
    MinimizeAndExitWindow(ImVec2 p, ImVec2 s, GLFWwindow* win); // costruttore
    void Render() override;
    float bar_height = 30.0f;
    ImGuiWindowFlags bar_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar 
    | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing 
    | ImGuiWindowFlags_NoNav;
}; // fine classe minimize and exit window
} // fine namespace Gui
