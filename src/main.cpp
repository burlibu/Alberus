#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

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

    // Variabili del tuo progetto
    bool show_demo_window = true;
    bool show_my_window = true;
    float my_float = 0.0f;
    int my_int = 0;

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

        // Demo window (opzionale)
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

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