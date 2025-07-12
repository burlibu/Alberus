#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>

#include "env.h"
#include "settings.h"
#include "functions.h"
#include "custom_colors.h"


void style() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = 20.0f;
    style.Colors[ImGuiCol_Button] = ImVec4(193.0f/255,60.0f/255,60.0f/255,255.0f/255);
};

const std::string username = "admin";
const std::string password = "password";

void RenderLoginForm() {
    static char username_input[64] = ""; 
    static char password_input[64] = "";
    static bool login_success = false;
    static bool login_failed = false;
    ImGui::Begin("Simple Login Form");

    ImGui::InputText("username", username_input, IM_ARRAYSIZE(username_input));
    ImGui::InputText("password", password_input, IM_ARRAYSIZE(password_input), ImGuiInputTextFlags_Password);

    if(ImGui::Button("Login")) {
        if (username_input == username && password_input == password) {
            login_success = true;
            login_failed = false;
        } else {
            login_success = false;
            login_failed = true;
        }
    }
    if (login_success) {
        ImGui::TextColored(ImVec4(0,1,0,1), "Login Successful");
    } else ImGui::TextColored(ImVec4(1,0,0,1), "Login Failed");
    ImGui::End();
}

// Funzione che prende una stringa colore come bde0fe o bde0fe80 e ritorna un ImVec4 corrispettivo
// Supporta stringhe da 6 o 8 caratteri
ImVec4 hexToImVec4(const std::string& hex) {
    std::string h = hex;
    if (h[0] == '#') h = h.substr(1);
    if (h.length() != 6 && h.length() != 8) return ImVec4(1,1,1,1); // fallback bianco
    unsigned int r, g, b, a = 255;
    std::stringstream ss;
    ss << std::hex << h.substr(0,2);
    ss >> r;
    ss.clear(); ss.str("");
    ss << std::hex << h.substr(2,2);
    ss >> g;
    ss.clear(); ss.str("");
    ss << std::hex << h.substr(4,2);
    ss >> b;
    if (h.length() == 8) {
        ss.clear(); ss.str("");
        ss << std::hex << h.substr(6,2);
        ss >> a;
    }
    return ImVec4(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
}

