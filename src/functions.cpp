//standard
#include <iostream>
#include <sstream>
#include <thread>
#include <future>
#include <chrono>
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

struct Notification {
    std::string title;
    std::string text;
    float duration;
    std::chrono::steady_clock::time_point start_time;
};

std::vector<Notification> notifications; // creazione vector di notifiche

// Funzione che crea una notifica dai parametri ma non la mostra. la aggiunge al vector di notifiche
// TODO cambiarla in modo da renderla utile per renderNotifications
void showNotification(const std::string& title, const std::string& text, int duration_ms) {
    Notification notification;
    notification.title = title;
    notification.text = text;
    notification.duration = duration_ms / 1000.0f; // dividiamo per mille così è in secondi
    notification.start_time = std::chrono::steady_clock::now();
    notifications.push_back(notification); // aggiunta della notifica al vettore di notifiche
}

// funzione che crea una finestra di notifica sullo schermo
void RenderNotifications() {
    ImGui::SetWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x-250, ImGui::GetIO().DisplaySize.y- 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(240,80), ImGuiCond_Always);

    for (long unsigned int i = 0; i < notifications.size();) {
        Notification& notification = notifications[i];
        float elapsed = std::chrono::duration<float>(std::chrono::steady_clock::now() - notification.start_time).count();

        if (elapsed > notification.duration) {
            notifications.erase(notifications.begin() + i);
        } 
        else {
            ImGui::Begin("Notification", nullptr, ImGuiWindowFlags_NoDecoration |  ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::TextWrapped("%s",notification.text.c_str()); // MEMO3
            ImGui::Separator();
            ImGui::TextWrapped("%s", notification.text.c_str()); //MEMO5
            ImGui::End();
            i++;
        }
    }
}

// Funzione per impostare gli stili
// TODO completarla
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
    ImGui::Begin("Simple Login Form");

    ImGui::InputText("username", username_input, IM_ARRAYSIZE(username_input));
    ImGui::InputText("password", password_input, IM_ARRAYSIZE(password_input), ImGuiInputTextFlags_Password);

    if(ImGui::Button("Login")) {
        if (username_input == username && password_input == password) {
            login_success = true;
        } 
    }
    if (login_success) {
        ImGui::TextColored(verde_giada, "Login Successful");
    } else ImGui::TextColored(rosso, "Login Failed");
    ImGui::End();
}


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

void DrawGlowingRectangle() {
    ImGui::Begin("Glowing Rectangle Window");

    // get current drawlist
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // define size and position
    ImVec2 pos = ImGui::GetCursorPos();
    ImVec2 rect_min = ImVec2(pos.x+50, pos.y+50);
    ImVec2 rect_max = ImVec2(pos.x+150, pos.y+150);

    // define glow and base color
    ImU32 glow_color = IM_COL32(0,150,255,60);
    ImU32 base_color = IM_COL32(0,150,255,255);

    //draw multiple layers of glowing effect with increased thickness
    for( int i = 0; i < 15; i++) {
        float glow_thickness = 10.0f + i * 3.0f;
        draw_list->AddRect(rect_min, rect_max, glow_color, 0.0f, ImDrawFlags_RoundCornersAll, glow_thickness);
    }
    draw_list->AddRectFilled(rect_min,rect_max,base_color);
    ImGui::End();
}

void HardLoad() {
    //simula lavoro lungo o pesante
    std::this_thread::sleep_for(std::chrono::seconds(5));
    //
    //std::thread t(hardLoad);
    //t.detach(); // Il thread lavora in background, non blocca il main thread
    //se invece vuoi apsettare che finisca prima di proseguire  usa t.join()
}

int lavoro_lungo() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 42; // risultato del calcolo
}

void esempio_future() {
    std::future<int> risultato = std::async(std::launch::async, lavoro_lungo);

    // Puoi fare altro mentre il thread lavora...

    // Quando ti serve il risultato:
    int valore = risultato.get(); // attende che il thread finisca
    std::cout << "Risultato: " << valore << std::endl;
}