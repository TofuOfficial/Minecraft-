#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Game.hpp"
#include "Util.hpp"
#include "Shader.hpp"

Game::Game()
    : m_Window(800, 800, "Minecraft++")
{
    ASSERT_INIT(m_Window.Init());

    glfwMakeContextCurrent(m_Window.GetWindow());

    ASSERT_INIT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

Game::~Game()
{
    glfwTerminate();
}

void Game::CreateGame()
{
}

void Game::Run()
{
    float positions[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, m_Window.GetWidth(), 0, m_Window.GetHeight(), 0, 0);
    glMatrixMode(GL_MODELVIEW);

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec4 triColor = ImVec4(0.8f, 0.3f, 0.5f, 1.0f);

    Shader shader("../assets/shaders/vertex.glsl", "../assets/shaders/fragment.glsl");

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    while(!glfwWindowShouldClose(m_Window.GetWindow())) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
            ImGui::ColorEdit3("triangle color", (float*)&triColor); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        ImGui::Render();

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.SetUniform("triColor", triColor.x, triColor.y, triColor.z, triColor.w);
        shader.Bind();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
        glBindVertexArray(0);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        m_Window.OnUpdate();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwDestroyWindow(m_Window.GetWindow());
    glfwTerminate();
}
