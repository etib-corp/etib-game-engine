/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** main
*/

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "vrtests.hpp"
#define IMGUI_IMPL_OPENGL_ES3
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_opengl3.h"
#include "Model.hpp"
#include "Shader.hpp"

MemoryIOSystem *gMemoryIOSystem;

extern "C" void android_main(android_app *app) {

    EGE::WindowVR a(app);
    AAssetManager *mgr = app->activity->assetManager;
    AAsset *file = AAssetManager_open(mgr, "shader/vertex.vert", AASSET_MODE_UNKNOWN);
    off_t fileLength = AAsset_getLength(file);
    char *vertexSource = (char *)malloc(fileLength + 1);
    AAsset_read(file, vertexSource, fileLength);
    vertexSource[fileLength] = '\0';

    file = AAssetManager_open(mgr, "shader/fragment.frag", AASSET_MODE_UNKNOWN);
    fileLength = AAsset_getLength(file);
    char *fragmentSource = (char *)malloc(fileLength + 1);
    AAsset_read(file, fragmentSource, fileLength);
    fragmentSource[fileLength] = '\0';

    a.create();

    EGE::Shader s;
    s.compile(vertexSource, fragmentSource);
    gMemoryIOSystem = new MemoryIOSystem();
    gMemoryIOSystem->setAssetManager(mgr);

    gMemoryIOSystem->addFile("models/cube/Grass_Block.obj");
    gMemoryIOSystem->addFile("models/cube/Grass_Block.mtl");

    EGE::Model m("models/cube/Grass_Block.obj");
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Model loaded\n");
    m.setPosition(EGE::Maths::Vector3<float>(0, 1, 0));
    m.setScale(EGE::Maths::Vector3<float>(0.5, 0.5, 0.5));
    // ImGuiContext &ctx = *ImGui::CreateContext();
    // ImGuiIO &io = ImGui::GetIO();
    // ImGui_ImplOpenGL3_Init();


    // GLuint gui_framebuffer;
    // glGenFramebuffers(1, &gui_framebuffer);
    // glBindFramebuffer(GL_FRAMEBUFFER, gui_framebuffer);

    // GLuint gui_texture;
    // glGenTextures(1, &gui_texture);
    // glBindTexture(GL_TEXTURE_2D, gui_texture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1000, 1000, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gui_texture, 0);

    // GLenum draw_buffers[1] = {GL_COLOR_ATTACHMENT0};
    // glDrawBuffers(1, draw_buffers);

    // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    // }

    // GLint m_viewport[4];

    // glGetIntegerv( GL_VIEWPORT, m_viewport );
    while (a.isRunning()) {
        // ImGui_ImplOpenGL3_NewFrame();
        // ctx.IO.DisplaySize = ImVec2(200, 200);
        // ImGui::NewFrame();
        // ImGui::SetNextWindowSize(ImVec2(200, 100));
        // ImGui::SetNextWindowPos(ImVec2(0, 50));
        // ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        // ImGui::Text("Hello, world!");
        // ImGui::End();

        a.appUpdatePumpEvents();
        if (!a.isSessionReady()) { continue; }
        a.appUpdateBeginFrame();
        if (a.isShouldRender()) {
            a.display(m, s);
            // ImGuiIO& io = ImGui::GetIO();
            // ImGui::Render();
            // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            //     ImGui::UpdatePlatformWindows();
            //     ImGui::RenderPlatformWindowsDefault();
            // }
        }
        a.appUpdateEndFrame();
    }
}
