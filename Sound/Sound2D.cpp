#include "Sound2D.h"

void Sound2D::play()
{
    if (this->pSoundSample == 0 || this->pSoundSample->getFMODSoundSample() == 0)
        return;

    // Sound is now playing so set flag

//        this->playingFlag = true;
    // Play the sound
    this->channel = FSOUND_PlaySound(this->channel, this->pSoundSample->getFMODSoundSample());
//        // Reserve the channel the sound is playing on
//        FSOUND_SetReserved(this->channel, true);
    // Set Paused (if the sound has been paused)
    FSOUND_SetPaused(this->channel, this->pausedFlag);
    // Set if playback should loop or not
    FSOUND_SetLoopMode(this->channel, ((this->loopFlag == true) ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF));
    // Set if the Sound should be muted or not
    FSOUND_SetMute(this->channel, this->muteFlag);
    // Set the speak balance
    FSOUND_SetPan(this->channel, this->pan);
    // Set the volume
    FSOUND_SetVolume(this->channel, this->volume);
    // Set the absolute volume
    FSOUND_SetVolumeAbsolute(this->channel, this->absoluteVolume);
    // Set surround
    FSOUND_SetSurround(this->channel, this->surroundFlag);
    // Set priority
    FSOUND_SetPriority(this->channel, this->priority);
    // Set Position and velocity
    float position[3] = {this->x, this->y, 0.0f};
    float velocity[3] = {this->xVelocity, this->yVelocity, 0.0f};
    FSOUND_3D_SetAttributes(this->channel, position, velocity);
    // Set MinMaxDistance
    FSOUND_3D_SetMinMaxDistance(this->channel, this->minDistance, this->maxDistance);
    /* A nasty hack to compensate for FMODs lack of a global mute function for the audio system */
    if (FMODGlobals::muteFlag == true)
    {
        // Brute force mute
        FSOUND_SetMute(this->channel, true);
    }
}

void Sound2D::playEx()
{
    if (this->pSoundSample == 0 || this->pSoundSample->getFMODSoundSample() == 0)
        return;

    // Play the sound paused
    this->channel = FSOUND_PlaySoundEx(this->channel, this->pSoundSample->getFMODSoundSample(), 0, true);
    // Reserve the channel the sound is playing on
    FSOUND_SetReserved(this->channel, true);
//        // Sound is now playing so set flag
//        this->playingFlag = true;
    // Sound is paused so set flag
    this->pausedFlag = true;
    // Set if playback should loop or not
    FSOUND_SetLoopMode(this->channel, ((this->loopFlag == true) ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF));
    // Set if the Sound should be muted or not
    FSOUND_SetMute(this->channel, this->muteFlag);
//        /* A nasty hack to compensate for FMODs lack of a global mute function for the audio system */
//        if (FMODGlobals::muteFlag == true)
//        {
//            // Brute force mute
//            FSOUND_SetMute(this->channel, true);
//        }
    // Set the speak balance
    FSOUND_SetPan(this->channel, this->pan);
    // Set the volume
    FSOUND_SetVolume(this->channel, this->volume);
    // Set the absolute volume
    FSOUND_SetVolumeAbsolute(this->channel, this->absoluteVolume);
    // Set surround
    FSOUND_SetSurround(this->channel, this->surroundFlag);
    // Set priority
    FSOUND_SetPriority(this->channel, this->priority);
    // Set Position and velocity
    float position[3] = {this->x, this->y, 0.0f};
    float velocity[3] = {this->xVelocity, this->yVelocity, 0.0f};
    FSOUND_3D_SetAttributes(this->channel, position, velocity);
    // Set MinMaxDistance
    FSOUND_3D_SetMinMaxDistance(this->channel, this->minDistance, this->maxDistance);
}

float Sound2D::getX()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return position[0];
    return this->x;
}

float Sound2D::getY()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return position[1];
    return this->y;
}

void Sound2D::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
    float position[3] = {x, y, 0.0f};
    float velocity[3] = {this->getXVelocity(), this->getYVelocity(), 0.0f};
    FSOUND_3D_SetAttributes(this->channel, position, velocity);
}

float Sound2D::getXVelocity()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return velocity[0];
    return this->xVelocity;
}

float Sound2D::getYVelocity()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return velocity[1];
    return this->yVelocity;
}

void Sound2D::setVelocity(float xVelocity, float yVelocity)
{
            this->xVelocity = xVelocity;
            this->yVelocity = yVelocity;
            float position[3] = {this->x, this->y, 0.0f};
            float velocity[3] = {this->xVelocity, this->yVelocity, 0.0f};
            FSOUND_3D_SetAttributes(this->channel, position, velocity);
}

float Sound2D::getMinDistance()
{
    // OLD CODE
    //float min = 0.0f;
    //float max = 0.0f;
    //FSOUND_3D_GetMinMaxDistance(this->channel, &min, &max);
    //return min;
    return this->minDistance;
}

float Sound2D::getMaxDistance()
{
    // OLD CODE
    //float min = 0.0f;
    //float max = 0.0f;
    //FSOUND_3D_GetMinMaxDistance(this->channel, &min, &max);
    //return max;
    return this->maxDistance;
}

void Sound2D::setMinDistance(float minDistance)
{
    this->minDistance = minDistance;
    FSOUND_3D_SetMinMaxDistance(this->channel, this->minDistance, this->maxDistance);
}

void Sound2D::setMaxDistance(float maxDistance)
{
    this->maxDistance = maxDistance;
    FSOUND_3D_SetMinMaxDistance(this->channel, this->minDistance, this->maxDistance);
}

void Sound2D::setMinMaxDistance(float minDistance, float maxDistance)
{
    this->minDistance = minDistance;
    this->maxDistance = maxDistance;
    FSOUND_3D_SetMinMaxDistance(this->channel, this->minDistance, this->maxDistance);
}

void Sound2D::bindToLua(lua_State* pLuaState)
{
    // TODO: More bindings
    // TODO: Not all functions are bound, double check and abound accordingly
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        luabind::class_<Sound2D>("Sound2D")
        .def(luabind::constructor<>())
        .def("play", (void(Sound2D::*)()) &Sound2D::play)
        .def("playEx", (void(Sound2D::*)()) &Sound2D::playEx)
        .def("stop", (void(Sound2D::*)()) &Sound2D::stop)
//        .def("setFrequency", (void(Sound2D::*)(int)) &Sound2D::setFrequency)
//        .def("setLoop", (void(Sound2D::*)(bool)) &Sound2D::setLoop)
//        .def("setMute", (void(Sound2D::*)(bool)) &Sound2D::setMute)
//        .def("setPan", (void(Sound2D::*)(int)) &Sound2D::setPan)
//        .def("setPaused", (void(Sound2D::*)(bool)) &Sound2D::setPaused)
//        .def("setPriority", (void(Sound2D::*)(int)) &Sound2D::setPriority)
//        .def("setReserved", (void(Sound2D::*)(bool)) &Sound2D::setReserved)
//        .def("setSurround", (void(Sound2D::*)(bool)) &Sound2D::setSurround)
//        .def("setVolume", (void(Sound2D::*)(int)) &Sound2D::setVolume)
//        .def("setVolumeAbsolute", (void(Sound2D::*)(int)) &Sound2D::setVolumeAbsolute)
//        .def("getVolume", (int(Sound2D::*)()) &Sound2D::getVolume)
//        .def("getAmplitude", (int(Sound2D::*)()) &Sound2D::getAmplitude)
//        .def("setCurrentPosition", (void(Sound2D::*)(unsigned int)) &Sound2D::setCurrentPosition)
//        .def("getCurrentPosition", (unsigned int(Sound2D::*)()) &Sound2D::getCurrentPosition)
//        .def("isLoop", (bool(Sound2D::*)()) &Sound2D::isLoop)
//        .def("isMute", (bool(Sound2D::*)()) &Sound2D::isMute)
//        .def("getSubChannelCount", (int(Sound2D::*)()) &Sound2D::getSubChannelCount)
//        .def("getPan", (int(Sound2D::*)()) &Sound2D::getPan)
//        .def("isPaused", (bool(Sound2D::*)()) &Sound2D::isPaused)
//        .def("setPaused", (void(Sound2D::*)(bool)) &Sound2D::setPaused)
//        .def("pause", (void(Sound2D::*)()) &Sound2D::pause)
//        .def("resume", (void(Sound2D::*)()) &Sound2D::resume)
//        .def("getPriority", (int(Sound2D::*)()) &Sound2D::getPriority)
//        .def("getReserved", (bool(Sound2D::*)()) &Sound2D::getReserved)
//        .def("getSurround", (bool(Sound2D::*)()) &Sound2D::getSurround)
//        .def("isPlaying", (bool(Sound2D::*)()) &Sound2D::isPlaying)
//        .def("getX", (float(Sound2D::*)()) &Sound2D::getX)
//        .def("getY", (float(Sound2D::*)()) &Sound2D::getY)
//        .def("setPosition", (float(Sound2D::*)(float, float)) &Sound2D::setPosition)
//        .def("getXVelocity", (float(Sound2D::*)()) &Sound2D::getXVelocity)
//        .def("getYVelocity", (float(Sound2D::*)()) &Sound2D::getYVelocity)
//        .def("setVelocity", (float(Sound2D::*)(float, float)) &Sound2D::setVelocity)
//        .def("setMinMaxDistance", (float(Sound2D::*)(float, float)) &Sound2D::setMinMaxDistance)
//        .def("getMinDistance", (float(Sound2D::*)()) &Sound2D::getMinDistance)
//        .def("getMaxDistance", (float(Sound2D::*)()) &Sound2D::getMaxDistance)
    ];
}

