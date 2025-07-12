#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

// STYLING

    void style() {
        ImGuiStyle& style = ImGui::GetStyle();
        style.FrameRounding = 20.0f;
        style.Colors[ImGuiCol_Button] = ImVec4(193.0f/255,60.0f/255,60.0f/255,255.0f/255);
    };


int main() {
    // Inizializza GLFW
    if (!glfwInit()) {
        std::cerr << "Errore nell'inizializzazione di GLFW" << std::endl;
        return -1;
    }

    // Crea la finestra
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Il Mio Progetto ImGui", nullptr, nullptr);
    if (!window) {
        std::cerr << "Errore nella creazione della finestra" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // VSync

    // Inizializza Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Variabili del progetto
    bool show_demo_window = false;
    bool show_my_window = false;
    bool window1 = true;
    // Impostazioni Window 1 
    float value1 = 0.1f;
    int value2 = 1;
    const char* items[] = {"item1", "item2", "item3"};
    int current = 0;
    //
    bool esperimenti_window = false;
    float my_float = 0.0f;
    int my_int = 0;

    style(); 
    // Loop principale
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // La tua UI qui
        if (show_my_window) {
            ImGui::Begin("Il Mio Progetto", &show_my_window);
            
            ImGui::Text("Benvenuto nel mio progetto ImGui!");
            ImGui::Separator();
            
            ImGui::SliderFloat("Float Value", &my_float, 0.0f, 1.0f);
            ImGui::SliderInt("Int Value", &my_int, 0, 100);
            
            if (ImGui::Button("Click Me!")) {
                std::cout << "Bottone cliccato!" << std::endl;
            }
            
            ImGui::SameLine();
            ImGui::Text("Counter: %d", my_int);
            
            ImGui::End();
        }
//*  /////////////////////////////////////////////////// Window1 ////////////////////////////////////
        
        // ImVec2 window1_vec2; // creo un vettore per setNextWindowsSize per dirgli le misure ma basta semplicemente mettere 
        // // come argomento a SetNextWindowSize(ImVec2(x,y))
        // window1_vec2.x = 400;
        // window1_vec2.y = 600;

        // un altro modo per inizializzare un ImVec2 è
        // ImVec2 a = {200, 300};
        ImGui::SetNextWindowSize(ImVec2(600,400));
        if (window1) {
            ImGui::Begin("Window1", &window1);

            if (ImGui::Button("My button", ImVec2(100,100))) {
                // tutto quello in questo if verrà eseguito quando il bottone sarà premuto
            }
            bool checkBoxValue = true;
            ImGui::Checkbox("CheckBox", &checkBoxValue);

            ImGui::SliderFloat("My Float Slider", &value1, 0.0f, 100.0f);

            ImGui::Combo("##id1", &current, items, IM_ARRAYSIZE(items));
            ImGui::SetCursorPosX(ImGui::GetWindowWidth()/2 - ImGui::CalcTextSize("This is some text").x/2);
            ImGui::Text("This is some text");

            ImGui::End();
        }

        // Demo window (opzionale)
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        if (esperimenti_window) {
            ImGui::Begin("Esperimenti");

            // Input text
            static char text[128] = "";
            ImGui::InputText("Nome", text, IM_ARRAYSIZE(text));

            // Checkbox
            static bool checkbox = false;
            ImGui::Checkbox("Attiva funzione", &checkbox);

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
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}