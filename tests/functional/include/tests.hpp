/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** tests
*/

#pragma once

#include "Camera.hpp"
#include "Color.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "Texture.hpp"
#include "Model.hpp"
#include "GUI/GUIManager.hpp"

#include <iostream>
#include <memory>

class TestGUI : public EGE::GUIManager {
    public:
        TestGUI() {
            this->_menuBar = new EGE::Main();
            this->_panels.push_back(new EGE::Panel("Test"));
        }
        ~TestGUI() {}
};
