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
    ImVec2 pos;
    ImVec2 size;
    std::string title;
    bool isOpen;

public:
    Window(const std::string& t, ImVec2 p, ImVec2 s)
        : title(t), pos(p), size(s), isOpen(true) {}

    virtual ~Window() = default;

    virtual void Render() = 0; // Funzione virtuale pura: ogni finestra la implementa

    void SetPos(const ImVec2& p) { pos = p; }
    void SetSize(const ImVec2& s) { size = s; }
    void SetTitle(const std::string& t) { title = t; }
    bool* GetOpenPtr() { return &isOpen; }
}; // fine class window

class LoginWindow : public Window { // inizio classe LoginWindow
private:
    char username[64] = "";
    char password[64] = "";
    bool login_success = false;
    bool login_failed = false;

public:
    LoginWindow(ImVec2 p, ImVec2 s) // costruttore della classe
        : Window("Login", p, s) {} // lista di inizializzazione : chiama il costruttore della classe base Windows e gli passa i paramatri "Login", p,s

    void Render() override {
        ImGui::SetNextWindowPos(pos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);
        if (ImGui::Begin(title.c_str(), &isOpen)) {
            ImGui::InputText("Username", username, IM_ARRAYSIZE(username));
            ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);
            if (ImGui::Button("Login")) {
                if (std::string(username) == "admin" && std::string(password) == "password") {
                    login_success = true;
                    login_failed = false;
                } else {
                    login_success = false;
                    login_failed = true;
                }
            }
            if (login_success) ImGui::TextColored(ImVec4(0,1,0,1), "Login Successful");
            if (login_failed) ImGui::TextColored(ImVec4(1,0,0,1), "Login Failed");
        }
        ImGui::End();
    }
}; // fine classe loginWindow

class SettingsWindow : public Window {
    // TODO da implementare
};

} // fine namespace Gui
