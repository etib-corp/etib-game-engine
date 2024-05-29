/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Camera
*/

#include "Camera.hpp"

EGE::Camera::Camera(
    Maths::Vector3<float> position,
    Maths::Vector3<float> up,
    float yaw,
    float pitch
)
    : _position(position),
      _worldUp(up),
      _yaw(yaw),
      _pitch(pitch),
      _front(Maths::Vector3<float>(0.0f, 0.0f, -1.0f)),
      _speed(SPEED),
      _zoom(ZOOM)
{
    updateCameraVectors();
}

EGE::Camera::~Camera()
{
}

EGE::Maths::Matrix<4, 4, double> EGE::Camera::getViewMatrix() const
{
    return EGE::Maths::Matrix<4, 4, double>(glm::lookAt(this->_position.toGlmVec3(), this->_position.toGlmVec3() + this->_front.toGlmVec3(), this->_up.toGlmVec3()));
}

void EGE::Camera::move(Movement direction, float deltaTime)
{
    float velocity = this->_speed * deltaTime;
    if (direction == FORWARD)
        this->_position += this->_front * velocity;
    if (direction == BACKWARD)
        this->_position -= this->_front * velocity;
    if (direction == LEFT)
        this->_position -= this->_right * velocity;
    if (direction == RIGHT)
        this->_position += this->_right * velocity;
    if (direction == DOWN)
        this->_position -= this->_up * velocity;
    if (direction == UP)
        this->_position += this->_up * velocity;
    this->updateCameraVectors();
}

void EGE::Camera::update(EGE::Shader &shader, float aspect)
{
    glm::mat4 projection = glm::perspective(glm::radians(this->getZoom()), aspect, 0.1f, 100.0f);
    glm::mat4 view = this->getViewMatrix().toGlm();
    shader.setMat("projection", EGE::Maths::Matrix<4, 4, float>(projection));
    shader.setMat("view", EGE::Maths::Matrix<4, 4, float>(view));
}

void EGE::Camera::rotate(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= this->_speed / 10.0f;
    yoffset *= this->_speed / 10.0f;

    this->_yaw += xoffset;
    this->_pitch += yoffset;

    if (constrainPitch) {
        if (this->_pitch > 89.0f)
            this->_pitch = 89.0f;
        if (this->_pitch < -89.0f)
            this->_pitch = -89.0f;
    }

    this->updateCameraVectors();
}

void EGE::Camera::zoom(float yoffset)
{
    this->_zoom -= yoffset;
    if (this->_zoom < 1.0f)
        this->_zoom = 1.0f;
    if (this->_zoom > 45.0f)
        this->_zoom = 45.0f;
}

void EGE::Camera::setPosition(Maths::Vector3<float> position)
{
    this->_position = position;
}

void EGE::Camera::setFront(Maths::Vector3<float> front)
{
    this->_front = front;
}

void EGE::Camera::setUp(Maths::Vector3<float> up)
{
    this->_up = up;
}

void EGE::Camera::setRight(Maths::Vector3<float> right)
{
    this->_right = right;
}

void EGE::Camera::setWorldUp(Maths::Vector3<float> worldUp)
{
    this->_worldUp = worldUp;
}

void EGE::Camera::setYaw(float yaw)
{
    this->_yaw = yaw;
}

void EGE::Camera::setPitch(float pitch)
{
    this->_pitch = pitch;
}

void EGE::Camera::setSpeed(float speed)
{
    this->_speed = speed;
}

void EGE::Camera::setZoom(float zoom)
{
    this->_zoom = zoom;
}

EGE::Maths::Vector3<float> EGE::Camera::getPosition() const
{
    return this->_position;
}

EGE::Maths::Vector3<float> EGE::Camera::getFront() const
{
    return this->_front;
}

EGE::Maths::Vector3<float> EGE::Camera::getUp() const
{
    return this->_up;
}

EGE::Maths::Vector3<float> EGE::Camera::getRight() const
{
    return this->_right;
}

EGE::Maths::Vector3<float> EGE::Camera::getWorldUp() const
{
    return this->_worldUp;
}

float EGE::Camera::getYaw() const
{
    return this->_yaw;
}

float EGE::Camera::getPitch() const
{
    return this->_pitch;
}

float EGE::Camera::getSpeed() const
{
    return this->_speed;
}

float EGE::Camera::getZoom() const
{
    return this->_zoom;
}

void EGE::Camera::updateCameraVectors()
{
    Maths::Vector3<float> front;
    front.x = cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
    front.y = sin(glm::radians(this->_pitch));
    front.z = sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
    this->_front = front.normalize();
    this->_right = this->_front.cross(this->_worldUp).normalize();
    this->_up = this->_right.cross(this->_front).normalize();
}