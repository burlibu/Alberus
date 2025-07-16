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


int main() {
    // Inizializza GLFW
    if (!glfwInit()) {
        std::cerr << "Errore nell'inizializzazione di GLFW" << std::endl;
        return -1;
    }

    // Crea la finestra
    Gui::FrameWindowManager frame_window_manager(frame_window_width_setting,frame_window_heigth_setting,frame_window_title_setting,frame_window_monitor_setting,
                                                frame_window_share_setting);
    frame_window_manager.Create();
    

    glfwMakeContextCurrent(frame_window_manager.getWindow());
    glfwSwapInterval(1); // VSync

    // Inizializza Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(frame_window_manager.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    //calcolo width and heigth finestra
    int minimize_and_exit_window_w, minimize_and_exit_window_h;
    glfwGetFramebufferSize(frame_window_manager.getWindow(), &minimize_and_exit_window_w, &minimize_and_exit_window_h);

    // Istanziazione classi finestre
    Gui::LoginWindow loginWin(ImVec2(100, 100), ImVec2(500, 400), frame_window_manager.getWindow());
    Gui::ShowMyWindow mywin(ImVec2(100, 100), ImVec2(500, 400), frame_window_manager.getWindow()); // classe loginWindow creata
    Gui::MinimizeAndExitWindow minimize_and_exit_window(ImVec2(0,0),ImVec2(minimize_and_exit_window_w,35.0f), frame_window_manager.getWindow(),flags_minimize_and_exit_window);
     

    //* /////////////////////////////////////////////////////////// Loop principale ///////////////////////////////////////////////////////
    while (!glfwWindowShouldClose(frame_window_manager.getWindow())) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    //^ ///////////////////////////////////////////////////////// Render Login Form //////////////////////////////////////////////////////
        if (showRenderLoginForm) {
        loginWin.Render();
        }
    //^ //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
    //£ ///////////////////////////////////////////////////////My Window /////////////////////////////////////////////////////////////////
        if (show_my_window) {
            mywin.Render();
        }
    //£ /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //! ///////////////////////////////////////////////////////////
        //! MINIMIZE AND EXIT WINDOW //////////////////////////////////
        //! ///////////////////////////////////////////////////////////
        if (minimize_and_exit_window_bool) {
            minimize_and_exit_window.Render();
        }
        //! ///////////////////////////////////////////////////////////

//*  /////////////////////////////////////////////////// Window1 ////////////////////////////////////
        ImGui::SetNextWindowPos(ImVec2(500,100));
        ImGui::SetNextWindowSize(ImVec2(600,400)); //£ MEMO 2
        if (window1) {
            ImGui::Begin("Window1", &window1);

            if (ImGui::Button("My button", ImVec2(100,100))) {
                // tutto quello in questo if verrà eseguito quando il bottone sarà premuto
                ImGui::Text("You pressed the button");
            }
            bool checkBoxValue = true;
            ImGui::Checkbox("CheckBox", &checkBoxValue);

            ImGui::SliderFloat("My Float Slider", &value1, 0.0f, 100.0f);

            ImGui::Combo("##id1", &current, items.data(), items.size());
            ImGui::SetCursorPosX(ImGui::GetWindowWidth()/2 - ImGui::CalcTextSize("This is some text").x/2);
            ImGui::Text("This is some text");
            ImGui::End();
        }
//* /////////////////////////////////////////////////////////////////////////////////////////////////////
        

        // Demo window (opzionale)
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }
        if (esperimenti_window) {
            ImGui::Begin("Esperimenti");

            // Input text
            static char text[128] = "";
            ImGui::InputText("Nome", text, IM_ARRAYSIZE(text));

            // Checkbox
            static bool checkbox = false;
            ImGui::Checkbox("Attiva checkbox", &checkbox);

            // Radio buttons
            static int radio = 0;
            ImGui::RadioButton("Opzione 1", &radio, 0);
            ImGui::RadioButton("Opzione 2", &radio, 1);

            // Color picker
            static float color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
            ImGui::ColorEdit4("Colore", color);

            ImGui::End();

        }
        // Aggiungi questi nel tuo loop principale

        // Rendering
        frame_window_manager.RenderFrame(blu);
    } // fine while principale

    // Cleanup
    frame_window_manager.CleanUp();

    return 0;
}