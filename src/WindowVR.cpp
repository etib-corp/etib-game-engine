/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** WindowVR
*/

#include "WindowVR.hpp"

EGE::WindowVR::WindowVR(android_app *app)
{
    LOGV("WindowVR Constructor hello\n");
    this->_app = app;
    this->_isRunning = true;
}

EGE::WindowVR::~WindowVR()
{
    XrResult result;

    printf("Shutting Down\n");

    // Clean up
    for (int i=0; i < this->_viewCount; i++) {
        result = xrDestroySwapchain(this->_swapchains[i]);
    }

    result = xrDestroySpace(this->_stageSpace);

    if (this->_isSessionBeginEver) {
        result = xrEndSession(this->_session);
    }

    result = xrDestroySession(this->_session);
    result = xrDestroyInstance(this->_instance);
}

extern "C" void app_android_handle_cmd(android_app *app, int32_t cmd) {
        EGE::WindowVR *a = static_cast<EGE::WindowVR *>(app->userData);

        switch (cmd) {
        case APP_CMD_DESTROY:
                // Handle application shutdown
                ANativeActivity_finish(app->activity);
                // TODO: call app_shutdown
                break;
        case APP_CMD_INIT_WINDOW:
                if (!a->getIsWindowInit()) {
                        a->setWindowInit(true);
                        printf( "Got start event\n" );
                }
                else {
                        // TODO: Handle Resume
                }
                break;
        case APP_CMD_TERM_WINDOW:
                // Turns up when focus is lost
                // Seems like the main loop just xrWaitFrame hitches
        	break;
        case APP_CMD_SAVE_STATE:
                printf("Saving application state\n");
                app->savedState = a;
                app->savedStateSize = sizeof(EGE::WindowVR);
                break;
        case APP_CMD_RESUME:
                // Nope, that doesn't work
                // printf("Resumed, loading state\n");
                // memcpy(a, app->savedState, sizeof(app_t));
                break;
        // TODO: APP_CMD_SAVE_STATE
        default:
                printf("event not handled: %d\n", cmd);
        }
}

void EGE::WindowVR::setWindowInit(bool value)
{
    this->_isWindowInit = value;
}

bool EGE::WindowVR::getIsWindowInit()
{
    return this->_isWindowInit;
}

void EGE::WindowVR::_appSetCallbacksAndWait()
{
    this->_app->userData = this;
    this->_app->onAppCmd = app_android_handle_cmd;
    int events;

    while (!this->getIsWindowInit()) {
            struct android_poll_source *source;
            if ( ALooper_pollAll( 0, 0, &events, (void **)&source ) >= 0 ) {
                    if (source != NULL) {
                            source->process(this->_app, source);
                    }
            }
    }
}

void EGE::WindowVR::_appInitEgl()
{
    this->_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (this->_eglDisplay == EGL_NO_DISPLAY) 
        throw EGE::WindowVRError("eglGetDisplay() returned error");
    EGLint egl_major, egl_minor;
    int egl_init_success = eglInitialize(this->_eglDisplay, &egl_major, &egl_minor);
    if (!egl_init_success) 
        throw EGE::WindowVRError("eglInitialize() returned error");
    printf("EGL Version: \"%s\"\n", eglQueryString(this->_eglDisplay, EGL_VERSION));
    printf("EGL Vendor: \"%s\"\n", eglQueryString(this->_eglDisplay, EGL_VENDOR));
    printf("EGL Extensions: \"%s\"\n", eglQueryString(this->_eglDisplay, EGL_EXTENSIONS));
    EGLint num_config;
    EGLint const config_attribute_list[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_BUFFER_SIZE, 32,
            EGL_STENCIL_SIZE, 0,
            EGL_DEPTH_SIZE, 16, // Maybe 32?
            //EGL_SAMPLES, 1,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_NONE
    };
    eglChooseConfig(this->_eglDisplay, config_attribute_list, &this->_eglConfig, 1, &num_config);
    printf("Config: %d\n", num_config);

    // Context
    printf("Creating Context\n");
    static const EGLint context_attribute_list[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };
    this->_eglContext = eglCreateContext(this->_eglDisplay, this->_eglConfig, EGL_NO_CONTEXT, context_attribute_list);
    if (this->_eglContext == EGL_NO_CONTEXT)
        throw EGE::WindowVRError("eglCreateContext() returned error");
    printf("Context Created %p\n", this->_eglContext);

    // Surface
    if (!this->_app->window)
        throw EGE::WindowVRError("No window");
    int win_width = ANativeWindow_getWidth(this->_app->window);
    int win_height = ANativeWindow_getHeight(this->_app->window);
    printf("Width/Height: %dx%d\n", win_width, win_height);
    EGLint window_attribute_list[] = { EGL_NONE };
    this->_eglSurface = eglCreateWindowSurface(this->_eglDisplay, this->_eglConfig, this->_app->window, window_attribute_list);
    printf("Got Surface: %p\n", this->_eglSurface);
    if (this->_eglSurface == EGL_NO_SURFACE)
        throw EGE::WindowVRError("eglCreateWindowSurface() returned error");

    // Make Current
    int egl_make_current_success = eglMakeCurrent(this->_eglDisplay, this->_eglSurface, this->_eglSurface, this->_eglContext);
    if (!egl_make_current_success)
        throw EGE::WindowVRError("eglMakeCurrent() returned error");

    // Make some OpenGL calls
    printf("GL Vendor: \"%s\"\n", glGetString(GL_VENDOR));
    printf("GL Renderer: \"%s\"\n", glGetString(GL_RENDERER));
    printf("GL Version: \"%s\"\n", glGetString(GL_VERSION));
    printf("GL Extensions: \"%s\"\n", glGetString(GL_EXTENSIONS));
}

void EGE::WindowVR::_appInitXrCreateInstance()
{
    XrResult result;

    // Loader
    PFN_xrInitializeLoaderKHR loader_func;
	result = xrGetInstanceProcAddr(XR_NULL_HANDLE, "xrInitializeLoaderKHR", (PFN_xrVoidFunction*)&loader_func);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrGetInstanceProcAddr failed");
    }
    XrLoaderInitInfoAndroidKHR init_data = { XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR };
    init_data.applicationVM = this->_app->activity->vm;
    init_data.applicationContext = this->_app->activity->clazz;
    result = loader_func((XrLoaderInitInfoBaseHeaderKHR*)&init_data);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrInitializeLoaderKHR failed");
    }
    XrExtensionProperties extension_properties[128];
	uint32_t extension_count = 0;
	result = xrEnumerateInstanceExtensionProperties(NULL, 0, &extension_count, NULL);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrEnumerateInstanceExtensionProperties failed");
    }
    bool is_gles_supported = false;
	for (int i = 0; i < extension_count; i++ ) {
		if (!std::strcmp("XR_KHR_opengl_es_enable", extension_properties[i].extensionName)) {
			is_gles_supported = true;
		}
	}
    if (!is_gles_supported) {
        throw EGE::WindowVRError("XR_KHR_opengl_es_enable not supported");
    }
    const char *enabledExtensions[] = { "XR_KHR_opengl_es_enable" };
    XrInstanceCreateInfo instance_desc = { XR_TYPE_INSTANCE_CREATE_INFO };
    instance_desc.next = NULL;
	instance_desc.createFlags = 0;
	instance_desc.enabledExtensionCount = 1;
	instance_desc.enabledExtensionNames = enabledExtensions;
	instance_desc.enabledApiLayerCount = 0;
	instance_desc.enabledApiLayerNames = NULL;
	std::strcpy(instance_desc.applicationInfo.applicationName, "questxrexample");
	instance_desc.applicationInfo.engineName[0] = '\0';
	instance_desc.applicationInfo.applicationVersion = 1;
	instance_desc.applicationInfo.engineVersion = 0;
	instance_desc.applicationInfo.apiVersion = XR_CURRENT_API_VERSION;
	result = xrCreateInstance(&instance_desc, &this->_instance);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateInstance failed");
    }
    XrInstanceProperties instance_props = { XR_TYPE_INSTANCE_PROPERTIES };
    instance_props.next = NULL;
    result = xrGetInstanceProperties(this->_instance, &instance_props);
    if (instance_props.runtimeName[0] == '\0') {
        throw EGE::WindowVRError("No runtime found");
    }
    printf("Runtime Name: %s\n", instance_props.runtimeName);
    printf("Runtime Name: %s\n", instance_props.runtimeName);
    printf("Runtime Version: %d.%d.%d\n",
            XR_VERSION_MAJOR(instance_props.runtimeVersion),
            XR_VERSION_MINOR(instance_props.runtimeVersion),
            XR_VERSION_PATCH(instance_props.runtimeVersion));

    // Enumerate API Layers
    XrApiLayerProperties layer_props[64];
    uint32_t layer_count;
    result = xrEnumerateApiLayerProperties(0, &layer_count, NULL);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("No layers found");
    }
    for (int i=0; i < layer_count; i++) {
            layer_props[i].type = XR_TYPE_API_LAYER_PROPERTIES;
            layer_props[i].next = NULL;
    }
    result = xrEnumerateApiLayerProperties(layer_count, &layer_count, layer_props);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrEnumerateApiLayerProperties failed");
    }
}

void EGE::WindowVR::_appInitXrGetSystem()
{
    XrSystemGetInfo system_desc = { XR_TYPE_SYSTEM_GET_INFO };
	system_desc.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
	system_desc.next = NULL;

	XrResult result = xrGetSystem(this->_instance, &system_desc, &this->_system);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrGetSystem failed");
    }

    XrSystemProperties system_props = { XR_TYPE_SYSTEM_PROPERTIES };
    result = xrGetSystemProperties(this->_instance, this->_system, &system_props);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrGetSystemProperties failed");
    }

    printf("System properties for system \"%s\":\n", system_props.systemName);
    printf("	maxLayerCount: %d\n", system_props.graphicsProperties.maxLayerCount);
    printf("	maxSwapChainImageHeight: %d\n", system_props.graphicsProperties.maxSwapchainImageHeight);
    printf("	maxSwapChainImageWidth: %d\n", system_props.graphicsProperties.maxSwapchainImageWidth);
    printf("	Orientation Tracking: %s\n", system_props.trackingProperties.orientationTracking ? "true" : "false");
    printf("	Position Tracking: %s\n", system_props.trackingProperties.positionTracking ? "true" : "false");
}

void EGE::WindowVR::_appInitXrEnumViews()
{
    XrResult result;

    // Enumerate View Configs
    result = xrEnumerateViewConfigurationViews(this->_instance, this->_system, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0, &this->_viewCount, NULL);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrEnumerateViewConfigurationViews failed");
    }
    if (this->_viewCount <= MAX_VIEWS)
        throw EGE::WindowVRError("Too many views");
    for (int i=0; i < this->_viewCount; i++) {
            this->_viewConfigs[i].type = XR_TYPE_VIEW_CONFIGURATION_VIEW;
            this->_viewConfigs[i].next = NULL;
    }
    result = xrEnumerateViewConfigurationViews(this->_instance, this->_system, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, this->_viewCount, &this->_viewCount, this->_viewConfigs);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrEnumerateViewConfigurationViews failed");
    }
    printf("%d view_configs:\n", this->_viewCount);
    for (int i = 0; i < this->_viewCount; i++) {
            printf("	view_configs[%d]:\n", i);
            printf("		recommendedImageRectWidth: %d\n", this->_viewConfigs[i].recommendedImageRectWidth);
            printf("		maxImageRectWidth: %d\n", this->_viewConfigs[i].maxImageRectWidth);
            printf("		recommendedImageRectHeight: %d\n", this->_viewConfigs[i].recommendedImageRectHeight);
            printf("		maxImageRectHeight: %d\n", this->_viewConfigs[i].maxImageRectHeight);
            printf("		recommendedSwapchainSampleCount: %d\n", this->_viewConfigs[i].recommendedSwapchainSampleCount);
            printf("		maxSwapchainSampleCount: %d\n", this->_viewConfigs[i].maxSwapchainSampleCount);
    }
}

void EGE::WindowVR::_appInitXrCreateSession()
{
    XrResult result;

        // Create the session
	PFN_xrGetOpenGLESGraphicsRequirementsKHR gles_reqs_func;
	xrGetInstanceProcAddr(this->_instance, "xrGetOpenGLESGraphicsRequirementsKHR", (PFN_xrVoidFunction*)(&gles_reqs_func));
	XrGraphicsRequirementsOpenGLESKHR xr_gles_reqs = { XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR };
	result = gles_reqs_func(this->_instance, this->_system, &xr_gles_reqs);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrGetOpenGLESGraphicsRequirementsKHR failed");
    }
	const XrVersion egl_version = XR_MAKE_VERSION(3, 2, 0);

	XrGraphicsBindingOpenGLESAndroidKHR gl_binding = { XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR };
	gl_binding.display = this->_eglDisplay;
	gl_binding.config = this->_eglConfig;
	gl_binding.context = this->_eglContext;
	XrSessionCreateInfo session_desc = { XR_TYPE_SESSION_CREATE_INFO };
	session_desc.next = &gl_binding;
	session_desc.systemId = this->_system;
	result = xrCreateSession(this->_instance, &session_desc, &this->_session);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateSession failed");
    }
}

void EGE::WindowVR::_appInitXrCreateStageSpace()
{
    XrResult result;

        // Create the session
	PFN_xrGetOpenGLESGraphicsRequirementsKHR gles_reqs_func;
	xrGetInstanceProcAddr(this->_instance, "xrGetOpenGLESGraphicsRequirementsKHR", (PFN_xrVoidFunction*)(&gles_reqs_func));
	XrGraphicsRequirementsOpenGLESKHR xr_gles_reqs = { XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR };
	result = gles_reqs_func(this->_instance, this->_system, &xr_gles_reqs);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrGetOpenGLESGraphicsRequirementsKHR failed");
    }
	const XrVersion egl_version = XR_MAKE_VERSION(3, 2, 0);

	XrGraphicsBindingOpenGLESAndroidKHR gl_binding = { XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR };
	gl_binding.display = this->_eglDisplay;
	gl_binding.config = this->_eglConfig;
	gl_binding.context = this->_eglContext;
	XrSessionCreateInfo session_desc = { XR_TYPE_SESSION_CREATE_INFO };
	session_desc.next = &gl_binding;
	session_desc.systemId = this->_system;
	result = xrCreateSession(this->_instance, &session_desc, &this->_session);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateSession failed");
    }
}

void EGE::WindowVR::_appInitXrCreateActions()
{
    XrResult result;

    // Create Action Set
	XrActionSetCreateInfo action_set_desc;
	action_set_desc.type = XR_TYPE_ACTION_SET_CREATE_INFO;
	action_set_desc.next = NULL;
	strcpy(action_set_desc.actionSetName, "gameplay");
	strcpy(action_set_desc.localizedActionSetName, "Gameplay");
	action_set_desc.priority = 0;
	result = xrCreateActionSet(this->_instance, &action_set_desc, &this->_actionSet);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateActionSet() failed");
    }

        // Create sub-action paths
	xrStringToPath(this->_instance, "/user/hand/left", &this->_handPaths[0]);
	xrStringToPath(this->_instance, "/user/hand/right", &this->_handPaths[1]);
	xrStringToPath(this->_instance, "/user/hand/left/input/squeeze/value",  &this->_squeezeValuePaths[0]);
	xrStringToPath(this->_instance, "/user/hand/right/input/squeeze/value", &this->_squeezeValuePaths[1]);
	xrStringToPath(this->_instance, "/user/hand/left/input/trigger/value",  &this->_triggerValuePaths[0]);
	xrStringToPath(this->_instance, "/user/hand/right/input/trigger/value", &this->_triggerValuePaths[1]);
	xrStringToPath(this->_instance, "/user/hand/left/input/grip/pose", &this->_posePaths[0]);
	xrStringToPath(this->_instance, "/user/hand/right/input/grip/pose", &this->_posePaths[1]);
	xrStringToPath(this->_instance, "/user/hand/left/output/haptic", &this->_hapticPaths[0]);
	xrStringToPath(this->_instance, "/user/hand/right/output/haptic", &this->_hapticPaths[1]);
	xrStringToPath(this->_instance, "/user/hand/left/input/menu/click", &this->_menuClickPaths[0]);
	xrStringToPath(this->_instance, "/user/hand/right/input/menu/click", &this->_menuClickPaths[1]);

    // Create Actions
    XrActionCreateInfo grab_desc;
	grab_desc.type = XR_TYPE_ACTION_CREATE_INFO;
	grab_desc.next = NULL;
	grab_desc.actionType = XR_ACTION_TYPE_FLOAT_INPUT;
	strcpy(grab_desc.actionName, "grab_object" );
	strcpy(grab_desc.localizedActionName, "Grab Object");
	grab_desc.countSubactionPaths = 2;
	grab_desc.subactionPaths = this->_handPaths;
	result = xrCreateAction(this->_actionSet, &grab_desc, &this->_grabAction);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateAction() failed");
    }

    XrActionCreateInfo trigger_desc;
	trigger_desc.type = XR_TYPE_ACTION_CREATE_INFO;
	trigger_desc.next = NULL;
	trigger_desc.actionType = XR_ACTION_TYPE_FLOAT_INPUT;
	strcpy(trigger_desc.actionName, "trigger" );
	strcpy(trigger_desc.localizedActionName, "Trigger");
	trigger_desc.countSubactionPaths = 2;
	trigger_desc.subactionPaths = this->_handPaths;
	result = xrCreateAction(this->_actionSet, &trigger_desc, &this->_triggerAction);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateAction() failed");
    }

    XrActionCreateInfo click_desc;
	click_desc.type = XR_TYPE_ACTION_CREATE_INFO;
	click_desc.next = NULL;
	click_desc.actionType = XR_ACTION_TYPE_BOOLEAN_INPUT;
	strcpy(click_desc.actionName, "trigger_click" );
	strcpy(click_desc.localizedActionName, "Trigger Click");
	click_desc.countSubactionPaths = 2;
	click_desc.subactionPaths = this->_handPaths;
	result = xrCreateAction(this->_actionSet, &click_desc, &this->_triggerClickAction);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateAction() failed");
    }

    XrActionCreateInfo pose_desc;
	pose_desc.type = XR_TYPE_ACTION_CREATE_INFO;
	pose_desc.next = NULL;
	pose_desc.actionType = XR_ACTION_TYPE_POSE_INPUT;
	strcpy(pose_desc.actionName, "hand_pose" );
	strcpy(pose_desc.localizedActionName, "Hand Pose");
	pose_desc.countSubactionPaths = 2;
	pose_desc.subactionPaths = this->_handPaths;
	result = xrCreateAction(this->_actionSet, &pose_desc, &this->_poseAction);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateAction() failed");
    }

    XrActionCreateInfo vibrate_desc;
	vibrate_desc.type = XR_TYPE_ACTION_CREATE_INFO;
	vibrate_desc.next = NULL;
	vibrate_desc.actionType = XR_ACTION_TYPE_VIBRATION_OUTPUT;
	strcpy(vibrate_desc.actionName, "vibrate_hand" );
	strcpy(vibrate_desc.localizedActionName, "Vibrate Hand");
	vibrate_desc.countSubactionPaths = 2;
	vibrate_desc.subactionPaths = this->_handPaths;
	result = xrCreateAction(this->_actionSet, &vibrate_desc, &this->_vibrateAction);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateAction() failed");
    }

    XrActionCreateInfo menu_desc;
	menu_desc.type = XR_TYPE_ACTION_CREATE_INFO;
	menu_desc.next = NULL;
	menu_desc.actionType = XR_ACTION_TYPE_BOOLEAN_INPUT;
	strcpy(menu_desc.actionName, "quit_session" );
	strcpy(menu_desc.localizedActionName, "Menu Button");
	menu_desc.countSubactionPaths = 2;
	menu_desc.subactionPaths = this->_handPaths;
	result = xrCreateAction(this->_actionSet, &menu_desc, &this->_menuAction);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateAction() failed");
    }

    // Oculus Touch Controller Interaction Profile
    xrStringToPath(this->_instance, "/interaction_profiles/oculus/touch_controller", &this->_touchControllerPath);
    XrActionSuggestedBinding bindings[] = {
            {this->_grabAction, this->_squeezeValuePaths[0]},
            {this->_grabAction, this->_squeezeValuePaths[1]},
            {this->_triggerAction, this->_triggerValuePaths[0]},
            {this->_triggerAction, this->_triggerValuePaths[1]},
            {this->_triggerClickAction, this->_triggerValuePaths[0]},
            {this->_triggerClickAction, this->_triggerValuePaths[1]},
            {this->_poseAction, this->_posePaths[0]},
            {this->_poseAction, this->_posePaths[1]},
            {this->_menuAction, this->_menuClickPaths[0]},
            {this->_vibrateAction, this->_hapticPaths[0]},
            {this->_vibrateAction, this->_hapticPaths[1]}
    };
    XrInteractionProfileSuggestedBinding suggested_bindings;
    suggested_bindings.type = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING;
    suggested_bindings.next = NULL;
    suggested_bindings.interactionProfile = this->_touchControllerPath;
    suggested_bindings.suggestedBindings = bindings;
    suggested_bindings.countSuggestedBindings = sizeof(bindings) / sizeof(bindings[0]);
    result = xrSuggestInteractionProfileBindings(this->_instance, &suggested_bindings);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrSuggestInteractionProfileBindings failed");
    }

    // Hand Spaces
	XrActionSpaceCreateInfo action_space_desc = { XR_TYPE_ACTION_SPACE_CREATE_INFO };
	action_space_desc.action = this->_poseAction;
	XrPosef identity = { {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f} };
	action_space_desc.poseInActionSpace = identity;
	action_space_desc.subactionPath = this->_handPaths[0];
	result = xrCreateActionSpace(this->_session, &action_space_desc, &this->_handSpaces[0]);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateActionSpace failed");
    }
	action_space_desc.subactionPath = this->_handPaths[1];
	result = xrCreateActionSpace(this->_session, &action_space_desc, &this->_handSpaces[1]);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateActionSpace failed");
    }

        // Attach Action Set
	XrSessionActionSetsAttachInfo session_actions_desc;
	session_actions_desc.type = XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO;
	session_actions_desc.next = NULL;
	session_actions_desc.countActionSets = 1;
	session_actions_desc.actionSets = &this->_actionSet;
	result = xrAttachSessionActionSets(this->_session, &session_actions_desc);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrAttachSessionActionSets failed");
    }
}

void EGE::WindowVR::_appInitXrCreateSwapchains()
{
  XrResult result;

    // Choose Swapchain Format
    uint32_t swapchain_format_count;
    result = xrEnumerateSwapchainFormats(this->_session, 0, &swapchain_format_count, NULL);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrEnumerateSwapchainFormats failed");
    }
    if (swapchain_format_count <= 128) {
        throw EGE::WindowVRError("No swapchain formats");
    }
    int64_t swapchain_formats[128];
    result = xrEnumerateSwapchainFormats(this->_session, swapchain_format_count, &swapchain_format_count, swapchain_formats);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrEnumerateSwapchainFormats() failed");
    }
    bool is_default = true;
    int64_t selected_format = 0;
    for (int i=0; i < swapchain_format_count; i++) {
            if (swapchain_formats[i] == GL_SRGB8_ALPHA8) {
                    is_default = false;
                    selected_format = swapchain_formats[i];
            }
            if (swapchain_formats[i] == GL_SRGB8 && is_default) {
                    is_default = false;
                    selected_format = swapchain_formats[i];
            }
    }

	for (int i = 0; i < this->_viewCount; i++) {
                // Create Swapchain
		XrSwapchainCreateInfo swapchain_desc = { XR_TYPE_SWAPCHAIN_CREATE_INFO };
		swapchain_desc.createFlags = 0;
		swapchain_desc.usageFlags = XR_SWAPCHAIN_USAGE_SAMPLED_BIT | XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;
		swapchain_desc.format = selected_format;
		swapchain_desc.sampleCount = 1;
		swapchain_desc.width = this->_viewConfigs[i].recommendedImageRectWidth;
		swapchain_desc.height = this->_viewConfigs[i].recommendedImageRectHeight;
		swapchain_desc.faceCount = 1;
		swapchain_desc.arraySize = 1;
		swapchain_desc.mipCount = 1;
		result = xrCreateSwapchain(this->_session, &swapchain_desc, &this->_swapchains[i]);
        if (XR_FAILED(result)) {
            throw EGE::WindowVRError("xrCreateSwapchain() failed");
        }
        this->_swapchainWidths[i] = swapchain_desc.width;
        this->_swapchainHeights[i] = swapchain_desc.height;

        // Enumerate Swapchain Images
        result = xrEnumerateSwapchainImages(this->_swapchains[i], 0, &this->_swapchainLengths[i], NULL);
        if (XR_FAILED(result)) {
            throw EGE::WindowVRError("xrEnumerateSwapchainImages() failed");
        }
		for (int j = 0; j < this->_swapchainLengths[i]; j++) {
			this->_swapchainImages[i][j].type = XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR;
			this->_swapchainImages[i][j].next = NULL;
		}
                XrSwapchainImageBaseHeader* image_header = (XrSwapchainImageBaseHeader*)(&this->_swapchainImages[i][0]);
		result = xrEnumerateSwapchainImages(this->_swapchains[i], this->_swapchainLengths[i], &this->_swapchainLengths[i], image_header);
        if (XR_FAILED(result)) {
            throw EGE::WindowVRError("xrEnumerateSwapchainImages() failed");
        }
	}
}

void EGE::WindowVR::_appInitOpenglFramebuffers()
{
    glGenFramebuffers(1, &this->_framebuffer);

    for (int i=0; i < this->_viewCount; i++) {
            int width = this->_swapchainWidths[i];
            int height = this->_swapchainHeights[i];

            glGenTextures(1, &this->_depthTargets[i]);
            glBindTexture(GL_TEXTURE_2D, this->_depthTargets[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->_depthTargets[i], 0);
    }
}

void EGE::WindowVR::create()
{
    this->_appSetCallbacksAndWait();
    this->_appInitEgl();
    this->_appInitXrCreateInstance();
    this->_appInitXrGetSystem();
    this->_appInitXrEnumViews();
    this->_appInitXrCreateSession();
    this->_appInitXrCreateStageSpace();
    this->_appInitXrCreateActions();
    this->_appInitXrCreateSwapchains();
    this->_appInitOpenglFramebuffers();
    glEnable(GL_DEPTH_TEST);
}

void EGE::WindowVR::_appUpdateBeginSession()
{
    printf("Beginning Session");
    XrSessionBeginInfo begin_desc;
    begin_desc.type = XR_TYPE_SESSION_BEGIN_INFO;
    begin_desc.next = NULL;
    begin_desc.primaryViewConfigurationType = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;
    XrResult result = xrBeginSession(this->_session, &begin_desc);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrBeginSession failed");
    }
    this->_isSessionBeginEver = true;
    this->_isSessionReady = true;
}

void EGE::WindowVR::appUpdateSessionStateChange(XrSessionState state)
{
        this->_sessionState = state;
        switch (this->_sessionState) {
        case XR_SESSION_STATE_IDLE:
                printf("XR_SESSION_STATE_IDLE\n");
                break;
        case XR_SESSION_STATE_READY:
                printf("XR_SESSION_STATE_READY\n");
                this->_appUpdateBeginSession();
                break;
        case XR_SESSION_STATE_SYNCHRONIZED:
                printf("XR_SESSION_STATE_SYNCHRONIZED\n");
                break;
        case XR_SESSION_STATE_VISIBLE:
                printf("XR_SESSION_STATE_VISIBLE\n");
                break;
        case XR_SESSION_STATE_FOCUSED:
                printf("XR_SESSION_STATE_FOCUSED\n");
                break;
        case XR_SESSION_STATE_STOPPING:
                printf("XR_SESSION_STATE_STOPPING\n");
                break;
        case XR_SESSION_STATE_LOSS_PENDING:
                printf("XR_SESSION_STATE_LOSS_PENDING\n");
                break;
        case XR_SESSION_STATE_EXITING:
                printf("XR_SESSION_STATE_EXITING\n");
                break;
        default:
                printf("XR_SESSION_STATE_??? %d\n", (int)this->_sessionState);
                break;
        }
}

void EGE::WindowVR::appUpdatePumpEvents()
{
        // Pump Android Event Loop
        int events;
        struct android_poll_source *source;
        while (ALooper_pollAll(0, 0, &events, (void**)&source) >= 0 ) {
                if (source != NULL) {
                        source->process(this->_app, source);
                }
        }

        // Pump OpenXR Event Loop
        bool is_remaining_events = true;
        while (is_remaining_events) {
                XrEventDataBuffer event_data = { XR_TYPE_EVENT_DATA_BUFFER };
                XrResult result = xrPollEvent(this->_instance, &event_data);
                if (result != XR_SUCCESS) {
                        is_remaining_events = false;
                        continue;
                }

                switch (event_data.type) {
                case XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING:
                        printf("Event: XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING\n");
                        // TODO: Handle, or prefer to handle loss pending in session state?
                        break;
                case XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED: {
                        printf("Event: XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED -> ");
                        XrEventDataSessionStateChanged* ssc = (XrEventDataSessionStateChanged*)&event_data;
                        this->appUpdateSessionStateChange(ssc->state);
                        break;
                }
                case XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING:
                        printf("Event: XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING\n");
                        // TODO: Handle Reference Spaces changes
                        break;
                case XR_TYPE_EVENT_DATA_EVENTS_LOST:
                        printf("Event: XR_TYPE_EVENT_DATA_EVENTS_LOST\n");
                        // TODO: print warning
                        break;
                case XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED:
                        printf("Event: XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED\n");
                        // TODO: this shouldn't happen but handle
                        break;
                default:
                        printf("Event: Unhandled event type %d\n", event_data.type);
                        break;
                }
        }
}

void EGE::WindowVR::appUpdateBeginFrame()
{
    XrResult result;

    // Sync Input
    XrActiveActionSet active_action_set;
    active_action_set.actionSet = this->_actionSet;
    active_action_set.subactionPath = XR_NULL_PATH;
    XrActionsSyncInfo action_sync_info;
    action_sync_info.type = XR_TYPE_ACTIONS_SYNC_INFO;
    action_sync_info.next = NULL;
    action_sync_info.countActiveActionSets = 1;
    action_sync_info.activeActionSets = &active_action_set;
    result = xrSyncActions(this->_session, &action_sync_info);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrSyncActions failed");
    }

    // Wait Frame
    this->_frameState.type = XR_TYPE_FRAME_STATE;
    this->_frameState.next = NULL;
    XrFrameWaitInfo frame_wait;
    frame_wait.type = XR_TYPE_FRAME_WAIT_INFO;
    frame_wait.next = NULL;
    result = xrWaitFrame(this->_session, &frame_wait, &this->_frameState);
    this->_shouldRender = this->_frameState.shouldRender;

    // TODO: Different code paths for focussed vs. not focussed

    // Get Action States and Spaces (i.e. current state of the controller inputs)
    for (int i=0; i < HAND_COUNT; i++) {
            this->_handLocations[i].type = XR_TYPE_SPACE_LOCATION;
            this->_triggerStates[i].type = XR_TYPE_ACTION_STATE_FLOAT;
            this->_triggerClickStates[i].type = XR_TYPE_ACTION_STATE_BOOLEAN;
    }

    result = xrLocateSpace(this->_handSpaces[0], this->_stageSpace, this->_frameState.predictedDisplayTime, &this->_handLocations[0]);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrLocateSpace failed");
    }
    result = xrLocateSpace(this->_handSpaces[1], this->_stageSpace, this->_frameState.predictedDisplayTime, &this->_handLocations[1]);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrLocateSpace failed");
    }

    XrActionStateGetInfo action_get_info = { XR_TYPE_ACTION_STATE_GET_INFO };
    action_get_info.action = this->_triggerAction;
    action_get_info.subactionPath = this->_handPaths[0];
    xrGetActionStateFloat(this->_session, &action_get_info, &this->_triggerStates[0]);
    action_get_info.subactionPath = this->_handPaths[1];
    xrGetActionStateFloat(this->_session, &action_get_info, &this->_triggerStates[1]);
    action_get_info.action = this->_triggerClickAction;
    action_get_info.subactionPath = this->_handPaths[0];
    xrGetActionStateBoolean(this->_session, &action_get_info, &this->_triggerClickStates[0]);
    action_get_info.subactionPath = this->_handPaths[1];
    xrGetActionStateBoolean(this->_session, &action_get_info, &this->_triggerClickStates[1]);

    XrFrameBeginInfo frame_begin;
    frame_begin.type = XR_TYPE_FRAME_BEGIN_INFO;
    frame_begin.next = NULL;
    result = xrBeginFrame(this->_session, &frame_begin);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrBeginFrame failed");
    }
}

void EGE::WindowVR::appUpdateEndFrame()
{
    const XrCompositionLayerBaseHeader * layers[1] = { (XrCompositionLayerBaseHeader *)&this->_projectionLayer };
    XrFrameEndInfo frame_end = { XR_TYPE_FRAME_END_INFO };
    frame_end.displayTime = this->_frameState.predictedDisplayTime;
    frame_end.environmentBlendMode = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;
    frame_end.layerCount = this->_shouldRender ? 1 : 0;
    frame_end.layers = this->_shouldRender ? layers : NULL;

    XrResult result = xrEndFrame(this->_session, &frame_end);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrEndFrame failed");
    }
}

bool EGE::WindowVR::isRunning()
{
    return this->_isRunning;
}