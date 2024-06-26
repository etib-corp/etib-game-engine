/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Event
*/

#include "Event.hpp"

EGE::GlfwWindowCloseCallbackFunction *EGE::GlfwWindowCloseCallbackFunction::_instance = nullptr;
EGE::GlfwWindowFocusCallbackFunction *EGE::GlfwWindowFocusCallbackFunction::_instance = nullptr;
EGE::GlfwWindowLostFocusCallbackFunction *EGE::GlfwWindowLostFocusCallbackFunction::_instance = nullptr;
EGE::GlfwWindowFileDropCallbackFunction *EGE::GlfwWindowFileDropCallbackFunction::_instance = nullptr;
EGE::GlfwWindowScrollCallbackFunction *EGE::GlfwWindowScrollCallbackFunction::_instance = nullptr;
EGE::GlfwWindowContentScaleChangedCallbackFunction *EGE::GlfwWindowContentScaleChangedCallbackFunction::_instance = nullptr;
EGE::GlfwWindowFramebufferResizedCallbackFunction *EGE::GlfwWindowFramebufferResizedCallbackFunction::_instance = nullptr;
EGE::GlfwWindowIconifiedCallbackFunction *EGE::GlfwWindowIconifiedCallbackFunction::_instance = nullptr;
EGE::GlfwWindowMaximizedCallbackFunction *EGE::GlfwWindowMaximizedCallbackFunction::_instance = nullptr;
EGE::GlfwWindowMovedCallbackFunction *EGE::GlfwWindowMovedCallbackFunction::_instance = nullptr;
EGE::GlfwWindowResizedCallbackFunction *EGE::GlfwWindowResizedCallbackFunction::_instance = nullptr;
EGE::GlfwWindowRefreshedCallbackFunction *EGE::GlfwWindowRefreshedCallbackFunction::_instance = nullptr;
EGE::GlfwCursorCallbackFunction *EGE::GlfwCursorCallbackFunction::_instance = nullptr;

EGE::Event::Trigger::Trigger(EGE::Event::Type type, std::uint32_t trigger, EGE::Event::Mode mode, std::function<void()> callback, std::uint8_t joystickId)
    : _type(type), _trigger(trigger), _mode(mode), _callback(callback), _joystickId(joystickId)
{
}

EGE::Event::Trigger::Trigger(EGE::Event::Type type, std::uint32_t trigger, EGE::Event::Mode mode, std::function<void(float)> callback, std::uint8_t joystickId)
    : _type(type), _trigger(trigger), _mode(mode), _joystickAxisCallback(callback), _joystickId(joystickId)
{
}

EGE::Event::Trigger::~Trigger()
{
}

std::uint32_t EGE::Event::Trigger::getTrigger() const
{
    return this->_trigger;
}

EGE::Event::Type EGE::Event::Trigger::getType() const
{
    return this->_type;
}

std::int8_t EGE::Event::Trigger::getJoystickId() const
{
    return this->_joystickId;
}

EGE::Event::Mode EGE::Event::Trigger::getMode() const
{
    return this->_mode;
}

std::function<void()> EGE::Event::Trigger::getCallback() const
{
    if (!this->_callback)
        throw EGE::Event::EventError("Callback is not set");
    return this->_callback;
}

std::function<void(float)> EGE::Event::Trigger::getJoystickAxisCallback() const
{
    if (!this->_joystickAxisCallback)
        throw EGE::Event::EventError("JoystickAxis Callback is not set");
    return this->_joystickAxisCallback;
}

bool EGE::Event::Trigger::isPressed() const
{
    return this->_pressed;
}

void EGE::Event::Trigger::setPressed(bool pressed)
{
    this->_pressed = pressed;
}

void EGE::Event::Trigger::setCallback(std::function<void()> callback)
{
    this->_callback = callback;
}

bool EGE::Event::Trigger::operator==(const EGE::Event::Trigger &other) const
{
    return this->_trigger == other._trigger && this->_type == other._type && this->_joystickId == other._joystickId && this->_mode == other._mode;
}

EGE::Event::Trigger& EGE::Event::Trigger::operator=(const EGE::Event::Trigger &other)
{
    if (this != &other) {
        this->_mode = other._mode;
        this->_callback = other._callback;
        this->_joystickAxisCallback = other._joystickAxisCallback;
        this->_pressed = other._pressed;
    }
    return *this;
}

EGE::Event::Event(GLFWwindow *window)
{
    this->_window = window;
    this->_joystickEnabled = false;
}

EGE::Event::~Event()
{
}

bool EGE::Event::bindTrigger(const EGE::Event::Trigger& trigger)
{
    if (std::find(this->_triggers.begin(), this->_triggers.end(), trigger) != this->_triggers.end())
        return false;
    if (trigger.getType() == EGE::Event::Type::Window)
        throw EGE::Event::EventError("Window event must be binded with bindWindowTrigger");
    this->_triggers.push_back(trigger);
    return true;
}

void EGE::Event::unbindTrigger(const EGE::Event::Trigger& trigger)
{
    this->_triggers.erase(std::remove(this->_triggers.begin(), this->_triggers.end(), trigger), this->_triggers.end());
}

void EGE::Event::pollEvents()
{
    int keyValue = -1;
    int keyType = -1;
    bool keyPressed = false;
    for (auto &trigger : this->_triggers) {
        keyType = trigger.getMode();
        keyPressed = trigger.isPressed();
        if (trigger.getType() == EGE::Event::Type::Keyboard) {
            keyValue = glfwGetKey(this->_window, trigger.getTrigger());
        } else if (trigger.getType() == EGE::Event::Type::Mouse) {
            if (trigger.getTrigger() != EGE::Event::Mouse::Cursor)
                keyValue = glfwGetMouseButton(this->_window, trigger.getTrigger());
            else
                keyValue = -1;
        } else if (trigger.getType() == EGE::Event::Type::JoystickButton) {
            if (!this->_joystickEnabled || !glfwJoystickPresent(trigger.getJoystickId()))
                continue;
            int count = 0;
            const unsigned char *buttons = glfwGetJoystickButtons(trigger.getJoystickId(), &count);
            if (count < trigger.getTrigger())
                continue;
            keyValue = buttons[trigger.getTrigger()];
        } else if (trigger.getType() == EGE::Event::Type::JoystickAxis) {
            if (!this->_joystickEnabled || !glfwJoystickPresent(trigger.getJoystickId()))
                continue;
            int count = 0;
            const float *axes = glfwGetJoystickAxes(trigger.getJoystickId(), &count);
            if (count < trigger.getTrigger())
                continue;
            trigger.getJoystickAxisCallback()(axes[trigger.getTrigger()]);
            continue;
        } else if (trigger.getType() == EGE::Event::Type::Window) {
            keyValue = -1; /**< Window event are already managed by glfw callback functions */
        } else {
            throw EGE::Event::EventError("Unknown event type");
        }
        if (keyValue == GLFW_PRESS && (!keyPressed || keyType == EGE::Event::Mode::Pressed)) {
            trigger.setPressed(true);
            if (keyType <= EGE::Event::Mode::JustPressed) {
                trigger.getCallback()();
            }
        } else if (keyValue == GLFW_RELEASE && (keyPressed || keyType == EGE::Event::Mode::Released)) {
            trigger.setPressed(false);
            if (keyType >= EGE::Event::Mode::Released) {
                trigger.getCallback()();
            }
        }
    }
}
