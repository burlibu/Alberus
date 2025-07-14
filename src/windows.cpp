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
#include "windows.h"

namespace Gui {
    LoginWindow::LoginWindow(ImVec2 p, ImVec2 s) // inizializzazione costruttore Window
        : Window("Login", p, s) {}

    void LoginWindow::Render() {
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
    } // fine funzione Render
}