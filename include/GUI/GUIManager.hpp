/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** GUIManager
*/

#ifndef GUIMANAGER_HPP_
#define GUIMANAGER_HPP_

#include "GUI/Panel.hpp"
#include "GUI/Menu/Main.hpp"

#include "GUI/Input/Button.hpp"
#include "GUI/Input/CheckBox.hpp"
#include "GUI/Input/ColorEditor.hpp"
#include "GUI/Input/Number.hpp"
#include "GUI/Input/Slider.hpp"
#include "GUI/Input/String.hpp"
#include "GUI/ListBox.hpp"
#include "GUI/RadioButtonList.hpp"

#include "GUI/Text.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <map>

namespace EGE {
    /**
     * @brief The GUIManager class handles the management and rendering of GUI elements.
     */
    class GUIManager {
        public:
            /**
             * @brief Destructor for the GUIManager class.
             */
            ~GUIManager();

            /**
             * @brief Initializes the GUIManager with the specified window.
             *
             * @param win The window to be associated with the GUIManager.
             */
            void init(Window *win);

            /**
             * @brief Clears all GUI elements from the GUIManager.
             */
            void clear();

            /**
             * @brief Draws all GUI elements on the screen.
             */
            void draw();

            /**
             * @brief Displays the rendered GUI elements on the screen.
             */
            void display();

            /**
             * @brief Sets the default mode for the GUIManager.
             */
            void defaultMode();

            /**
             * @brief Sets the dark mode for the GUIManager.
             */
            void darkMode();

            /**
             * @brief Shows the GUIManager.
             */
            void show();

            /**
             * @brief Hides the GUIManager.
             */
            void hide();

            /**
             * @brief Toggles the visibility of the GUIManager.
             */
            void toggle();

            /**
             * @brief Checks if the GUIManager is hidden.
             *
             * @return True if the GUIManager is visible, false otherwise.
             */
            bool isVisible() const;

            std::map<std::string, Panel *> _panels; /**< The vector of panels managed by the GUIManager. */
            Main *_menuBar; /**< The main menu bar managed by the GUIManager. */

            Window *_window; /**< The window associated with the GUIManager. */

        protected:
            bool _hidden; /**< The hidden state of the GUIManager. */
    };
}

#endif /* !GUIMANAGER_HPP_ */
