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
    if (this->_hidden)
        return;
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

void EGE::GUIManager::defaultMode()
{
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.TabRounding = 4.0f;
    style.ChildRounding = 4.0f;

    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 0.5f;
    style.PopupBorderSize = 1.0f;
    style.ChildBorderSize = 0.5f;
    style.ScrollbarSize = 15.0f;

    style.GrabMinSize = 10.0f;
    style.GrabRounding = 2.0f;
    style.FramePadding = ImVec2(5, 5);
    style.ItemSpacing = ImVec2(5, 5);
    style.ItemInnerSpacing = ImVec2(5, 5);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 0.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.DisplaySafeAreaPadding = ImVec2(4, 4);

    style.Colors[ImGuiCol_Text]                  = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

    style.Colors[ImGuiCol_WindowBg]              = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_PopupBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);

    style.Colors[ImGuiCol_Border]                = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);

    style.Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 1.00f, 1.00f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    style.Colors[ImGuiCol_TitleBg]               = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);

    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);

    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.0f, 0.0f, 0.0f, 0.1f);

    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);

    style.Colors[ImGuiCol_Button]                = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);

    style.Colors[ImGuiCol_Header]                = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

    style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);

    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
}

void EGE::GUIManager::darkMode()
{
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.TabRounding = 4.0f;
    style.ChildRounding = 4.0f;

    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 0.5f;
    style.PopupBorderSize = 1.0f;
    style.ChildBorderSize = 0.5f;
    style.ScrollbarSize = 15.0f;

    style.GrabMinSize = 10.0f;
    style.GrabRounding = 2.0f;
    style.FramePadding = ImVec2(5, 5);
    style.ItemSpacing = ImVec2(5, 5);
    style.ItemInnerSpacing = ImVec2(5, 5);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 0.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.DisplaySafeAreaPadding = ImVec2(4, 4);

    style.Colors[ImGuiCol_Text]                  = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);

    style.Colors[ImGuiCol_Border]                = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.10f);

    style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.00f, 0.00f, 0.00f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    style.Colors[ImGuiCol_TitleBg]               = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);

    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(1.0f, 1.0f, 1.0f, 0.1f);

    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);

    style.Colors[ImGuiCol_Button]                = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);

    style.Colors[ImGuiCol_Header]                = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

    style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.098f, 0.463f, 0.824f, 1.0f);

    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);
}

void EGE::GUIManager::show()
{
    this->_hidden = false;
}

void EGE::GUIManager::hide()
{
    this->_hidden = true;
}

void EGE::GUIManager::toggle()
{
    this->_hidden = !this->_hidden;
}

bool EGE::GUIManager::isVisible() const
{
    return !this->_hidden;
}