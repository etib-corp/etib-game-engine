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
    class Movement {
        public:
            class MovementError : public EGE::Error {
                public:
                    MovementError(const std::string& message) : EGE::Error(message) {}
            };
            Movement(int duration = 1000, bool loop = false);
            ~Movement();

            void move(float deltaTime);

            EGE::Movement& addModel(const std::string &name, const std::shared_ptr<EGE::Model>& model);
            EGE::Movement& removeModel(const std::string &name);

            bool hasModel(const std::string &name) const;
            int getModelsCount() const;
            std::vector<std::string> getModelsNames() const;
            std::map<std::string, std::shared_ptr<EGE::Model>> getModels() const;

            void setKeyFrames(const std::vector<EGE::Maths::Matrix<4, 4, float>> &keyFrames);
            std::vector<EGE::Maths::Matrix<4, 4, float>> getKeyFrames() const;

            void setCurrentKeyFrame(int keyFrame);
            int getCurrentKeyFrame() const;
            void setDuration(int duration);
            int getDuration() const;

            EGE::Movement& pushFrontKeyFrame(const EGE::Maths::Matrix<4, 4, float> &keyFrame);
            EGE::Movement& pushBackKeyFrame(const EGE::Maths::Matrix<4, 4, float> &keyFrame);
            void insertKeyFrame(int ind, const EGE::Maths::Matrix<4, 4, float> &keyFrame);
            void replaceKeyFrame(int ind, const EGE::Maths::Matrix<4, 4, float> &keyFrame);
            EGE::Movement& removeKeyFrame(int ind);

            inline EGE::Maths::Vector3<float> getRotation(const EGE::Maths::Matrix<4, 4, float>& keyFrame) const
            {
                return EGE::Maths::Vector3<float>(keyFrame[0][0], keyFrame[1][0], keyFrame[2][0]);
            }

            inline EGE::Maths::Vector3<float> getScale(const EGE::Maths::Matrix<4, 4, float>& keyFrame) const
            {
                return EGE::Maths::Vector3<float>(keyFrame[0][1], keyFrame[1][1], keyFrame[2][1]);
            }

            inline EGE::Maths::Vector3<float> getShear(const EGE::Maths::Matrix<4, 4, float>& keyFrame) const
            {
                return EGE::Maths::Vector3<float>(keyFrame[0][2], keyFrame[1][2], keyFrame[2][2]);
            }

            inline EGE::Maths::Vector3<float> getTranslation(const EGE::Maths::Matrix<4, 4, float>& keyFrame) const
            {
                return EGE::Maths::Vector3<float>(keyFrame[0][3], keyFrame[1][3], keyFrame[2][3]);
            }

        protected:
            std::vector<EGE::Maths::Matrix<4, 4, float>> _keyFrames;
            int _currentKeyFrame;
            int _lastKeyFrame;
            std::map<std::string, std::shared_ptr<EGE::Model>> _models;
            int _duration;
            int _durationPerKeyFrame;
            std::chrono::high_resolution_clock _clock;
            std::chrono::high_resolution_clock::time_point _lastTime;
            bool _loop;
    };
}