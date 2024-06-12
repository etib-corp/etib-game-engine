/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Movement
*/

#include "Movement.hpp"

EGE::Movement::Movement(int duration, bool loop)
{
    this->_currentKeyFrame = 0;
    this->_lastKeyFrame = 0;
    this->_duration = duration;
    this->_durationPerKeyFrame = this->_duration;
    this->_clock = std::chrono::high_resolution_clock();
    this->_lastTime = this->_clock.now();
    this->_loop = loop;
}

EGE::Movement::~Movement()
{
}

void EGE::Movement::move(float deltaTime)
{
    float ratio = (deltaTime * 1000.0) / this->_durationPerKeyFrame;
    for (auto &[name, model] : _models) {
        model->setPosition(model->getPosition() + this->getTranslation(this->_keyFrames[_currentKeyFrame]) * ratio);
        model->setRotation(model->getRotation() + this->getRotation(this->_keyFrames[_currentKeyFrame] * ratio));
        model->setScale(model->getScale() + this->getScale(this->_keyFrames[_currentKeyFrame] * ratio));
        model->setShear(model->getShear() + this->getShear(this->_keyFrames[_currentKeyFrame] * ratio));
    }
    if (this->_clock.now() - this->_lastTime >= std::chrono::milliseconds(this->_durationPerKeyFrame)) {
        this->_currentKeyFrame = (this->_currentKeyFrame + 1) % this->_keyFrames.size();
        this->_lastTime = this->_clock.now();
        if (this->_loop && this->_currentKeyFrame == 0) {
            for (auto &[name, model] : _models) {
                EGE::Maths::Matrix<4, 4, float> originalModelMatrix = model->getOriginalModelMatrix();
                model->setPosition(this->getTranslation(originalModelMatrix));
                model->setRotation(this->getRotation(originalModelMatrix));
                model->setScale(this->getScale(originalModelMatrix));
                model->setShear(this->getShear(originalModelMatrix));
            }
        }
    }
}

EGE::Movement &EGE::Movement::addModel(const std::string &name, const std::shared_ptr<EGE::Model> &model)
{
    this->_models[name] = model;
    return *this;
}
EGE::Movement& EGE::Movement::removeModel(const std::string &name)
{
    this->_models.erase(name);
    return *this;
}

bool EGE::Movement::hasModel(const std::string &name) const
{
    return this->_models.find(name) != this->_models.end();
}

int EGE::Movement::getModelsCount() const
{
    return this->_models.size();
}

std::vector<std::string> EGE::Movement::getModelsNames() const
{
    std::vector<std::string> names;
    for (auto &[name, model] : this->_models) {
        names.push_back(name);
    }
    return names;
}

std::map<std::string, std::shared_ptr<EGE::Model>> EGE::Movement::getModels() const
{
    return this->_models;
}

void EGE::Movement::setKeyFrames(const std::vector<EGE::Maths::Matrix<4, 4, float>> &keyFrames)
{
    this->_keyFrames = keyFrames;
    this->_durationPerKeyFrame = this->_duration / this->_keyFrames.size();
}

std::vector<EGE::Maths::Matrix<4, 4, float>> EGE::Movement::getKeyFrames() const
{
    return this->_keyFrames;
}

void EGE::Movement::setCurrentKeyFrame(int keyFrame)
{
    this->_currentKeyFrame = keyFrame;
}

int EGE::Movement::getCurrentKeyFrame() const
{
    return this->_currentKeyFrame;
}

void EGE::Movement::setDuration(int duration)
{
    this->_duration = duration;
    this->_durationPerKeyFrame = duration / (this->_keyFrames.size() == 0 ? 1 : this->_keyFrames.size());
}

int EGE::Movement::getDuration() const
{
    return this->_duration;
}

EGE::Movement& EGE::Movement::pushFrontKeyFrame(const EGE::Maths::Matrix<4, 4, float> &keyFrame)
{
    this->_keyFrames.insert(this->_keyFrames.begin(), keyFrame);
    this->_durationPerKeyFrame = this->_duration / this->_keyFrames.size();
    return *this;
}

EGE::Movement& EGE::Movement::pushBackKeyFrame(const EGE::Maths::Matrix<4, 4, float> &keyFrame)
{
    this->_keyFrames.push_back(keyFrame);
    this->_durationPerKeyFrame = this->_duration / this->_keyFrames.size();
    return *this;
}

void EGE::Movement::insertKeyFrame(int ind, const EGE::Maths::Matrix<4, 4, float> &keyFrame)
{
    this->_keyFrames.insert(this->_keyFrames.begin() + ind, keyFrame);
    this->_durationPerKeyFrame = this->_duration / this->_keyFrames.size();
}

void EGE::Movement::replaceKeyFrame(int ind, const EGE::Maths::Matrix<4, 4, float> &keyFrame)
{
    this->_keyFrames[ind] = keyFrame;
}

EGE::Movement& EGE::Movement::removeKeyFrame(int ind)
{
    this->_keyFrames.erase(this->_keyFrames.begin() + ind);
    this->_durationPerKeyFrame = this->_duration / this->_keyFrames.size();
    return *this;
}
