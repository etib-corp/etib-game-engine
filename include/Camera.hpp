/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Camera
*/

#pragma once

// Engine include
#include "OpenGL.hpp"
#include "Maths/Matrix.hpp"
#include "Maths/Vector3.hpp"

// C++ include

namespace EGE {
    /**
     * @class Camera
     * @brief Represents a camera in a 3D scene.
     *
     * The Camera class provides functionality to manipulate and control the position and orientation of a camera in a 3D scene.
     * It also calculates the view matrix used for rendering objects from the perspective of the camera.
     */
    /**
     * @brief The Camera class represents a camera in a 3D space.
     */
    class Camera {
    public:
        constexpr static const float YAW = -90.0f;        ///< Default yaw value
        constexpr static const float PITCH = 0.0f;        ///< Default pitch value
        constexpr static const float SPEED = 2.5f;        ///< Default speed value
        constexpr static const float SENSITIVITY = 0.1f;  ///< Default sensitivity value
        constexpr static const float ZOOM = 45.0f;        ///< Default zoom value

        /**
         * @brief Represents the possible directions in which the camera can move.
         */
        enum Movement {
            FORWARD,        ///< Move the camera forward
            BACKWARD,       ///< Move the camera backward
            LEFT,           ///< Move the camera left
            RIGHT,          ///< Move the camera right
            UP,             ///< Move the camera up
            DOWN            ///< Move the camera down
        };

        /**
         * @brief Constructs a Camera object.
         *
         * @param position The position of the camera in 3D space.
         * @param up The up vector of the camera.
         * @param yaw The yaw angle of the camera.
         * @param pitch The pitch angle of the camera.
         */
        Camera(
            Maths::Vector3<float> position = Maths::Vector3<float>(0.0f, 0.0f, 0.0f),
            Maths::Vector3<float> up = Maths::Vector3<float>(0.0f, 1.0f, 0.0f),
            float yaw = YAW,
            float pitch = PITCH
        );

        /**
         * @brief Destructor for the Camera object.
         */
        ~Camera();

        /**
         * @brief Calculates the view matrix for the camera.
         *
         * @return The view matrix.
         */
        Maths::Matrix<4, 4> getViewMatrix() const;

        /**
         * @brief Moves the camera based on the specified direction.
         *
         * @param direction The direction in which to move the camera.
         * @param deltaTime The time between the last frame and the current frame.
         */
        void move(Movement direction, float deltaTime);

        /**
         * @brief Rotates the camera based on the specified offset values.
         *
         * @param xoffset The offset value for the x-axis.
         * @param yoffset The offset value for the y-axis.
         * @param constrainPitch Whether to constrain the pitch angle.
         */
        void rotate(float xoffset, float yoffset, bool constrainPitch = true);

        /**
         * @brief Zooms the camera based on the specified offset value.
         *
         * @param yoffset The offset value for the y-axis.
         */
        void zoom(float yoffset);

        /**
         * @brief Sets the position of the camera.
         *
         * @param position The new position of the camera.
         */
        void setPosition(Maths::Vector3<float> position);

        /**
         * @brief Sets the front vector of the camera.
         *
         * @param front The new front vector of the camera.
         */
        void setFront(Maths::Vector3<float> front);

        /**
         * @brief Sets the up vector of the camera.
         *
         * @param up The new up vector of the camera.
         */
        void setUp(Maths::Vector3<float> up);

        /**
         * @brief Sets the right vector of the camera.
         *
         * @param right The new right vector of the camera.
         */
        void setRight(Maths::Vector3<float> right);

        /**
         * @brief Sets the world up vector of the camera.
         *
         * @param worldUp The new world up vector of the camera.
         */
        void setWorldUp(Maths::Vector3<float> worldUp);

        /**
         * @brief Sets the yaw angle of the camera.
         *
         * @param yaw The new yaw angle of the camera.
         */
        void setYaw(float yaw);

        /**
         * @brief Sets the pitch angle of the camera.
         *
         * @param pitch The new pitch angle of the camera.
         */
        void setPitch(float pitch);

        /**
         * @brief Sets the speed of the camera.
         *
         * @param speed The new speed of the camera.
         */
        void setSpeed(float speed);

        /**
         * @brief Sets the zoom value of the camera.
         *
         * @param zoom The new zoom value of the camera.
         */
        void setZoom(float zoom);

        /**
         * @brief Gets the position of the camera.
         *
         * @return The position of the camera.
         */
        Maths::Vector3<float> getPosition() const;

        /**
         * @brief Gets the front vector of the camera.
         *
         * @return The front vector of the camera.
         */
        Maths::Vector3<float> getFront() const;

        /**
         * @brief Gets the up vector of the camera.
         *
         * @return The up vector of the camera.
         */
        Maths::Vector3<float> getUp() const;

        /**
         * @brief Gets the right vector of the camera.
         *
         * @return The right vector of the camera.
         */
        Maths::Vector3<float> getRight() const;

        /**
         * @brief Gets the world up vector of the camera.
         *
         * @return The world up vector of the camera.
         */
        Maths::Vector3<float> getWorldUp() const;

        /**
         * @brief Gets the yaw angle of the camera.
         *
         * @return The yaw angle of the camera.
         */
        float getYaw() const;

        /**
         * @brief Gets the pitch angle of the camera.
         *
         * @return The pitch angle of the camera.
         */
        float getPitch() const;

        /**
         * @brief Gets the speed of the camera.
         *
         * @return The speed of the camera.
         */
        float getSpeed() const;

        /**
         * @brief Gets the zoom value of the camera.
         *
         * @return The zoom value of the camera.
         */
        float getZoom() const;

    private:
        /**
         * @brief Updates the camera's vectors based on the yaw and pitch angles.
         */
        void updateCameraVectors();

        Maths::Vector3<float> _position;  ///< The position of the camera
        Maths::Vector3<float> _front;     ///< The front vector of the camera
        Maths::Vector3<float> _up;        ///< The up vector of the camera
        Maths::Vector3<float> _right;     ///< The right vector of the camera
        Maths::Vector3<float> _worldUp;   ///< The world up vector of the camera

        float _yaw;     ///< The yaw angle of the camera
        float _pitch;   ///< The pitch angle of the camera

        float _speed;   ///< The speed of the camera
        float _zoom;    ///< The zoom value of the camera
    };
}