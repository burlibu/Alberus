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

    //calcolo width and heigth finestra in tempo reale
    int frame_width, frame_height;
    glfwGetFramebufferSize(frame_window_manager.getWindow(), &frame_width, &frame_height);
    GLFWwindow* frame_p = frame_window_manager.getWindow(); // pointer to the frame

    // Istanziazione classi finestre
    Gui::MinimizeAndExitWindow minimize_and_exit_window(ImVec2(0,0),ImVec2(frame_width,35.0f), frame_p,flags_minimize_and_exit_window);
    Gui::LoginWindow loginWin(ImVec2(100, 100), ImVec2(500, 400), frame_p, flags_login_window);
    Gui::ShowMyWindow mywin(ImVec2(100, 100), ImVec2(500, 400), frame_p, flags_my_window); // classe loginWindow creata
    Gui::showDemoWindow demoWindow(ImVec2(400,400), ImVec2(200,200), frame_p,flags_demo_window);
    Gui::EsperimentiWindow esperimenti_window(ImVec2(300,300), ImVec2(200,200), frame_p,flags_esperimenti_window);
    Gui::Window1 window1(ImVec2(100, 100), ImVec2(500, 400), frame_p, flags_window1);
    Gui::MenuBar menubar(ImVec2(0,0), ImVec2(0,0), frame_p, flags_menu_bar);
    Gui::TabWindow tabWindow("TabWindow", ImVec2(100,100), ImVec2(500,400), frame_p, flags_tab_window);
    Gui::Tree tree("Tree", ImVec2(600,100), ImVec2(500,400), frame_p, flags_tree);
    Gui::Table table("Table", ImVec2(100,100), ImVec2(500,400), frame_p, flags_table);
    Gui::SettingsWindow settingsWindow(ImVec2(0,0 + menubar.GetPos().y), ImVec2(frame_window_manager.frame_window_width,frame_window_manager.frame_window_heigth - menubar.GetPos().y), frame_p, flags_settings);
    Gui::BottomBar bottomBar("BomboClap", ImVec2(500,500), ImVec2(frame_width, 35.0f), frame_p, flags_BottomBar);







     

    //* /////////////////////////////////////////////////////////// Loop principale ///////////////////////////////////////////////////////
    while (!glfwWindowShouldClose(frame_window_manager.getWindow())) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    //^ ///////////////////////////////////////////////////////// Login Window ///////////////////////////////////////////////////////////
        if (bool_login_window) {
            loginWin.Render();
            loginWin.isLogged(); // TODO da rendere più sicuro ed efficiente
            if (!loginWin.logged){
                bool_my_window = false;
                bool_window1 = false;
                bool_demo_window = false;
                bool_esperimenti_window = false;
            } else {
                bool_my_window = true;
                bool_window1 = true;
                bool_demo_window = true;
                bool_esperimenti_window = true;
            }
        }
        
        
    //£ ///////////////////////////////////////////////////////My Window /////////////////////////////////////////////////////////////////
        if (bool_my_window) {
            mywin.Render();
        }
    
        
    //! ////////////////////////////////////////////////MINIMIZE AND EXIT WINDOW /////////////////////////////////////////////////////////
        if (bool_minimize_and_exit_window) {
            minimize_and_exit_window.Render();
        }
     

    //*  ////////////////////////////////////////////////////////// Window1 ///////////////////////////////////////////////////////////////
        if (bool_window1) {
            window1.Render();
        }

    // TODO /////////////////////////////////////////////////////// Demo Window ////////////////////////////////////////////////////////////
        if (bool_demo_window) {
            demoWindow.Render();
        }

    //? ///////////////////////////////////////////////////////// Esperimenti window //////////////////////////////////////////////////////
        if (bool_esperimenti_window) {
            esperimenti_window.Render();
        }
        

    ///////////////////////////////////////////////////////////// Menu Bar ///////////////////////////////////////////////////////////////
        if (bool_menu_bar) {
            menubar.Render();
        }

    //////////////////////////////////////////////////////////// Tab Window /////////////////////////////////////////////////////////////////
        if (bool_tab_window) {
            tabWindow.Render();
        }

    /////////////////////////////////////////////////////////// Tree ////////////////////////////////////////////////////////////////////////
    if (bool_Tree) {
        tree.Render();
    }
    /////////////////////////////////////////////////////////// Table //////////////////////////////////////////////////////////////////////////
    if (bool_table) {
        table.Render();
    }
    /////////////////////////////////////////////////////////// Settings Window //////////////////////////////////////////////////////////////////////////
    if (bool_settings) {
        settingsWindow.Render();
    }

    if (bool_BottomBar)
    {
        bottomBar.Render();
    }

    Rectangle(ImVec2(100,100), ImVec2(200,200), viola);
    Rectangle(ImVec2(600,100), ImVec2(100,200), rosso);
    Rectangle(ImVec2(300,500), ImVec2(100,50), blu_chiaro);
    Rectangle(ImVec2(400,500), ImVec2(100,50), verde);
    Rectangle(ImVec2(500,500), ImVec2(100,50), rosa);



    

    // Rendering frame principale
    frame_window_manager.RenderFrame(blu);
    } // fine while principale

    // Cleanup
    frame_window_manager.CleanUp();

    return 0;
}