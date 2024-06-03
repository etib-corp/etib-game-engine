/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** WindowVR
*/

#pragma once

#define HAND_COUNT (2)
#define MAX_VIEWS (4)
#define MAX_SWAPCHAIN_LENGTH (3)

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "external/vr/include/android_native_app_glue.h"
#include <jni.h>
#include <android/log.h>
#include <android/native_activity.h>

#include "Error.hpp"
#include <string.h>

#define XR_USE_PLATFORM_ANDROID
#define XR_USE_GRAPHICS_API_OPENGL_ES
#include "openxr/openxr.h"
#include "openxr/openxr_platform.h"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "tag", __VA_ARGS__)

namespace EGE {
    class WindowVRError : public EGE::Error {
        public:
            WindowVRError(const std::string &message) : EGE::Error(message) {}
    };

    class WindowVR {
        public:
            WindowVR(android_app *app);
            ~WindowVR();

            void create();

            void setWindowInit(bool is_init);

            bool getIsWindowInit();

            void appUpdatePumpEvents();

            void appUpdateBeginFrame();

            void appUpdateEndFrame();

            bool isRunning();

            bool isSessionReady();

            // void setSessionReady(bool is_ready);

            bool isShouldRender();

            void draw();

        private:
            void _appSetCallbacksAndWait();
            void _appInitEgl();
            void _appInitXrCreateInstance();
            void _appInitXrGetSystem();
            void _appInitXrEnumViews();
            void _appInitXrCreateSession();
            void _appInitXrCreateStageSpace();
            void _appInitXrCreateActions();
            void _appInitXrCreateSwapchains();
            void _appInitOpengl();
            void _appUpdateBeginSession();
            void appUpdateSessionStateChange(XrSessionState state);
            // void _appInitOpenglShaders();

            // Native app glue
            android_app *_app;
            bool _isWindowInit;

            // EGL state required to initialise OpenXR
            EGLDisplay _eglDisplay;
            EGLConfig _eglConfig;
            EGLContext _eglContext;
            EGLSurface _eglSurface;

            // OpenXR driver state
            XrInstance _instance;
            XrSystemId _system;
            XrSession _session;

            // Views
            uint32_t _viewCount;
            XrViewConfigurationView _viewConfigs[MAX_VIEWS];

            // Spaces
            XrSpace _stageSpace;
            XrSpace _handSpaces[HAND_COUNT];

            // OpenXR paths (interned query strings)
            XrPath _touchControllerPath;
            XrPath _handPaths[HAND_COUNT];
            XrPath _squeezeValuePaths[HAND_COUNT];
            XrPath _triggerValuePaths[HAND_COUNT];
            XrPath _posePaths[HAND_COUNT];
            XrPath _hapticPaths[HAND_COUNT];
            XrPath _menuClickPaths[HAND_COUNT];

            // Action Set and Actions
            XrActionSet _actionSet;
            XrAction _grabAction;
            XrAction _triggerAction;
            XrAction _triggerClickAction;
            XrAction _poseAction;
            XrAction _vibrateAction;
            XrAction _menuAction;

            // Swapchains
            int32_t _swapchainWidths[MAX_VIEWS];
            int32_t _swapchainHeights[MAX_VIEWS];
            uint32_t _swapchainLengths[MAX_VIEWS];
            XrSwapchain _swapchains[MAX_VIEWS];
            XrSwapchainImageOpenGLESKHR _swapchainImages[MAX_VIEWS][MAX_SWAPCHAIN_LENGTH];

            // OpenGL state
            uint32_t _boxProgram;
            uint32_t _backgroundProgram;
            uint32_t _framebuffer;
            uint32_t _depthTargets[MAX_VIEWS];

            // Current Controller Inputs
            XrSpaceLocation _handLocations[HAND_COUNT];
            XrActionStateFloat _triggerStates[HAND_COUNT];
            XrActionStateBoolean _triggerClickStates[HAND_COUNT];

            // Session State
            XrSessionState _sessionState;
            XrFrameState _frameState;
            bool _shouldRender;
            bool _isRunning;
            bool _isSessionReady;
            bool _isSessionBeginEver;

            // Frame Submission
            uint32_t _viewSubmitCount;
            XrCompositionLayerProjection _projectionLayer;
            XrCompositionLayerProjectionView _projectionLayerViews[MAX_VIEWS];
    };
}
