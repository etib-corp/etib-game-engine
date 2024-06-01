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
    class String : public Interactable {
        public:
            String(const std::string &title = "");
            ~String();

            void draw() override;

            void setContent(const std::string &content);
            std::string getContent() const;

        protected:
            std::string _content;
    };
}

#endif /* !STRING_HPP_ */
