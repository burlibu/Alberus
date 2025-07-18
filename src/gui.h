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
/**
 * Classe primaria
 */
class FrameWindowManager {
public:
    int frame_window_width; // la larghezza del frame
    int frame_window_heigth; // l' altezza del frame
    std::string title; // titolo del frame
    GLFWmonitor *monitor;  // The monitor to use for full screen mode, or NULL for windowed mode.
    GLFWwindow *share;  // The window whose context to share resources with, or NULL to not share resources

    
    FrameWindowManager(int width, int heigth, const std::string& t, GLFWmonitor *mon, GLFWwindow *sha); // costruttore
    ~FrameWindowManager(); // distruttore
    /**
     * Funzione che genera la finestra principale del programma
     * `frame_window` : variabile in cui verrà messo il risultato della funzione
     * glfwCreateWindow()
     * se !main_window ritorna false
     */
    Error Create();
    /**
     * Funzione che ritorna il puntatore GLFWwindow* alla finestra principale
     */
    GLFWwindow* getWindow() const;
    Error RenderFrame(const ImVec4& clear_color);
    void CleanUp();

private:
    GLFWwindow* frame_window = nullptr;
};
/**
 * CLasse primaria
 */
class Window { // inizio class Window
protected:
    std::string title;
    ImVec2 pos;
    ImVec2 size;
    bool isOpen;
    ImGuiWindowFlags flags;
    

public:
    // Modifica il costruttore per accettare anche i flags (con default opzionale)
    Window(const std::string& t, ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f = 0)
        : title(t), pos(p), size(s), isOpen(true), flags(f), window_ptr(win)  {}
        
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
    int Area() {
        return size.x * size.y;
    }
protected:
    GLFWwindow* window_ptr;
}; // fine class window

//^ ///////////////////////////////////////////////////////// Login Window ///////////////////////////////////////////////////////////

class LoginWindow : public Window { // inizio classe LoginWindow
private:
    char username[64] = "";
    char password[64] = "";
    bool login_success = false;
    bool login_failed = false;
    

public:
    LoginWindow(ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f); // costruttore della classe
    void Render() override;
}; // fine classe loginWindow



//& ShowMyWindow /////////////////////////////////////////////////////////////////////////////////////////////////////

class ShowMyWindow : public Window {
public:
    ShowMyWindow(ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f); //il costruttore deve avere lo stesso nome della classe
    unsigned int count = 0; // counter del bottone clickMe
    void Render() override;
}; // fine class ShowMyWindow



class SettingsWindow : public Window {
    // TODO da implementare
};
//! ///////////////////////////////////////////Minimize and exit window ///////////////////////////////////////////////
class MinimizeAndExitWindow : public Window {
public:
    MinimizeAndExitWindow(ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f); // costruttore
    void Render() override;
    float bar_height = 30.0f;
    
}; // fine classe minimize and exit window

class showDemoWindow : public Window {
public:
    showDemoWindow(ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f);//costruttore
    void Render() override;
};

class EsperimentiWindow : public Window {
public:
    EsperimentiWindow(ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f); // costruttore
    void Render() override;
};

class Window1 : public Window {
public:
    Window1(ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f); // costruttore
    void Render() override;
};

} // fine namespace Gui
