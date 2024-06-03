/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** GUIManager
*/

#include "GUI/GUIManager.hpp"

EGE::GUIManager::~GUIManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void EGE::GUIManager::clear()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void EGE::GUIManager::display()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    //     ImGui::UpdatePlatformWindows();
    //     ImGui::RenderPlatformWindowsDefault();
    //     glfwMakeContextCurrent(this->_window->getWindow());
    // }
}

void EGE::GUIManager::draw()
{
    this->_menuBar->draw();
    for (auto &gui : this->_panels) {
        gui->draw();
    }
}

void EGE::GUIManager::init(Window *win)
{
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(win->getWindow(), true);
    this->_window = win;
    this->_menuBar->init(win);
    for (auto &gui : this->_panels) {
        gui->init(win);
    }
}
