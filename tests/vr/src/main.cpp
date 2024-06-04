/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** main
*/

#include "vrtests.hpp"


extern "C" void android_main(android_app *app) {
    EGE::WindowVR a(app);
    a.create();
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "FINISH CREATE");
    while (a.isRunning()) {
        a.appUpdatePumpEvents();
        if (!a.isSessionReady()) { continue; }
        a.appUpdateBeginFrame();
        if (a.isShouldRender())
            // a.draw();
        // tout draw
        a.appUpdateEndFrame();
    }
}
