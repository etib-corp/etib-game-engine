/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** String
*/

#ifndef STRING_HPP_
#define STRING_HPP_

#include "GUI/Interactable.hpp"

namespace EGE {

    /**
     * @brief The String class represents an input field for text content.
     * 
     * It inherits from the Interactable class and provides methods to set and get the content of the input field.
     */
    class String : public Interactable {
        public:
            /**
             * @brief Constructs a String object with an optional title.
             * 
             * @param title The title of the input field.
             */
            String(const std::string &title = "");

            /**
             * @brief Destroys the String object.
             */
            ~String();

            /**
             * @brief Draws the input field on the screen.
             */
            void draw() override;

            /**
             * @brief Sets the content of the input field.
             * 
             * @param content The content to be set.
             */
            void setContent(const std::string &content);

            /**
             * @brief Gets the current content of the input field.
             * 
             * @return The current content of the input field.
             */
            std::string getContent() const;

        protected:
            std::string _content; /**< The content of the input field. */
    };
}

#endif /* !STRING_HPP_ */
