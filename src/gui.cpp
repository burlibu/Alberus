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
#include "gui.h"

namespace Gui {
    // Frame Window ////////////////////////////////////////////////////////////////////////////////////////////////////
    FrameWindowManager::FrameWindowManager(int width, int height, const std::string& t, GLFWmonitor *mon, GLFWwindow *sha) 
        : frame_window_width(width), frame_window_heigth(height), title(t.c_str()), monitor(mon), share(sha), frame_window(nullptr){
        // attenzione: qui perdi la proprietà di std::string ! -> ->  ^   
    }
    FrameWindowManager::~FrameWindowManager() {
        if (frame_window) {
            glfwDestroyWindow(frame_window);
        }
    }

    Error FrameWindowManager::Create() {
        frame_window = glfwCreateWindow(frame_window_width, frame_window_heigth, title.c_str(), monitor, share);
        if (!frame_window) return Error::FAIL;
        return Error::OK;
    }
    
    GLFWwindow* FrameWindowManager::getWindow() const {
        return frame_window;
    }


    // TODO guardare dove mettere i possibili return fail
    Error FrameWindowManager::RenderFrame(const ImVec4& clear_color) {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(frame_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(frame_window);
    return Error::OK;
    }

    void FrameWindowManager::CleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (frame_window) {
        glfwDestroyWindow(frame_window);
        frame_window = nullptr;
        }
    glfwTerminate();
    }


    //^ LoginWindow ////////////////////////////////////////////////////////////////////////////////////////////////////
    LoginWindow::LoginWindow(ImVec2 position, ImVec2 size, GLFWwindow* win) // inizializzazione costruttore Window
        : Window("Login", position, size, win) {} // gli sta passando questi parametri

    /**
     *  Parameters:
     * 
     * `const ImVec2& cursorpos` posizione del cursore dove sarà l' angolo alto sinistro della schermata
     * `const ImVec2& window_size` larghezza e altezza in un imvec2
     * Attenzione: chiama checkWindowSize se DEBUG è attivo
     */
    void LoginWindow::Render() {
        ImGui::SetNextWindowPos(pos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);
        if (ImGui::Begin(title.c_str(), &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings)) {
            ImGui::InputText("Username", username, IM_ARRAYSIZE(username));
            ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);
            if (ImGui::Button("Login")) {
                if (std::string(username) == "admin" && std::string(password) == "password") {
                    login_success = true;
                } else {
                    login_success = false;
                }
            }
            if (login_success) ImGui::TextColored(ImVec4(0,1,0,1), "Login Successful");
            if (!login_success) ImGui::TextColored(ImVec4(1,0,0,1), "Login Failed");
        }
        ImGui::End();
    } // fine funzione Render
    //^ ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //& ShowMyWindow //////////////////////////////////////////////////////////////////////////////////////////////////////
    ShowMyWindow::ShowMyWindow(ImVec2 position, ImVec2 size, GLFWwindow* win) 
        : Window("My window", position, size, win) {}
    /**
     *  Parameters:
     * 
     * `const ImVec2& cursorpos` posizione del cursore dove sarà l' angolo alto sinistro della schermata
     * `const ImVec2& window_size` larghezza e altezza in un imvec2
     * Attenzione: chiama checkWindowSize se DEBUG è attivo
     */
    void ShowMyWindow::Render() {
        ImGui::SetNextWindowPos(pos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);
        ImGui::Begin("Alberus [Cariddi#1]", &isOpen);
        ImGui::Text("Benvenuto nel mio progetto ImGui!");
        ImGui::Separator();
        
        ImGui::SliderFloat("Float Value", &my_float, 0.0f, 1.0f);
        ImGui::SliderInt("Int Value", &my_int, 0, 100);
        
        if (ImGui::Button("Click Me!")) {
            std::cout << "Bottone cliccato!" << std::endl;
            count++;
        }
        
        ImGui::SameLine();
        ImGui::Text("Counter: %d", count);
        
        ImGui::End();

        if (DEBUG) {
        checkWindowSizeChange(size);
        }
    }
    //& //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //! /////////////////////////////////////Minimize and exit window ////////////////////////////////////////////////////
    MinimizeAndExitWindow::MinimizeAndExitWindow(ImVec2 position, ImVec2 size, GLFWwindow* win) 
        : Window("MinimizeAndExitWindow", position, size, win) {};

    void MinimizeAndExitWindow::Render() {
        // Inizializzazione
        ImGui::SetNextWindowPos(pos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);
        ImGui::Begin("minimize_and_exit_window_id", &isOpen, bar_flags);
        //
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 4)); // padding interno dei bottoni (il blu)
        ImGui::SetCursorPosX(pos.x - ImGui::CalcTextSize("- X").x - 30); // calcolo per metterli a destra
        // Bottone Minimize
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, arancione); // hover arancione
        ImGui::PushStyleColor(ImGuiCol_Text, bianco); // testo bianco
        if (ImGui::Button("-")) {
            glfwHideWindow(window_ptr); // TODO trovare un modo per mettere window nella classe
            // TODO ho provato al posto di dichiararla nel main metterla in settings ma non funzionava
        }
        ImGui::PopStyleColor(2);
        ImGui::SameLine();

        // Bottone Exit
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, rosso); // hover rosso
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1,1,1,1)); // testo bianco
        if (ImGui::Button("X")) {
            exit(0);
        }
        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar();
        ImGui::End();

    }
}