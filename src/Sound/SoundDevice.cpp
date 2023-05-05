#include "SoundDevice.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

SoundDevice* SoundDevice::get()
{
    static  SoundDevice* snd_device = new SoundDevice();
    return snd_device;
}

SoundDevice::SoundDevice()
{
    p_ALCDevice = alcOpenDevice(nullptr); //nullptr : will get the default device
    if (!p_ALCDevice)
    {
        std::cout << "OpenAL: failed to get sound device" << std::endl;
        return;
    }

    p_ALCContext = alcCreateContext(p_ALCDevice, nullptr); //create context
    if (!p_ALCContext)
    {
        std::cout << "OpenAL: failed to create context" << std::endl;
        return;
    }

    if (!alcMakeContextCurrent(p_ALCContext)) //make context current
    {
        std::cout << "OpenAL: failed to make context current" << std::endl;
        return;
    }

    const ALCchar* name = nullptr;
    if (alcIsExtensionPresent(p_ALCDevice,"ALC_ENUMERATE_ALL_EXT"))
        name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
    if (!name || alcGetError(p_ALCDevice) != AL_NO_ERROR)
        name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);

    std::cout << "OpenAL: opened device " << name << std::endl;
}

SoundDevice::~SoundDevice()
{
    if (!alcMakeContextCurrent(nullptr)) {
        std::cout << "OpenAL: failed to unset context" << std::endl;
        return;
    }

    alcDestroyContext(p_ALCContext);
    if (p_ALCContext)
    {
        std::cout << "OpenAL: failed to destroy context" << std::endl;
        return;
    }

    if (!alcCloseDevice(p_ALCDevice))
    {
        std::cout << "OpenAL: failed to close sound device" << std::endl;
        return;
    }
}