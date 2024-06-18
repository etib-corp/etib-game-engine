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
#include "ModelVR.hpp"
#include "Shader.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Matrix.hpp"
#include <memory>
#include <map>

#include "Error.hpp"
#include <string.h>
#include <vector>
#include <tuple>


#define XR_USE_PLATFORM_ANDROID
#define XR_USE_GRAPHICS_API_OPENGL_ES
#include "openxr/openxr.h"
#include "openxr/openxr_platform.h"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "tag", __VA_ARGS__)

namespace EGE {
    /**
     * @brief The WindowVRError class represents an error that can occur during WindowVR operations.
    */
    class WindowVRError : public EGE::Error {
        public:
            /**
             * @brief Constructs a WindowVRError object with the given error message.
            */
            WindowVRError(const std::string &message) : EGE::Error(message) {}
    };

    /**
     * @brief The WindowVR class represents a window for virtual reality rendering.
     *
     * This class provides functionality for creating and managing a window for virtual reality rendering.
     * It handles the initialization of the window, rendering of models, and interaction with the virtual reality system.
     */
    class WindowVR {
        public:
            /**
             * @brief Constructs a WindowVR object with the specified android app.
             *
             * @param app The android app.
            */
            WindowVR(android_app *app);

            /**
             * @brief Destroys the WindowVR object.
            */
            ~WindowVR();

            /**
             * @brief Initializes the window.
            */
            void create();

            /**
             * @brief Sets the window initialization flag.
             *
             * @param is_init The window initialization flag.
            */
            void setWindowInit(bool is_init);

            /**
             * @brief Gets the window initialization flag.
             *
             * @return bool The window initialization flag.
            */
            bool getIsWindowInit();

            /**
             * @brief Processes the android app events.
            */
            void appUpdatePumpEvents();

            /**
             * @brief Begins the frame rendering.
            */
            void appUpdateBeginFrame();

            /**
             * @brief Ends the frame rendering.
            */
            void appUpdateEndFrame();

            /**
             * @brief Indicates whether the window is running.
             *
             * @return bool True if the window is running, false otherwise.
            */
            bool isRunning();

            /**
             * @brief Indicates whether the session is ready.
             *
             * @return bool True if the session is ready, false otherwise.
             */
            bool isSessionReady();

            // void setSessionReady(bool is_ready);

            /**
             * @brief Indicates whether the window should render.
             *
             * @return bool True if the window should render, false otherwise.
             */
            bool isShouldRender();

            /**
             * @brief Adds a model to render on the window.
             *
             * @param key The key of the model.
             * @param model The shared pointer to the model object.
             */
            void addModel(const std::string &key, const std::shared_ptr<ModelVR> &model);

            /**
             * @brief Removes a model from the window.
             *
             * @param key The key of the model.
             * @param model The shared pointer to the model object.
             */
            void removeModel(const std::string &key, const std::shared_ptr<ModelVR> &model);

            /**
             * @brief Adds a shader to the window.
             *
             * @param key The key of the shader.
             * @param shader The shared pointer to the shader object.
             */
            void addNewSlot(const std::string &key, const std::shared_ptr<Shader> &shader);

            /**
             * @brief Displays the window.
             *
             * This method will display the window and render the models.
            */
            void display();

        private:
            std::map<std::string, std::pair<std::shared_ptr<Shader>, std::vector<std::shared_ptr<ModelVR>>>> _drawable; ///< Map of shaders and models to render

            /**
             * @brief Sets the callbacks and waits for the app to be ready.
            */
            void _appSetCallbacksAndWait();

            /**
             * @brief Initializes the EGL.
            */
            void _appInitEgl();

            /**
             * @brief Creates the OpenXR instance.
            */
            void _appInitXrCreateInstance();

            /**
             * @brief Gets the OpenXR system.
            */
            void _appInitXrGetSystem();

            /**
             * @brief Enumerates the OpenXR views.
            */
            void _appInitXrEnumViews();

            /**
             * @brief Creates the OpenXR session.
            */
            void _appInitXrCreateSession();

            /**
             * @brief Creates the OpenXR spaces.
            */
            void _appInitXrCreateStageSpace();

            /**
             * @brief Creates the OpenXR actions.
            */
            void _appInitXrCreateActions();

            /**
             * @brief Creates the OpenXR swapchains.
            */
            void _appInitXrCreateSwapchains();

            /**
             * @brief Initializes the OpenGL.
            */
            void _appInitOpengl();

            /**
             * @brief Initializes the OpenGL shaders.
            */
            void _appUpdateBeginSession();

            /**
             * @brief Updates the session state change.
            */
            void appUpdateSessionStateChange(XrSessionState state);
            // void _appInitOpenglShaders();

            XrVector3f _position;   ///< The position of the window

            // Native app glue
            android_app *_app;      ///< The android app instance
            bool _isWindowInit;     ///< The window initialization flag

            // EGL state required to initialise OpenXR
            EGLDisplay _eglDisplay;     ///< The EGL display
            EGLConfig _eglConfig;       ///< The EGL config
            EGLContext _eglContext;     ///< The EGL context
            EGLSurface _eglSurface;     ///< The EGL surface

            // OpenXR driver state
            XrInstance _instance;       ///< The OpenXR instance
            XrSystemId _system;         ///< The OpenXR system
            XrSession _session;         ///< The OpenXR session

            // Views
            uint32_t _viewCount;        ///< The view count
            XrViewConfigurationView _viewConfigs[MAX_VIEWS];    ///< The view configurations

            // Spaces
            XrSpace _stageSpace;        ///< The stage space
            XrSpace _handSpaces[HAND_COUNT];        ///< The hand spaces

            // OpenXR paths (interned query strings)
            XrPath _touchControllerPath;        ///< The touch controller path
            XrPath _handPaths[HAND_COUNT];      ///< The hand paths
            XrPath _squeezeValuePaths[HAND_COUNT];      ///< The squeeze value paths
            XrPath _triggerValuePaths[HAND_COUNT];      ///< The trigger value paths
            XrPath _posePaths[HAND_COUNT];              ///< The pose paths
            XrPath _hapticPaths[HAND_COUNT];            ///< The haptic paths
            XrPath _menuClickPaths[HAND_COUNT];         ///< The menu click paths
            XrPath _thumbstickPaths[HAND_COUNT];        ///< The thumbstick paths

            // Action Set and Actions
            XrActionSet _actionSet;                     ///< The action set
            XrAction _grabAction;                       ///< The grab action
            XrAction _triggerAction;                    ///< The trigger action
            XrAction _triggerClickAction;               ///< The trigger click action
            XrAction _poseAction;                       ///< The pose action
            XrAction _vibrateAction;                    ///< The vibrate action
            XrAction _menuAction;                       ///< The menu action
            XrAction _thumbstickAction;                 ///< The thumbstick action

            // Swapchains
            int32_t _swapchainWidths[MAX_VIEWS];        ///< The swapchain widths
            int32_t _swapchainHeights[MAX_VIEWS];       ///< The swapchain heights
            uint32_t _swapchainLengths[MAX_VIEWS];      ///< The swapchain lengths
            XrSwapchain _swapchains[MAX_VIEWS];         ///< The swapchains
            XrSwapchainImageOpenGLESKHR _swapchainImages[MAX_VIEWS][MAX_SWAPCHAIN_LENGTH];      ///< The swapchain images

            // OpenGL state
            uint32_t _boxProgram;               ///< The box program
            uint32_t _backgroundProgram;        ///< The background program
            uint32_t _screenProgram;            ///< The screen program
            uint32_t _framebuffer;              ///< The framebuffer
            uint32_t _screenFramebuffer;        ///< The screen framebuffer
            uint32_t _screenTexture;            ///< The screen texture
            uint32_t _depthTargets[MAX_VIEWS];  ///< The depth targets

            // Current Controller Inputs
            XrSpaceLocation _handLocations[HAND_COUNT];             ///< The hand locations
            XrActionStateFloat _triggerStates[HAND_COUNT];          ///< The trigger states
            XrActionStateBoolean _triggerClickStates[HAND_COUNT];   ///< The trigger click states
            XrActionStateVector2f _thumbstickStates[HAND_COUNT];    ///< The thumbstick states

            // Session State
            XrSessionState _sessionState;           ///< The session state
            XrFrameState _frameState;               ///< The frame state
            bool _shouldRender;                     ///< The should render flag
            bool _isRunning;                        ///< The is running flag
            bool _isSessionReady;                   ///< The is session ready flag
            bool _isSessionBeginEver;               ///< The is session begin ever flag

            // Frame Submission
            uint32_t _viewSubmitCount;                                              ///< The view submit count
            XrCompositionLayerProjection _projectionLayer;                          ///< The projection layer
            XrCompositionLayerProjectionView _projectionLayerViews[MAX_VIEWS];      ///< The projection layer views

    };
}
