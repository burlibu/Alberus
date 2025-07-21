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


    /**
     * Renderizza la finestra
     * `fwbc` : [frame_window_background_color]: color of the background
     */
    Error FrameWindowManager::RenderFrame(const ImVec4& fwbc) {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(frame_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(fwbc.x, fwbc.y, fwbc.z, fwbc.w);
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

    Window::WindowVertices Window::GetVertices () const{
        Window::WindowVertices verts;
        verts.p1 = pos;
        verts.p2 = ImVec2(pos.x + size.x, pos.y);
        verts.p3 = ImVec2(pos.x + size.x, pos.y + size.y);
        verts.p4 = ImVec2(pos.x, pos.y + size.y);
        return verts;
    }




    //^ LoginWindow ////////////////////////////////////////////////////////////////////////////////////////////////////
    LoginWindow::LoginWindow(ImVec2 position, ImVec2 size, GLFWwindow* win, ImGuiWindowFlags f) // inizializzazione costruttore Window
        : Window("Login", position, size, win, f) {} // gli sta passando questi parametri

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
            else ImGui::TextColored(ImVec4(1,0,0,1), "Login Failed");
        }
        ImGui::End();
    } // fine funzione Render

    void LoginWindow::isLogged(){
        if (login_success) {
            logged = true;
        } else logged = false;
    }
    //^ ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //& ShowMyWindow //////////////////////////////////////////////////////////////////////////////////////////////////////
    ShowMyWindow::ShowMyWindow(ImVec2 position, ImVec2 size, GLFWwindow* win, ImGuiWindowFlags f) 
        : Window("My window", position, size, win, f) {}
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
        ImGui::Begin("MyWindow", &isOpen);
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
        
        }
    }
    //& //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //! /////////////////////////////////////Minimize and exit window ////////////////////////////////////////////////////
    MinimizeAndExitWindow::MinimizeAndExitWindow(ImVec2 position, ImVec2 size, GLFWwindow* win, ImGuiWindowFlags f) 
        : Window("MinimizeAndExitWindow", position, size, win, f) {};

    void MinimizeAndExitWindow::Render() {
        // Aggiorna la larghezza della barra in base alla finestra principale
        int width, height;
        glfwGetFramebufferSize(window_ptr, &width, &height);
        size.x = width; // aggiorna la larghezza della barra
        // Mantieni la posizione sempre in alto a sinistra
        pos = ImVec2(0, 0);

        ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(size, ImGuiCond_Always);
        ImGui::Begin("minimize_and_exit_window_id", &isOpen, flags_minimize_and_exit_window);
        //
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 4)); // padding interno dei bottoni (il blu)
        // Posiziona i bottoni a destra
        float windowWidth = ImGui::GetWindowWidth();
        ImGui::SetCursorPosX(windowWidth - ImGui::CalcTextSize("- X").x - 30);
        // Bottone Minimize
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, arancione); // hover arancione
        ImGui::PushStyleColor(ImGuiCol_Text, bianco); // testo bianco
        if (ImGui::Button("-")) {
            glfwHideWindow(window_ptr); 
        }
        ImGui::PopStyleColor(2);
        ImGui::SameLine();

        // Bottone Exit
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, rosso); // hover rosso
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1,1,1,1)); // testo bianco
        if (ImGui::Button("X")) {
            exit(0);
        }
        checkWindowSizeChange(size);
        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar();
        ImGui::End();
    } // fine MinimizeAndExitWindow::Render()
    ////////////////////////////////////////////////////Show Demo Window///////////////////////////////////////////////////////
    showDemoWindow::showDemoWindow(ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f) 
    : Window("Demo Window", p, s, win, f){ // costruttore con lista di inizializzazione

    };
    void showDemoWindow::Render() {
        ImGui::ShowDemoWindow(&bool_demo_window);
    };

    //////////////////////////////////////////////////Esperimenti Window ////////////////////////////////////////////////////
    EsperimentiWindow::EsperimentiWindow(ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f)
    : Window("Esperimenti", p, s, win, f) {

    }
    void EsperimentiWindow::Render() {
        ImGui::Begin("Esperimenti", &bool_esperimenti_window, flags_esperimenti_window);

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

    //////////////////////////////////////Window 1 /////////////////////////////////////////////////////////////////
    Window1::Window1(ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f)
    : Window("Window1", p, s, win, f) {

    }

    void Window1::Render() {
    ImGui::Begin("Window1", &bool_window1, flags_window1);

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
    };

    //////////////////////////////////////////////// MENU BAR ///////////////////////////////////////////////////////////////
    MenuBar::MenuBar(ImVec2 p, ImVec2 s, GLFWwindow* win, ImGuiWindowFlags f)
    : Window("MenuBar", p, s, win, f) {

    }
    void MenuBar::Render() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if(ImGui::MenuItem("New")) {

                }
                if(ImGui::MenuItem("Open")) {
                    
                }
                if(ImGui::MenuItem("Save")) {
                    
                }
                ImGui::EndMenu();
            }
            
            if (ImGui::BeginMenu("Settings")) {
                if (ImGui::MenuItem("Attiva funzione", NULL, &checked)) {
                    // checked viene aggiornato automaticamente
                }
                if (ImGui::BeginMenu("Sotto-menu")) {
                    if (ImGui::MenuItem("Voce 1")) {}
                    if (ImGui::MenuItem("Voce 2")) {}
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            ImGui::SameLine();
            if (ImGui::BeginMenu("Help")) {
                if (ImGui::MenuItem("What the fuck!", NULL, &checked)) {

                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    };

    TabWindow::TabWindow(const std::string& title, ImVec2 pos, ImVec2 size, GLFWwindow* win, ImGuiWindowFlags f)
    : Window(title, pos, size, win, f) {}

    void TabWindow::Render(){
        if (ImGui::Begin(title.c_str(), nullptr, flags)) {
            if (ImGui::BeginTabBar("MyTabBar", ImGuiTabBarFlags_Reorderable)) {
                // Tab fisso (non chiudibile)
                if (ImGui::BeginTabItem("Generale")) {
                    ImGui::Text("Contenuto tab generale");
                    if (ImGui::Button("Azione 1")) {
                        // Azione del bottone
                    }
                    ImGui::EndTabItem();
                }

                // Tab chiudibili
                if (tab1_open && ImGui::BeginTabItem("Tab 1", &tab1_open)) {
                    ImGui::Text("Contenuto tab 1");
                    ImGui::EndTabItem();
                }

                if (tab2_open && ImGui::BeginTabItem("Tab 2", &tab2_open, ImGuiTabItemFlags_UnsavedDocument)) {
                    ImGui::Text("Contenuto tab 2 (non salvato)");
                    ImGui::EndTabItem();
                }

                if (tab3_open && ImGui::BeginTabItem("Tab 3", &tab3_open)) {
                    ImGui::Text("Contenuto tab 3");
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
            ImGui::End();
        }
    }

    Tree::Tree(const std::string& title, ImVec2 pos, ImVec2 size, GLFWwindow* win, ImGuiWindowFlags f)
    : Window(title, pos, size, win, f) {}

    void Tree::Render() {
        if (ImGui::TreeNode("Nodo Principale")) {
            ImGui::Text("Contenuto del nodo");
            if (ImGui::TreeNode("Sotto-nodo 1")) {
                ImGui::Text("Contenuto del sotto-nodo 1");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Sotto-nodo 2")) {
                ImGui::Text("Contenuto del sotto-nodo 2");
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }

} // fine namespace gui