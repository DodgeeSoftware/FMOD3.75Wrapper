#include "Sound3D.h"

void Sound3D::play()
{
    if (this->pSoundSample == 0 || this->pSoundSample->getFMODSoundSample() == 0)
        return;

//        // Sound is now playing so set flag
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
    float position[3] = {this->x, this->y, this->z};
    float velocity[3] = {this->xVelocity, this->yVelocity, this->zVelocity};
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

void Sound3D::playEx()
{
    if (this->pSoundSample == 0 || this->pSoundSample->getFMODSoundSample() == 0)
        return;

    // Play the sound paused
    this->channel = FSOUND_PlaySoundEx(this->channel, this->pSoundSample->getFMODSoundSample(), 0, true);
//        // Reserve the channel the sound is playing on
//        FSOUND_SetReserved(this->channel, true);
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
    float position[3] = {this->x, this->y, this->z};
    float velocity[3] = {this->xVelocity, this->yVelocity, this->zVelocity};
    FSOUND_3D_SetAttributes(this->channel, position, velocity);
    // Set MinMaxDistance
    FSOUND_3D_SetMinMaxDistance(this->channel, this->minDistance, this->maxDistance);
}

float Sound3D::getX()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return position[0];
    return this->x;
}

float Sound3D::getY()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return position[1];
    return this->y;
}

float Sound3D::getZ()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return position[2];
    return this->z;
}

void Sound3D::setPosition(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    float position[3] = {this->x, this->y, this->z};
    float velocity[3] = {this->xVelocity, this->yVelocity, this->zVelocity};
    FSOUND_3D_SetAttributes(this->channel, position, velocity);
}

float Sound3D::getXVelocity()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return velocity[0];
    return this->xVelocity;
}

float Sound3D::getYVelocity()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return velocity[1];
    return this->yVelocity;
}

float Sound3D::getZVelocity()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return velocity[2];
    return this->zVelocity;
}

void Sound3D::setVelocity(float xVelocity, float yVelocity, float zVelocity)
{
    this->xVelocity = xVelocity;
    this->yVelocity = yVelocity;
    this->zVelocity = zVelocity;
    float position[3] = {this->x, this->y, this->z};
    float velocity[3] = {this->xVelocity, this->yVelocity, this->zVelocity};
    FSOUND_3D_SetAttributes(this->channel, position, velocity);
}

float Sound3D::getMinDistance()
{
    // OLD CODE
    //float min = 0.0f;
    //float max = 0.0f;
    //FSOUND_3D_GetMinMaxDistance(this->channel, &min, &max);
    //return min;
    return this->minDistance;
}

float Sound3D::getMaxDistance()
{
    // OLD CODE
    //float min = 0.0f;
    //float max = 0.0f;
    //FSOUND_3D_GetMinMaxDistance(this->channel, &min, &max);
    //return max;
    return this->maxDistance;
}

void Sound3D::setMinMaxDistance(float minDistance, float maxDistance)
{
    this->minDistance = minDistance;
    this->maxDistance = maxDistance;
    FSOUND_3D_SetMinMaxDistance(this->channel, this->minDistance, this->maxDistance);
}

void Sound3D::bindToLua(lua_State* pLuaState)
{
    // TODO: More bindings
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        luabind::class_<Sound3D>("Sound3D")
        .def(luabind::constructor<>())
        .def("play", (void(Sound3D::*)()) &Sound3D::play)
        .def("playEx", (void(Sound3D::*)()) &Sound3D::playEx)
        .def("stop", (void(Sound3D::*)()) &Sound3D::stop)
//        .def("setFrequency", (void(Sound3D::*)(int)) &Sound3D::setFrequency)
//        .def("setLoop", (void(Sound3D::*)(bool)) &Sound3D::setLoop)
//        .def("setMute", (void(Sound3D::*)(bool)) &Sound3D::setMute)
//        .def("setPan", (void(Sound3D::*)(int)) &Sound3D::setPan)
//        .def("setPaused", (void(Sound3D::*)(bool)) &Sound3D::setPaused)
//        .def("setPriority", (void(Sound3D::*)(int)) &Sound3D::setPriority)
//        .def("setReserved", (void(Sound3D::*)(bool)) &Sound3D::setReserved)
//        .def("setSurround", (void(Sound3D::*)(bool)) &Sound3D::setSurround)
//        .def("setVolume", (void(Sound3D::*)(int)) &Sound3D::setVolume)
//        .def("setVolumeAbsolute", (void(Sound3D::*)(int)) &Sound3D::setVolumeAbsolute)
//        .def("getVolume", (int(Sound3D::*)()) &Sound3D::getVolume)
//        .def("getAmplitude", (int(Sound3D::*)()) &Sound3D::getAmplitude)
//        .def("setCurrentPosition", (void(Sound3D::*)(unsigned int)) &Sound3D::setCurrentPosition)
//        .def("getCurrentPosition", (unsigned int(Sound3D::*)()) &Sound3D::getCurrentPosition)
//        .def("isLoop", (bool(Sound3D::*)()) &Sound3D::isLoop)
//        .def("isMute", (bool(Sound3D::*)()) &Sound3D::isMute)
//        .def("getSubChannelCount", (int(Sound3D::*)()) &Sound3D::getSubChannelCount)
//        .def("getPan", (int(Sound3D::*)()) &Sound3D::getPan)
//        .def("isPaused", (bool(Sound3D::*)()) &Sound3D::isPaused)
//        .def("setPaused", (void(Sound3D::*)(bool)) &Sound3D::setPaused)
//        .def("pause", (void(Sound3D::*)()) &Sound3D::pause)
//        .def("resume", (void(Sound3D::*)()) &Sound3D::resume)
//        .def("getPriority", (int(Sound3D::*)()) &Sound3D::getPriority)
//        .def("getReserved", (bool(Sound3D::*)()) &Sound3D::getReserved)
//        .def("getSurround", (bool(Sound3D::*)()) &Sound3D::getSurround)
//        .def("isPlaying", (bool(Sound3D::*)()) &Sound3D::isPlaying)
//        .def("getX", (float(Sound3D::*)()) &Sound3D::getX)
//        .def("getY", (float(Sound3D::*)()) &Sound3D::getY)
//        .def("setPosition", (float(Sound3D::*)(float, float)) &Sound3D::setPosition)
//        .def("getXVelocity", (float(Sound3D::*)()) &Sound3D::getXVelocity)
//        .def("getYVelocity", (float(Sound3D::*)()) &Sound3D::getYVelocity)
//        .def("setVelocity", (float(Sound3D::*)(float, float)) &Sound3D::setVelocity)
//        .def("setMinMaxDistance", (float(Sound3D::*)(float, float)) &Sound3D::setMinMaxDistance)
//        .def("getMinDistance", (float(Sound3D::*)()) &Sound3D::getMinDistance)
//        .def("getMaxDistance", (float(Sound3D::*)()) &Sound3D::getMaxDistance)
    ];
}
