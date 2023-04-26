//
// Created by emilie on 26/04/2023.
//

#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <vector>

class SoundBuffer {
public:
    static SoundBuffer* get();

    ALuint addSoundEffect(const char* filename);
    bool removeSoundEffect(const ALuint& buffer);

private:
    SoundBuffer();
    ~SoundBuffer();

    std::vector<ALuint> p_SoundEffectBuffers;
};



