/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Movement
*/

#pragma once

// Engine include
#include "Model.hpp"

// C++ include
#include <chrono>
#include <memory>

namespace EGE {
    /**
     * @brief The Movement class represents a movement animation.
     */
    class Movement {
        public:
            /**
             * @brief The MovementError class represents an error that can occur during movement.
             */
            class MovementError : public EGE::Error {
                public:
                    /**
                     * @brief Constructs a MovementError object with the given error message.
                     * @param message The error message.
                     */
                    MovementError(const std::string& message) : EGE::Error(message) {}
            };

            /**
             * @brief Constructs a Movement object with the specified duration and loop flag.
             * @param duration The duration of the movement animation in milliseconds.
             * @param loop Flag indicating whether the movement animation should loop.
             */
            Movement(int duration = 1000, bool loop = false);

            /**
             * @brief Destroys the Movement object.
             */
            ~Movement();

            /**
             * @brief Moves the animation by the specified delta time.
             * @param deltaTime The time elapsed since the last frame in seconds.
             */
            void move(float deltaTime);

            /**
             * @brief Adds a model to the movement animation.
             * @param name The name of the model.
             * @param model The shared pointer to the model object.
             * @return A reference to the Movement object.
             */
            EGE::Movement& addModel(const std::string &name, const std::shared_ptr<EGE::Model>& model);

            /**
             * @brief Removes a model from the movement animation.
             * @param name The name of the model to remove.
             * @return A reference to the Movement object.
             */
            EGE::Movement& removeModel(const std::string &name);

            /**
             * @brief Checks if a model with the specified name exists in the movement animation.
             * @param name The name of the model.
             * @return True if the model exists, false otherwise.
             */
            bool hasModel(const std::string &name) const;

            /**
             * @brief Gets the number of models in the movement animation.
             * @return The number of models.
             */
            int getModelsCount() const;

            /**
             * @brief Gets the names of all the models in the movement animation.
             * @return A vector of model names.
             */
            std::vector<std::string> getModelsNames() const;

            /**
             * @brief Gets a map of all the models in the movement animation.
             * @return A map of model names to model objects.
             */
            std::map<std::string, std::shared_ptr<EGE::Model>> getModels() const;

            /**
             * @brief Sets the key frames for the movement animation.
             * @param keyFrames The vector of key frames.
             */
            void setKeyFrames(const std::vector<EGE::Maths::Matrix<4, 4, float>> &keyFrames);

            /**
             * @brief Gets the key frames of the movement animation.
             * @return The vector of key frames.
             */
            std::vector<EGE::Maths::Matrix<4, 4, float>> getKeyFrames() const;

            /**
             * @brief Sets the current key frame index.
             * @param keyFrame The index of the current key frame.
             */
            void setCurrentKeyFrame(int keyFrame);

            /**
             * @brief Gets the current key frame index.
             * @return The index of the current key frame.
             */
            int getCurrentKeyFrame() const;

            /**
             * @brief Sets the duration of the movement animation.
             * @param duration The duration of the movement animation in milliseconds.
             */
            void setDuration(int duration);

            /**
             * @brief Gets the duration of the movement animation.
             * @return The duration of the movement animation in milliseconds.
             */
            int getDuration() const;

            /**
             * @brief Adds a key frame to the front of the key frames vector.
             * @param keyFrame The key frame to add.
             * @return A reference to the Movement object.
             */
            EGE::Movement& pushFrontKeyFrame(const EGE::Maths::Matrix<4, 4, float> &keyFrame);

            /**
             * @brief Adds a key frame to the back of the key frames vector.
             * @param keyFrame The key frame to add.
             * @return A reference to the Movement object.
             */
            EGE::Movement& pushBackKeyFrame(const EGE::Maths::Matrix<4, 4, float> &keyFrame);

            /**
             * @brief Inserts a key frame at the specified index in the key frames vector.
             * @param ind The index at which to insert the key frame.
             * @param keyFrame The key frame to insert.
             */
            void insertKeyFrame(int ind, const EGE::Maths::Matrix<4, 4, float> &keyFrame);

            /**
             * @brief Replaces the key frame at the specified index in the key frames vector.
             * @param ind The index of the key frame to replace.
             * @param keyFrame The new key frame.
             */
            void replaceKeyFrame(int ind, const EGE::Maths::Matrix<4, 4, float> &keyFrame);

            /**
             * @brief Removes the key frame at the specified index from the key frames vector.
             * @param ind The index of the key frame to remove.
             */
            EGE::Movement& removeKeyFrame(int ind);

            /**
             * @brief Gets the rotation vector from a key frame matrix.
             * @param keyFrame The key frame matrix.
             * @return The rotation vector.
             */
            inline EGE::Maths::Vector3<float> getRotation(const EGE::Maths::Matrix<4, 4, float>& keyFrame) const
            {
                return EGE::Maths::Vector3<float>(keyFrame[0][0], keyFrame[1][0], keyFrame[2][0]);
            }

            /**
             * @brief Gets the scale vector from a key frame matrix.
             * @param keyFrame The key frame matrix.
             * @return The scale vector.
             */
            inline EGE::Maths::Vector3<float> getScale(const EGE::Maths::Matrix<4, 4, float>& keyFrame) const
            {
                return EGE::Maths::Vector3<float>(keyFrame[0][1], keyFrame[1][1], keyFrame[2][1]);
            }

            /**
             * @brief Gets the shear vector from a key frame matrix.
             * @param keyFrame The key frame matrix.
             * @return The shear vector.
             */
            inline EGE::Maths::Vector3<float> getShear(const EGE::Maths::Matrix<4, 4, float>& keyFrame) const
            {
                return EGE::Maths::Vector3<float>(keyFrame[0][2], keyFrame[1][2], keyFrame[2][2]);
            }

            /**
             * @brief Gets the translation vector from a key frame matrix.
             * @param keyFrame The key frame matrix.
             * @return The translation vector.
             */
            inline EGE::Maths::Vector3<float> getTranslation(const EGE::Maths::Matrix<4, 4, float>& keyFrame) const
            {
                return EGE::Maths::Vector3<float>(keyFrame[0][3], keyFrame[1][3], keyFrame[2][3]);
            }

        protected:
            std::vector<EGE::Maths::Matrix<4, 4, float>> _keyFrames; /**< The key frames of the movement animation. */
            int _currentKeyFrame; /**< The index of the current key frame. */
            int _lastKeyFrame; /**< The index of the last key frame. */
            std::map<std::string, std::shared_ptr<EGE::Model>> _models; /**< The models in the movement animation. */
            int _duration; /**< The duration of the movement animation in milliseconds. */
            int _durationPerKeyFrame; /**< The duration per key frame in milliseconds. */
            std::chrono::high_resolution_clock _clock; /**< The high resolution clock used for timing. */
            std::chrono::high_resolution_clock::time_point _lastTime; /**< The time point of the last frame. */
            bool _loop; /**< Flag indicating whether the movement animation should loop. */
    };
}