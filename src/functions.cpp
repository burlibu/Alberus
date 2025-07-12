#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "custom_colors.h" // colori custom
#include "functions.h"

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
