//
// Created by emilie on 26/04/2023.
//
#pragma once
#include <AL/al.h>

class SoundSource {
public:
    SoundSource();
    ~SoundSource();

    void Play(const ALuint buffer_to_play);

private:
    ALuint p_Source;
    float p_Pitch = 1.f;
    float p_Gain = 1.f;
    float p_Position[3] = { 0,0,0 }; //default sound comming from everywhere
    float p_Velocity[3] = { 0,0,0 }; //no need for effects
    bool p_LoopSound = false;
    ALuint p_Buffer = 0;
};



