/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include "GUI/Interactable.hpp"

namespace EGE {
    class Color : public Interactable {
        public:
            Color(const std::string &title = "");
            ~Color();

            void draw() override;

            void setColor(float r, float g, float b, float a = 1);

            float getRed() const;
            float getGreen() const;
            float getBlue() const;
            float getAlpha() const;

        protected:
            float _r;
            float _g;
            float _b;
            float _a;
    };
}

#endif /* !COLOR_HPP_ */
