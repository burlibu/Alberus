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

class Window { // inizio class Window
protected:
    std::string title;
    ImVec2 pos;
    ImVec2 size;
    bool isOpen;

public:
    Window(const std::string& t, ImVec2 p, ImVec2 s)
        : title(t), pos(p), size(s), isOpen(true) {}

    virtual ~Window() = default; // distruttore virtuale che garantisce distruzione nella gerarchia

    virtual void Render() = 0; // Funzione virtuale pura: ogni finestra la implementa

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
}; // fine class window
//^ LoginWindow ////////////////////////////////////////////////////////////////////////////////////////////////////

class LoginWindow : public Window { // inizio classe LoginWindow
private:
    char username[64] = "";
    char password[64] = "";
    bool login_success = false;
    bool login_failed = false;

public:
    LoginWindow(ImVec2 p, ImVec2 s); // costruttore della classe
    void Render() override;
}; // fine classe loginWindow
//^ ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//& ShowMyWindow /////////////////////////////////////////////////////////////////////////////////////////////////////

class ShowMyWindow : public Window {
public:
    ShowMyWindow(ImVec2 p, ImVec2 s); //il costruttore deve avere lo stesso nome della classe
    void Render() override;
};
//& //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class SettingsWindow : public Window {
    // TODO da implementare
};

} // fine namespace Gui
