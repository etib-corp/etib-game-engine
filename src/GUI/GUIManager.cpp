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
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EGE::GUIManager::draw()
{
    this->_menuBar->draw();
    for (auto &gui : this->_panels) {
        this->_panels[gui.first]->draw();
    }
}

void EGE::GUIManager::init(Window *win)
{
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(win->getWindow(), true);
    ImGui_ImplOpenGL3_Init();
    this->_window = win;
    this->_menuBar->init(win);
    for (auto &elm : this->_panels) {
        this->_panels[elm.first]->init(win);
    }
}
