/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Device
*/

#include "Sound/Device.hpp"

extern "C" size_t encapsulatedStrLen(const char *str)
{
    return strlen(str);
}

extern "C" EGE::Sound::Device::ErrorType InitOpenALDevice(EGE::Sound::Device *myDevice, const char *deviceName = NULL)
{
    ALCdevice *hardwareDevice = alcOpenDevice(deviceName);
    ALCcontext *context = NULL;

    if (!hardwareDevice)
        return EGE::Sound::Device::ErrorType::CAN_NOT_OPEN_DEVICE;
    context = alcCreateContext(hardwareDevice, NULL);
    if (!context)
        return EGE::Sound::Device::ErrorType::CAN_NOT_CREATE_CONTEXT;
    if (!alcMakeContextCurrent(context))
        return EGE::Sound::Device::ErrorType::CAN_NOT_MAKE_CONTEXT_CURRENT;
    myDevice->setOpenALDevice(hardwareDevice);
    myDevice->setOpenALContext(context);
    return EGE::Sound::Device::ErrorType::NO_ERROR;
}

extern "C" void CloseOpenALDevice(EGE::Sound::Device *myDevice)
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(myDevice->getOpenALContext());
    alcCloseDevice(myDevice->getOpenALMainDevice());
}

EGE::Sound::Device::Device()
{
    switch (InitOpenALDevice(this)) {
        case EGE::Sound::Device::ErrorType::CAN_NOT_OPEN_DEVICE:
            throw EGE::Sound::Device::SoundDeviceError("Can not open device (default)");
            break;
        case EGE::Sound::Device::ErrorType::CAN_NOT_CREATE_CONTEXT:
            throw EGE::Sound::Device::SoundDeviceError("Can not create context");
            break;
        case EGE::Sound::Device::ErrorType::CAN_NOT_MAKE_CONTEXT_CURRENT:
            throw EGE::Sound::Device::SoundDeviceError("Can not make context current");
            break;
        default:
            break;
    }
    refreshDevices();
}

EGE::Sound::Device::~Device()
{
    CloseOpenALDevice(this);
}

ALCdevice *EGE::Sound::Device::getOpenALMainDevice()
{
    return this->_openALMainDevice;
}

void EGE::Sound::Device::setOpenALDevice(ALCdevice *openALDevice)
{
    this->_openALMainDevice = openALDevice;
}

ALCcontext *EGE::Sound::Device::getOpenALContext()
{
    return this->_openALMainContext;
}

void EGE::Sound::Device::setOpenALContext(ALCcontext *openALContext)
{
    this->_openALMainContext = openALContext;
}

void EGE::Sound::Device::refreshDevices()
{
    this->_devices.clear();

    const ALCchar *deviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

    if (!deviceList)
        return;
    while (encapsulatedStrLen(deviceList) > 0) {
        this->_devices.push_back(deviceList);
        deviceList += encapsulatedStrLen(deviceList) + 1;
    }
}

std::vector<std::string> EGE::Sound::Device::getDevices()
{
    return this->_devices;
}
