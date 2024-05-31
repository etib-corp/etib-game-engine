/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** main
*/

#include "vrtests.hpp"

extern "C" void android_main(android_app *app) {
    LOGV("WindowVR Constructor hello\n");
    EGE::WindowVR a(app);
    a.create();
    while (a.isRunning()) {
        a.appUpdatePumpEvents();
        a.appUpdateBeginFrame();
        // tout draw
        a.appUpdateEndFrame();
    }
}
