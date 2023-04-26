//
// Created by emilie on 26/04/2023.
//

#pragma once //we won't use multiple soundDevice
#include <AL/al.h>
#include <AL/alc.h>

class SoundDevice {
public:
    static SoundDevice* get();

private:
    SoundDevice();
    ~SoundDevice();

    ALCdevice* p_ALCDevice;
    ALCcontext* p_ALCContext;
};



