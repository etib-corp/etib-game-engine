/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** WindowVR
*/

#include "WindowVR.hpp"

const char *BACKGROUND_VERT_SRC = R"glsl(
#version 320 es
precision highp float;

layout(location = 0) uniform mat4 view_proj;

layout(location = 0) out vec3 world_pos;

void main() {
        const vec2 positions[3] = vec2[3](vec2(-1000,-1000), vec2(3000,-1000), vec2(-1000, 3000));
        vec2 pos = positions[gl_VertexID];
        world_pos = vec3(pos.x, 0.0, pos.y);
        gl_Position = view_proj * vec4(world_pos, 1.0);
}
)glsl";

const char *BACKGROUND_FRAG_SRC = R"glsl(
#version 320 es
precision highp float;

layout(location = 1) uniform vec3 cam_pos;

layout(location = 0) in vec3 world_pos;
layout(location = 0) out vec4 out_color;

#define TILE_SIZE 1.0
#define LINE_WIDTH 0.1

void main() {
        // Based on the work of Evan Wallace: https://madebyevan.com/shaders/grid/
        vec3 cam_to_point = world_pos - cam_pos;
        float dist_sq = max(0.000001, (dot(cam_to_point, cam_to_point)));
        float fog_alpha = 1.0 / exp(0.005 * dist_sq);
        vec2 coord = world_pos.xz;
        vec2 grid = abs(fract(coord - 0.5) - 0.5) / fwidth(coord);
        float line = min(grid.x, grid.y);
        float color = 1.0 - min(line, 1.0);
        color = mix(color, 0.4, 1.0 - fog_alpha);
        vec3 col = mix(vec3(0.0), vec3(1.0, 1.0, 2.0), color);
        out_color = vec4(col, 1.0);
}
)glsl";

const char *BOX_VERT_SRC = R"glsl(
#version 320 es
precision highp float;

layout(location = 0) uniform mat4 mvp;
layout(location = 1) uniform vec2 trigger_state;
layout(location = 0) out vec3 vc;

void main() {
        const vec3 cube_positions[8] = vec3[8](
                vec3(-0.1, -0.1, -0.1),
                vec3( 0.1, -0.1, -0.1),
                vec3( 0.1, -0.1,  0.1),
                vec3(-0.1, -0.1,  0.1),
                vec3(-0.1,  0.1, -0.1),
                vec3( 0.1,  0.1, -0.1),
                vec3( 0.1,  0.1,  0.1),
                vec3(-0.1,  0.1,  0.1)
        );

        const int cube_indices[36] = int[36](
                0, 2, 1, 0, 3, 2,
                4, 5, 6, 4, 6, 7,
                0, 1, 5, 0, 5, 4,
                3, 6, 2, 3, 7, 6,
                0, 4, 7, 0, 7, 3,
                1, 2, 6, 1, 6, 5
        );

        int index = clamp(gl_VertexID, 0, 35);
        int element = clamp(cube_indices[index], 0, 7);
        float t = -(cos(3.14159 * trigger_state.x) - 1.0) / 2.0; // Ease
        vec3 pos = vec3(mix(1.0, 1.2, t)) * cube_positions[element];

        gl_Position = vec4(mvp * vec4(pos, 1.0));
        vc = mix(vec3(0, 0, 1), vec3(1, 0, 0), trigger_state.x);
}
)glsl";

const char *BOX_FRAG_SRC = R"glsl(
#version 320 es
precision highp float;

layout(location = 0) in vec3 vc;
layout(location = 0) out vec4 outColor;

void main() {
        outColor = vec4(vc, 1.0);
}
)glsl";

const char *SCREEN_VERT_SRC = R"glsl(
#version 320 es
precision highp float;

layout(location = 0) uniform mat4 mvp;
layout(location = 0) out vec2 screen_uv;

void main() {
        const vec2 screen_pos[4] = vec2[4](
                vec2(-0.11, 0.12),
                vec2( 0.11, 0.12),
                vec2(-0.11, 0.32),
                vec2(0.11, 0.32)
        );

        const vec2 screen_tex[4] = vec2[4](
                vec2(0.0, 0.0),
                vec2(1.0, 0.0),
                vec2(0.0, 1.0),
                vec2(1.0, 1.0)
        );

        const int screen_indices[6] = int[6](
                0, 1, 2,
                1, 3, 2
        );

        int element = screen_indices[gl_VertexID];
        vec2 pos = screen_pos[element];

        gl_Position = vec4(mvp * vec4(pos.x, 0.0, -pos.y, 1.0));
        screen_uv = screen_tex[element];
}
)glsl";

const char *SCREEN_FRAG_SRC = R"glsl(
#version 320 es
precision highp float;

layout(location = 1) uniform sampler2D tex;

layout(location = 0) in vec2 screen_uv;
layout(location = 0) out vec4 outColor;

void main() {
        outColor = texture(tex, screen_uv);
}
)glsl";

void matrix_identity(float *result) {
	result[0] = (1.0);
	result[1] = (0.0);
	result[2] = (0.0);
	result[3] = (0.0);
	result[4] = (0.0);
	result[5] = (1.0);
	result[6] = (0.0);
	result[7] = (0.0);
	result[8] = (0.0);
	result[9] = (0.0);
	result[10] = (1.0);
	result[11] = (0.0);
	result[12] = (0.0);
	result[13] = (0.0);
	result[14] = (0.0);
	result[15] = (1.0);
}

void matrix_translate(float *result, float* m0, float* v0) {
	result[0] = m0[0];
	result[1] = m0[1];
	result[2] = m0[2];
	result[3] = m0[3];
	result[4] = m0[4];
	result[5] = m0[5];
	result[6] = m0[6];
	result[7] = m0[7];
	result[8] = m0[8];
	result[9] = m0[9];
	result[10] = m0[10];
	result[11] = m0[11];
	result[12] = m0[12] + v0[0];
	result[13] = m0[13] + v0[1];
	result[14] = m0[14] + v0[2];
	result[15] = m0[15];
}

void matrix_rotation_from_quat(float *result, float *q0) {
	float xx = q0[0] * q0[0];
	float yy = q0[1] * q0[1];
	float zz = q0[2] * q0[2];
	float xy = q0[0] * q0[1];
	float zw = q0[2] * q0[3];
	float xz = q0[0] * q0[2];
	float yw = q0[1] * q0[3];
	float yz = q0[1] * q0[2];
	float xw = q0[0] * q0[3];
	result[0] = (1.0) - (2.0) * (yy + zz);
	result[1] = (2.0) * (xy + zw);
	result[2] = (2.0) * (xz - yw);
	result[3] = (0.0);
	result[4] = (2.0) * (xy - zw);
	result[5] = (1.0) - (2.0) * (xx + zz);
	result[6] = (2.0) * (yz + xw);
	result[7] = (0.0);
	result[8] = (2.0) * (xz + yw);
	result[9] = (2.0) * (yz - xw);
	result[10] = (1.0) - (2.0) * (xx + yy);
	result[11] = (0.0);
	result[12] = (0.0);
	result[13] = (0.0);
	result[14] = (0.0);
	result[15] = (1.0);
}

void matrix_inverse(float *result, float *m0) {
	float inverse[16];
	float inverted_determinant;
	float m11 = m0[0];
	float m21 = m0[1];
	float m31 = m0[2];
	float m41 = m0[3];
	float m12 = m0[4];
	float m22 = m0[5];
	float m32 = m0[6];
	float m42 = m0[7];
	float m13 = m0[8];
	float m23 = m0[9];
	float m33 = m0[10];
	float m43 = m0[11];
	float m14 = m0[12];
	float m24 = m0[13];
	float m34 = m0[14];
	float m44 = m0[15];
	inverse[0] = m22 * m33 * m44 - m22 * m43 * m34 - m23 * m32 * m44 + m23 * m42 * m34 + m24 * m32 * m43 - m24 * m42 * m33;
	inverse[4] = -m12 * m33 * m44 + m12 * m43 * m34 + m13 * m32 * m44 - m13 * m42 * m34 - m14 * m32 * m43 + m14 * m42 * m33;
	inverse[8] = m12 * m23 * m44 - m12 * m43 * m24 - m13 * m22 * m44 + m13 * m42 * m24 + m14 * m22 * m43 - m14 * m42 * m23;
	inverse[12] = -m12 * m23 * m34 + m12 * m33 * m24 + m13 * m22 * m34 - m13 * m32 * m24 - m14 * m22 * m33 + m14 * m32 * m23;
	inverse[1] = -m21 * m33 * m44 + m21 * m43 * m34 + m23 * m31 * m44 - m23 * m41 * m34 - m24 * m31 * m43 + m24 * m41 * m33;
	inverse[5] =m11 * m33 * m44 -m11 * m43 * m34 - m13 * m31 * m44 + m13 * m41 * m34 + m14 * m31 * m43 - m14 * m41 * m33;
	inverse[9] = -m11 * m23 * m44 +m11 * m43 * m24 + m13 * m21 * m44 - m13 * m41 * m24 - m14 * m21 * m43 + m14 * m41 * m23;
	inverse[13] =m11 * m23 * m34 -m11 * m33 * m24 - m13 * m21 * m34 + m13 * m31 * m24 + m14 * m21 * m33 - m14 * m31 * m23;
	inverse[2] = m21 * m32 * m44 - m21 * m42 * m34 - m22 * m31 * m44 + m22 * m41 * m34 + m24 * m31 * m42 - m24 * m41 * m32;
	inverse[6] = -m11 * m32 * m44 +m11 * m42 * m34 + m12 * m31 * m44 - m12 * m41 * m34 - m14 * m31 * m42 + m14 * m41 * m32;
	inverse[10] =m11 * m22 * m44 -m11 * m42 * m24 - m12 * m21 * m44 + m12 * m41 * m24 + m14 * m21 * m42 - m14 * m41 * m22;
	inverse[14] = -m11 * m22 * m34 +m11 * m32 * m24 + m12 * m21 * m34 - m12 * m31 * m24 - m14 * m21 * m32 + m14 * m31 * m22;
	inverse[3] = -m21 * m32 * m43 + m21 * m42 * m33 + m22 * m31 * m43 - m22 * m41 * m33 - m23 * m31 * m42 + m23 * m41 * m32;
	inverse[7] = m11 * m32 * m43 - m11 * m42 * m33 - m12 * m31 * m43 + m12 * m41 * m33 + m13 * m31 * m42 - m13 * m41 * m32;
	inverse[11] = -m11 * m22 * m43 + m11 * m42 * m23 + m12 * m21 * m43 - m12 * m41 * m23 - m13 * m21 * m42 + m13 * m41 * m22;
	inverse[15] = m11 * m22 * m33 - m11 * m32 * m23 - m12 * m21 * m33 + m12 * m31 * m23 + m13 * m21 * m32 - m13 * m31 * m22;
	inverted_determinant = (1.0) / (m11 * inverse[0] + m21 * inverse[4] + m31 * inverse[8] + m41 * inverse[12]);
	result[0] = inverse[0] * inverted_determinant;
	result[1] = inverse[1] * inverted_determinant;
	result[2] = inverse[2] * inverted_determinant;
	result[3] = inverse[3] * inverted_determinant;
	result[4] = inverse[4] * inverted_determinant;
	result[5] = inverse[5] * inverted_determinant;
	result[6] = inverse[6] * inverted_determinant;
	result[7] = inverse[7] * inverted_determinant;
	result[8] = inverse[8] * inverted_determinant;
	result[9] = inverse[9] * inverted_determinant;
	result[10] = inverse[10] * inverted_determinant;
	result[11] = inverse[11] * inverted_determinant;
	result[12] = inverse[12] * inverted_determinant;
	result[13] = inverse[13] * inverted_determinant;
	result[14] = inverse[14] * inverted_determinant;
	result[15] = inverse[15] * inverted_determinant;
}

void matrix_proj_opengl(float *proj, float left, float right, float up, float down, float near, float far) {

        const float tan_left = tan(left);
        const float tan_right = tan(right);

        const float tan_down = tan(down);
        const float tan_up = tan(up);

        const float tan_width = tan_right - tan_left;
        const float tan_height = (tan_up - tan_down);

        const float offset = near;

        proj[0] = 2 / tan_width;
        proj[4] = 0;
        proj[8] = (tan_right + tan_left) / tan_width;
        proj[12] = 0;

        proj[1] = 0;
        proj[5] = 2 / tan_height;
        proj[9] = (tan_up + tan_down) / tan_height;
        proj[13] = 0;

        proj[2] = 0;
        proj[6] = 0;
        proj[10] = -(far + offset) / (far - near);
        proj[14] = -(far * (near + offset)) / (far - near);

        proj[3] = 0;
        proj[7] = 0;
        proj[11] = -1;
        proj[15] = 0;
}

void matrix_multiply(float *result, float *m0, float *m1) {
	float multiplied[16];
	multiplied[0] = m0[0] * m1[0] + m0[4] * m1[1] + m0[8] * m1[2] + m0[12] * m1[3];
	multiplied[1] = m0[1] * m1[0] + m0[5] * m1[1] + m0[9] * m1[2] + m0[13] * m1[3];
	multiplied[2] = m0[2] * m1[0] + m0[6] * m1[1] + m0[10] * m1[2] + m0[14] * m1[3];
	multiplied[3] = m0[3] * m1[0] + m0[7] * m1[1] + m0[11] * m1[2] + m0[15] * m1[3];
	multiplied[4] = m0[0] * m1[4] + m0[4] * m1[5] + m0[8] * m1[6] + m0[12] * m1[7];
	multiplied[5] = m0[1] * m1[4] + m0[5] * m1[5] + m0[9] * m1[6] + m0[13] * m1[7];
	multiplied[6] = m0[2] * m1[4] + m0[6] * m1[5] + m0[10] * m1[6] + m0[14] * m1[7];
	multiplied[7] = m0[3] * m1[4] + m0[7] * m1[5] + m0[11] * m1[6] + m0[15] * m1[7];
	multiplied[8] = m0[0] * m1[8] + m0[4] * m1[9] + m0[8] * m1[10] + m0[12] * m1[11];
	multiplied[9] = m0[1] * m1[8] + m0[5] * m1[9] + m0[9] * m1[10] + m0[13] * m1[11];
	multiplied[10] = m0[2] * m1[8] + m0[6] * m1[9] + m0[10] * m1[10] + m0[14] * m1[11];
	multiplied[11] = m0[3] * m1[8] + m0[7] * m1[9] + m0[11] * m1[10] + m0[15] * m1[11];
	multiplied[12] = m0[0] * m1[12] + m0[4] * m1[13] + m0[8] * m1[14] + m0[12] * m1[15];
	multiplied[13] = m0[1] * m1[12] + m0[5] * m1[13] + m0[9] * m1[14] + m0[13] * m1[15];
	multiplied[14] = m0[2] * m1[12] + m0[6] * m1[13] + m0[10] * m1[14] + m0[14] * m1[15];
	multiplied[15] = m0[3] * m1[12] + m0[7] * m1[13] + m0[11] * m1[14] + m0[15] * m1[15];
	result[0] = multiplied[0];
	result[1] = multiplied[1];
	result[2] = multiplied[2];
	result[3] = multiplied[3];
	result[4] = multiplied[4];
	result[5] = multiplied[5];
	result[6] = multiplied[6];
	result[7] = multiplied[7];
	result[8] = multiplied[8];
	result[9] = multiplied[9];
	result[10] = multiplied[10];
	result[11] = multiplied[11];
	result[12] = multiplied[12];
	result[13] = multiplied[13];
	result[14] = multiplied[14];
	result[15] = multiplied[15];
}


EGE::WindowVR::WindowVR(android_app *app)
{
    LOGV("WindowVR Constructor hello\n");
    this->_app = app;
    this->_isWindowInit = false;

    this->_position = {0.0, 0.0, 0.0};

    this->_eglDisplay = EGL_NO_DISPLAY;
    this->_eglConfig = 0;
    this->_eglContext = EGL_NO_CONTEXT;
    this->_eglSurface = EGL_NO_SURFACE;

    this->_instance = XR_NULL_HANDLE;
    this->_system = 0;
    this->_session = XR_NULL_HANDLE;

    this->_viewCount = 0;
    this->_viewConfigs[0] = {};
    this->_viewConfigs[1] = {};
    this->_viewConfigs[2] = {};
    this->_viewConfigs[3] = {};

    this->_stageSpace = XR_NULL_HANDLE;
    this->_handSpaces[0] = XR_NULL_HANDLE;
    this->_handSpaces[1] = XR_NULL_HANDLE;

    this->_touchControllerPath = 0;
    this->_handPaths[0] = 0;
    this->_handPaths[1] = 0;
    this->_squeezeValuePaths[0] = 0;
    this->_squeezeValuePaths[1] = 0;
    this->_triggerValuePaths[0] = 0;
    this->_triggerValuePaths[1] = 0;
    this->_posePaths[0] = 0;
    this->_posePaths[1] = 0;
    this->_hapticPaths[0] = 0;
    this->_hapticPaths[1] = 0;
    this->_menuClickPaths[0] = 0;
    this->_menuClickPaths[1] = 0;

    this->_actionSet = XR_NULL_HANDLE;
    this->_grabAction = XR_NULL_HANDLE;
    this->_triggerAction = XR_NULL_HANDLE;
    this->_triggerClickAction = XR_NULL_HANDLE;
    this->_poseAction = XR_NULL_HANDLE;
    this->_menuAction = XR_NULL_HANDLE;

    this->_swapchainHeights[0] = 0;
    this->_swapchainHeights[1] = 0;
    this->_swapchainHeights[2] = 0;
    this->_swapchainHeights[3] = 0;
    this->_swapchainWidths[0] = 0;
    this->_swapchainWidths[1] = 0;
    this->_swapchainWidths[2] = 0;
    this->_swapchainWidths[3] = 0;
    this->_swapchains[0] = XR_NULL_HANDLE;
    this->_swapchains[1] = XR_NULL_HANDLE;
    this->_swapchains[2] = XR_NULL_HANDLE;
    this->_swapchains[3] = XR_NULL_HANDLE;
    this->_swapchainLengths[0] = {0};
    this->_swapchainLengths[1] = {0};
    this->_swapchainLengths[2] = {0};
    this->_swapchainLengths[3] = {0};

    this->_handLocations[0] = {};
    this->_handLocations[1] = {};
    this->_triggerStates[0] = {};
    this->_triggerStates[1] = {};
    this->_triggerClickStates[0] = {};
    this->_triggerClickStates[1] = {};

    this->_sessionState = XR_SESSION_STATE_UNKNOWN;
    this->_frameState = {};

    this->_shouldRender = false;
    this->_isRunning = true;
    this->_session = XR_NULL_HANDLE;
    this->_isSessionReady = false;
    this->_isSessionBeginEver = false;

    this->_viewSubmitCount = 0;
    this->_projectionLayer = {};
    this->_projectionLayerViews[0] = {};
    this->_projectionLayerViews[1] = {};
    this->_projectionLayerViews[2] = {};
    this->_projectionLayerViews[3] = {};
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
    for (int i=0; i < extension_count; i++) {
            extension_properties[i].type = XR_TYPE_EXTENSION_PROPERTIES;
            extension_properties[i].next = NULL;
    }
    result = xrEnumerateInstanceExtensionProperties(NULL, extension_count, &extension_count, extension_properties);
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
    if (this->_viewCount <= 0) {
        throw EGE::WindowVRError("No view configurations found");
    }
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
    // Create Space
    uint32_t reference_spaces_count;
    XrReferenceSpaceType reference_spaces[64];
    result = xrEnumerateReferenceSpaces(this->_session, 0, &reference_spaces_count, NULL);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrEnumerateReferenceSpaces failed");
    }
    for (int i = 0; i < reference_spaces_count; i++) {
            reference_spaces[i] = XR_REFERENCE_SPACE_TYPE_VIEW;
    }
    result = xrEnumerateReferenceSpaces(this->_session, reference_spaces_count, &reference_spaces_count, reference_spaces);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrEnumerateReferenceSpaces failed");
    }
    printf("Reference Spaces:\n");
    for (int i = 0; i < reference_spaces_count; i++) {
            switch (reference_spaces[i]) {
            case XR_REFERENCE_SPACE_TYPE_VIEW:
                    printf("	XR_REFERENCE_SPACE_TYPE_VIEW\n");
                    break;
            case XR_REFERENCE_SPACE_TYPE_LOCAL:
                    printf("	XR_REFERENCE_SPACE_TYPE_LOCAL\n");
                    break;
            case XR_REFERENCE_SPACE_TYPE_STAGE:
                    printf("	XR_REFERENCE_SPACE_TYPE_STAGE\n");
                    break;
            default:
                    printf("	XR_REFERENCE_SPACE_TYPE_%d\n", reference_spaces[i]);
                    break;
            }
    }

	XrPosef identity_pose = { {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f} };
	XrReferenceSpaceCreateInfo space_desc;
	space_desc.type = XR_TYPE_REFERENCE_SPACE_CREATE_INFO;
	space_desc.next = NULL;
	space_desc.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
	space_desc.poseInReferenceSpace = identity_pose;
	result = xrCreateReferenceSpace(this->_session, &space_desc, &this->_stageSpace);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateReferenceSpace failed");
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
    xrStringToPath(this->_instance, "/user/hand/left/input/thumbstick", &this->_thumbstickPaths[0]);
    xrStringToPath(this->_instance, "/user/hand/right/input/thumbstick", &this->_thumbstickPaths[1]);


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

    XrActionCreateInfo thumbstickDesc;
    thumbstickDesc.type = XR_TYPE_ACTION_CREATE_INFO;
    thumbstickDesc.next = NULL;
    thumbstickDesc.actionType = XR_ACTION_TYPE_VECTOR2F_INPUT;
    strcpy(thumbstickDesc.actionName, "thumbstick" );
    strcpy(thumbstickDesc.localizedActionName, "Thumbstick");
    thumbstickDesc.countSubactionPaths = 2;
    thumbstickDesc.subactionPaths = this->_handPaths;
    result = xrCreateAction(this->_actionSet, &thumbstickDesc, &this->_thumbstickAction);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrCreateAction() failed");
    }

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
            // {this->_menuAction, this->_menuClickPaths[1]},
            {this->_vibrateAction, this->_hapticPaths[0]},
            {this->_vibrateAction, this->_hapticPaths[1]},
            {this->_thumbstickAction, this->_thumbstickPaths[0]},
            {this->_thumbstickAction, this->_thumbstickPaths[1]}
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
    printf("Swapchains:\n");
    for (int i = 0; i < this->_viewCount; i++) {
            printf("        width: %d\n", this->_swapchainWidths[i]);
            printf("        height: %d\n", this->_swapchainHeights[i]);
            printf("        length: %d\n", this->_swapchainLengths[i]);
    }
}

void EGE::WindowVR::_appInitOpengl()
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


    // glGenFramebuffers(1, &this->_screenFramebuffer);
    // glBindFramebuffer(GL_FRAMEBUFFER, this->_screenFramebuffer);

    // glGenTextures(1, &this->_screenTexture);
    // glBindTexture(GL_TEXTURE_2D, this->_screenTexture);
    // glBindTexture(GL_TEXTURE_2D, this->_screenTexture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 200, 200, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->_screenTexture, 0);

    // GLenum draw_buffers[1] = {GL_COLOR_ATTACHMENT0};
    // glDrawBuffers(1, draw_buffers);

    // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    // }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glDisable(GL_BLEND);

    // Box Program
    // uint32_t vert_shd = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vert_shd, 1, &BOX_VERT_SRC, NULL);
    // glCompileShader(vert_shd);

    int success;
    // glGetShaderiv(vert_shd, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //         char info_log[512];
    //         glGetShaderInfoLog(vert_shd, 512, NULL, info_log);
    // }

    // uint32_t frag_shd = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(frag_shd, 1, &BOX_FRAG_SRC, NULL);
    // glCompileShader(frag_shd);

    // glGetShaderiv(frag_shd, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //         char info_log[512];
    //         glGetShaderInfoLog(frag_shd, 512, NULL, info_log);
    // }

    // this->_boxProgram = glCreateProgram();
    // glAttachShader(this->_boxProgram, vert_shd);
    // glAttachShader(this->_boxProgram, frag_shd);
    // glLinkProgram(this->_boxProgram);

    // glGetProgramiv(this->_boxProgram, GL_LINK_STATUS, &success);
    // if (!success) {
    //         char info_log[512];
    //         glGetProgramInfoLog(this->_boxProgram, 512, NULL, info_log);
    // }

    // glDeleteShader(vert_shd);
    // glDeleteShader(frag_shd);

    // Background Program
    uint32_t vert_shd = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shd, 1, &BACKGROUND_VERT_SRC, NULL);
    glCompileShader(vert_shd);

    glGetShaderiv(vert_shd, GL_COMPILE_STATUS, &success);
    if (!success) {
            char info_log[512];
            glGetShaderInfoLog(vert_shd, 512, NULL, info_log);
    }

    uint32_t frag_shd = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shd, 1, &BACKGROUND_FRAG_SRC, NULL);
    glCompileShader(frag_shd);

    glGetShaderiv(frag_shd, GL_COMPILE_STATUS, &success);
    if (!success) {
            char info_log[512];
            glGetShaderInfoLog(frag_shd, 512, NULL, info_log);
    }

    this->_backgroundProgram = glCreateProgram();
    glAttachShader(this->_backgroundProgram, vert_shd);
    glAttachShader(this->_backgroundProgram, frag_shd);
    glLinkProgram(this->_backgroundProgram);

    glGetProgramiv(this->_backgroundProgram, GL_LINK_STATUS, &success);
    if (!success) {
            char info_log[512];
            glGetProgramInfoLog(this->_backgroundProgram, 512, NULL, info_log);
    }

    glDeleteShader(vert_shd);
    glDeleteShader(frag_shd);

    // vert_shd = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vert_shd, 1, &SCREEN_VERT_SRC, NULL);
    // glCompileShader(vert_shd);

    // glGetShaderiv(vert_shd, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //         char info_log[512];
    //         glGetShaderInfoLog(vert_shd, 512, NULL, info_log);
    // }

    // frag_shd = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(frag_shd, 1, &SCREEN_FRAG_SRC, NULL);
    // glCompileShader(frag_shd);

    // glGetShaderiv(frag_shd, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //         char info_log[512];
    //         glGetShaderInfoLog(frag_shd, 512, NULL, info_log);
    // }

    // this->_screenProgram = glCreateProgram();
    // glAttachShader(this->_screenProgram, vert_shd);
    // glAttachShader(this->_screenProgram, frag_shd);
    // glLinkProgram(this->_screenProgram);

    // glGetProgramiv(this->_screenProgram, GL_LINK_STATUS, &success);
    // if (!success) {
    //         char info_log[512];
    //         glGetProgramInfoLog(this->_screenProgram, 512, NULL, info_log);
    // }

    // glDeleteShader(vert_shd);
    // glDeleteShader(frag_shd);
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
    this->_appInitOpengl();
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
                    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING");
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
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrWaitFrame failed");
    }
    // TODO: Different code paths for focussed vs. not focussed

    // Get Action States and Spaces (i.e. current state of the controller inputs)
    for (int i=0; i < HAND_COUNT; i++) {
            this->_handLocations[i].type = XR_TYPE_SPACE_LOCATION;
            this->_triggerStates[i].type = XR_TYPE_ACTION_STATE_FLOAT;
            this->_triggerClickStates[i].type = XR_TYPE_ACTION_STATE_BOOLEAN;
            this->_thumbstickStates[i].type = XR_TYPE_ACTION_STATE_VECTOR2F;
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

    action_get_info.action = this->_thumbstickAction;
    action_get_info.subactionPath = this->_handPaths[0];
    xrGetActionStateVector2f(this->_session, &action_get_info, &this->_thumbstickStates[0]);
    action_get_info.subactionPath = this->_handPaths[1];
    xrGetActionStateVector2f(this->_session, &action_get_info, &this->_thumbstickStates[1]);

    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Trigger: x = %f", this->_thumbstickStates[0].currentState.x);
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Trigger: y = %f", this->_thumbstickStates[0].currentState.y);

    XrFrameBeginInfo frame_begin;
    frame_begin.type = XR_TYPE_FRAME_BEGIN_INFO;
    frame_begin.next = NULL;
    result = xrBeginFrame(this->_session, &frame_begin);
    if (XR_FAILED(result)) {
        throw EGE::WindowVRError("xrBeginFrame failed");
    }
}

void EGE::WindowVR::addModel(const std::string &key, const std::shared_ptr<EGE::ModelVR> &model)
{
    this->_drawable[key].second.push_back(model);
}

void EGE::WindowVR::removeModel(const std::string &key, const std::shared_ptr<EGE::ModelVR> &model)
{
    this->_drawable[key].second.erase(std::remove(this->_drawable[key].second.begin(), this->_drawable[key].second.end(), model), this->_drawable[key].second.end());
}

void EGE::WindowVR::addNewSlot(const std::string &key, const std::shared_ptr<EGE::Shader> &shader)
{
    this->_drawable[key] = {shader, {}};
}

void EGE::WindowVR::display()
{
    XrResult result;

    this->_projectionLayer = { XR_TYPE_COMPOSITION_LAYER_PROJECTION };
    this->_projectionLayer.layerFlags = 0;
    this->_projectionLayer.next = NULL;
    this->_projectionLayer.space = this->_stageSpace;

    // Locate Views
    XrView views[MAX_VIEWS];
    for (int i=0; i < this->_viewCount; i++) {
            views[i].type = XR_TYPE_VIEW;
            views[i].next = NULL;
    }
    XrViewState view_state = { XR_TYPE_VIEW_STATE };
    XrViewLocateInfo view_locate_info;
    view_locate_info.type = XR_TYPE_VIEW_LOCATE_INFO;
    view_locate_info.viewConfigurationType = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;
    view_locate_info.displayTime = this->_frameState.predictedDisplayTime;
    view_locate_info.space = this->_stageSpace;
    result = xrLocateViews(this->_session, &view_locate_info, &view_state, this->_viewCount, &this->_viewSubmitCount, views);

    // Fill in Projection Views info
    for (int i = 0; i < this->_viewSubmitCount; i++) {
            this->_projectionLayerViews[i].type = XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW;
            this->_projectionLayerViews[i].pose = views[i].pose;
            this->_projectionLayerViews[i].fov = views[i].fov;
            this->_projectionLayerViews[i].subImage.swapchain = this->_swapchains[i];
            this->_projectionLayerViews[i].subImage.imageRect.offset.x = 0;
            this->_projectionLayerViews[i].subImage.imageRect.offset.y = 0;
            this->_projectionLayerViews[i].subImage.imageRect.extent.width = this->_swapchainWidths[i];
            this->_projectionLayerViews[i].subImage.imageRect.extent.height = this->_swapchainHeights[i];
            this->_projectionLayerViews[i].subImage.imageArrayIndex = 0;
    }
    for (int v = 0; v < this->_viewSubmitCount; v++) {
        // Acquire and wait for the swapchain image
        uint32_t image_index;
        XrSwapchainImageAcquireInfo acquire_info = { XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO };
        result = xrAcquireSwapchainImage(this->_swapchains[v], &acquire_info, &image_index);
        XrSwapchainImageWaitInfo wait_info = { XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO };
        wait_info.timeout = XR_INFINITE_DURATION;
        result = xrWaitSwapchainImage(this->_swapchains[v], &wait_info);
        XrSwapchainImageOpenGLESKHR swapchain_image = this->_swapchainImages[v][image_index];
        uint32_t colour_tex = swapchain_image.image;
        int width = this->_projectionLayerViews[v].subImage.imageRect.extent.width;
        int height = this->_projectionLayerViews[v].subImage.imageRect.extent.height;

        // Projection
        float left = this->_projectionLayerViews[v].fov.angleLeft;
        float right = this->_projectionLayerViews[v].fov.angleRight;
        float up = this->_projectionLayerViews[v].fov.angleUp;
        float down = this->_projectionLayerViews[v].fov.angleDown;
        float proj[16];
        matrix_proj_opengl(proj, left, right, up, down, 0.01, 100.0);

        // View, View Projection
        float translation[16];
        float rotation[16];
        float view[16];
        float view_proj[16];
        float inverse_view_proj[16];
        matrix_identity(translation);
        XrVector3f pos = {0, 0, 0};
        this->_projectionLayerViews[v].pose.position.x += this->_position.x * 0.1;
        this->_projectionLayerViews[v].pose.position.z += this->_position.z * 0.1;
        matrix_translate(translation, translation, (float *)& this->_projectionLayerViews[v].pose.position);
        matrix_rotation_from_quat(rotation, (float *)&this->_projectionLayerViews[v].pose.orientation);
        matrix_multiply(view, translation, rotation);
        matrix_inverse(view, view);
        matrix_multiply(view_proj, proj, view);
        matrix_inverse(inverse_view_proj, view_proj);

        // get front vector from view matrix
        float front[3] = {view[2], view[6], view[10]};
        // get right vector from view matrix
        float right_vector[3] = {view[0], view[4], view[8]};
        // get up vector from view matrix
        float up_vector[3] = {view[1], view[5], view[9]};




        this->_position.x -= this->_thumbstickStates[0].currentState.y * front[0];
        this->_position.y -= this->_thumbstickStates[0].currentState.y * front[1];
        this->_position.z -= this->_thumbstickStates[0].currentState.y * front[2];

        this->_position.x += this->_thumbstickStates[0].currentState.x * right_vector[0];
        this->_position.y += this->_thumbstickStates[0].currentState.x * right_vector[1];
        this->_position.z += this->_thumbstickStates[0].currentState.x * right_vector[2];



        // // Left MVP
        // float left_translation[16];
        // float left_rotation[16];
        // float left_model[16];
        // float left_mvp[16];
        // matrix_identity(left_translation);
        // matrix_translate(left_translation, left_translation, (float *)&this->_handLocations[0].pose.position);
        // matrix_rotation_from_quat(left_rotation, (float *)&this->_handLocations[0].pose.orientation);
        // matrix_multiply(left_model, left_translation, left_rotation);
        // matrix_multiply(left_mvp, view_proj, left_model);

        // // Right Model
        // float right_translation[16];
        // float right_rotation[16];
        // float right_model[16];
        // float right_mvp[16];
        // matrix_identity(right_translation);
        // matrix_translate(right_translation, right_translation, (float *)&this->_handLocations[1].pose.position);
        // matrix_rotation_from_quat(right_rotation, (float *)&this->_handLocations[1].pose.orientation);
        // matrix_multiply(right_model, right_translation, right_rotation);
        // matrix_multiply(right_mvp, view_proj, right_model);

        // Render into the swapchain directlyleft_model
        glBindFramebuffer(GL_FRAMEBUFFER, this->_framebuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colour_tex, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->_depthTargets[v], 0);
        glViewport(0, 0, width, height);
        glClearColor(0.4, 0.4, 0.8, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render Background
        glUseProgram(this->_backgroundProgram);
        glUniformMatrix4fv(0, 1, GL_FALSE, view_proj);
        glUniform3fv(1, 1, (float *)&this->_handLocations[0].pose.position);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // // Render Left Hand
        // glUseProgram(this->_boxProgram);
        // glUniformMatrix4fv(0, 1, GL_FALSE, left_mvp);
        // glUniform2f(1, this->_triggerStates[0].currentState, (float)(this->_triggerClickStates[0].currentState));
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        // // Render Right Hand
        // glUseProgram(this->_boxProgram);
        // glUniformMatrix4fv(0, 1, GL_FALSE, right_mvp);
        // glUniform2f(1, this->_triggerStates[1].currentState, (float)(this->_triggerClickStates[1].currentState));
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        for (auto& d : this->_drawable) {
            auto shader = d.second.first;
            auto models = d.second.second;
            shader->use();
            int id = glGetUniformLocation(shader->getID(), "view_proj");
            glUniformMatrix4fv(id, 1, GL_FALSE, view_proj);
            for (auto& model : models) {
                model->draw(*shader);
            }
        }

        // // Bind Screen Texture
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, this->_screenTexture);

        // // Render Screen
        // glUseProgram(this->_screenProgram);
        // glUniformMatrix4fv(0, 1, GL_FALSE, left_mvp);
        // glUniform1i(1, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 6);

        // Release Image
        XrSwapchainImageReleaseInfo release_info = { XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO };
        result = xrReleaseSwapchainImage(this->_swapchains[v], &release_info);
    }

    this->_projectionLayer.viewCount = this->_viewSubmitCount;
    this->_projectionLayer.views = &this->_projectionLayerViews[0];

    // glBindFramebuffer(GL_FRAMEBUFFER, this->_screenFramebuffer);
    // glViewport(0, 0, 200, 200);

    // glClearColor(0.0, 0.0, 0.0, 0.0);
    // glClear(GL_COLOR_BUFFER_BIT);
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

bool EGE::WindowVR::isSessionReady()
{
    return this->_isSessionReady;
}

bool EGE::WindowVR::isShouldRender()
{
    return this->_shouldRender;
}
