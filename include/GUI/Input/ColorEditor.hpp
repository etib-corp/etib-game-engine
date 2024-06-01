/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** ColorEditor
*/

#ifndef COLOREDITOR_HPP_
#define COLOREDITOR_HPP_

#include "GUI/Interactable.hpp"


namespace EGE {
    class ColorEditor : public Interactable {
        public:
            ColorEditor(const std::string &title = "");
            ~ColorEditor();

            void draw() override;

            void setColor(float red, float green, float blue, float alpha = 1.0);

            float getRed() const;
            float getGreen() const;
            float getBlue() const;
            float getAlpha() const;

            float *getColor() const;
        protected:
            float _red;
            float _green;
            float _blue;
            float _alpha;
    };
}

#endif /* !COLOR_HPP_ */
