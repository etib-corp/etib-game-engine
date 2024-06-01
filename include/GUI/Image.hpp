/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include "GUI/GUI.hpp"

namespace EGE {
    class Image : public GUI {
        public:
            Image();
            ~Image();

        protected:
            std::string _path;
            void *_texture;
    };
}

#endif /* !IMAGE_HPP_ */
