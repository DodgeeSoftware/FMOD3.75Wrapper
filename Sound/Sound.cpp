#include "Sound.h"

void Sound::think()
{
    // TODO: implement me
}

void Sound::update(float dTime)
{
    // NOTE: Implement this function if we need it
}

void Sound::clear()
{
//    this->playingFlag = false;
    this->pausedFlag = false;
    this->loopFlag = false;
    this->muteFlag = false;
    this->pan = 128;
    this->volume = 255;
    this->absoluteVolume = 255;
    this->surroundFlag = false;
    this->priority = 0;
    //this->reserved = false;
    if (this->channel != FSOUND_FREE)
        FSOUND_SetReserved(this->channel, false);
    this->pSoundSample = 0;
    this->channel = FSOUND_FREE;
    this->filename.clear();
    this->name.clear();
}

void Sound::free()
{
    // TODO: Implement me
}

void Sound::play()
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
    /* A nasty hack to compensate for FMODs lack of a global mute function for the audio system */
    if (FMODGlobals::muteFlag == true)
    {
        // Brute force mute
        FSOUND_SetMute(this->channel, true);
    }
}

void Sound::playEx()
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
    /* A nasty hack to compensate for FMODs lack of a global mute function for the audio system */
    if (FMODGlobals::muteFlag == true)
    {
        // Brute force mute
        FSOUND_SetMute(this->channel, true);
    }
}

void Sound::start()
{
    // Play the sound
    this->play();
}

void Sound::stop()
{
//            // Sound is no longer playing so set flag
//            this->playingFlag = false;
    // Sound is no longer paused so set flag
    this->pausedFlag = false;
    // Unreserve the Channel
    if (FSOUND_GetReserved(this->channel) == true)
        FSOUND_SetReserved(this->channel, false);
    // If channel isn't playing then return
    if (FSOUND_IsPlaying(this->channel) == true)
    {
        // Stop the channel from playing
        FSOUND_StopSound(this->channel);
    }
    // Reset channel id
    this->channel = FSOUND_FREE;
}

void Sound::reset()
{
    this->stop();
}

bool Sound::isPaused()
{
    //return FSOUND_GetPaused(this->channel);
    return this->pausedFlag;
}

void Sound::setPaused(bool pausedFlag)
{
    this->pausedFlag = pausedFlag;
    FSOUND_SetPaused(this->channel, this->pausedFlag);
}

void Sound::pause()
{
    this->pausedFlag = true;
    FSOUND_SetPaused(this->channel, this->pausedFlag);
}

void Sound::resume()
{
    this->pausedFlag = false;
    FSOUND_SetPaused(this->channel, this->pausedFlag);
}

void Sound::setLoop(bool loopFlag)
{
    this->loopFlag = loopFlag;
    FSOUND_SetLoopMode(this->channel, ((this->loopFlag == true) ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF));
}

bool Sound::isLoop()
{
    //return FSOUND_GetLoopMode(this->channel);
    return this->loopFlag;
}

unsigned int Sound::getCurrentPosition()
{
    // Return -1 if the sound isnt playing
    if (this->isPlaying() == false)
        return -1;
    // return the position
    return FSOUND_GetCurrentPosition(this->channel);
}

void Sound::setCurrentPosition(unsigned int value)
{
    FSOUND_SetCurrentPosition(this->channel, value);
}

bool Sound::isMute()
{
    //return FSOUND_GetMute(this->channel);
    return this->muteFlag;
}

void Sound::setMute(bool muteFlag)
{
    this->muteFlag = muteFlag;
    FSOUND_SetMute(this->channel, this->muteFlag);
}

void Sound::mute()
{
    this->muteFlag = true;
    FSOUND_SetMute(this->channel, this->muteFlag);
}

void Sound::unmute()
{
    this->muteFlag = false;
    FSOUND_SetMute(this->channel, this->muteFlag);
}

int Sound::getPan()
{
    //return FSOUND_GetPan(this->channel);
    return this->pan;
}

void Sound::setPan(int pan)
{
    this->pan = pan;
    FSOUND_SetPan(this->channel, this->pan);
}

int Sound::getVolume()
{
    //return FSOUND_GetVolume(this->channel);
    return this->volume;
}

void Sound::setVolume(int volume)
{
    this->volume = volume;
    FSOUND_SetVolume(this->channel, this->volume);
}

void Sound::setVolumeAbsolute(int absoluteVolume)
{
    this->absoluteVolume = absoluteVolume;
    FSOUND_SetVolumeAbsolute(this->channel, this->absoluteVolume);
}

bool Sound::isSurround()
{
    //return FSOUND_GetSurround(this->channel);
    return surroundFlag;
}

bool Sound::getSurround()
{
    //return FSOUND_GetSurround(this->channel);
    return surroundFlag;
}

void Sound::setSurround(bool surroundFlag)
{
    this->surroundFlag = surroundFlag;
    FSOUND_SetSurround(this->channel, this->surroundFlag);
}

int Sound::getPriority()
{
    //return FSOUND_GetPriority(this->channel);
    return this->priority;
}

void Sound::setPriority(int priority)
{
    this->priority = priority;
    FSOUND_SetPriority(this->channel, this->priority);
}

bool Sound::isReserved()
{
    //return FSOUND_GetReserved(this->channel);
    return this->reserved;
}

void Sound::setReserved(bool reserved)
{
    this->reserved = reserved;
    FSOUND_SetReserved(this->channel, this->reserved);
}

int Sound::getFrequency()
{
    return FSOUND_GetFrequency(this->channel);
}

void Sound::setFrequency(int frequency)
{
    FSOUND_SetFrequency(this->channel, frequency);
}

int Sound::getAmplitude()
{
    return FSOUND_GetAmplitude(this->channel);
}

FSOUND_SAMPLE* Sound::getCurrentSample()
{
    return FSOUND_GetCurrentSample(this->channel);
}

int Sound::getSubChannelCount()
{
    return FSOUND_GetNumSubChannels(this->channel);
}

SoundSample* Sound::getSoundSample()
{
    return this->pSoundSample;
}

void Sound::setSoundSample(SoundSample* pSoundSample)
{
    this->pSoundSample = pSoundSample;
}

void Sound::bindToLua(lua_State* pLuaState)
{
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        // TODO: More bindings
        luabind::class_<Sound>("Sound")
        .def(luabind::constructor<>())
        .def("play", (void(Sound::*)()) &Sound::play)
        .def("playEx", (void(Sound::*)()) &Sound::playEx)
        .def("stop", (void(Sound::*)()) &Sound::stop)
        .def("clear", (void(Sound::*)()) &Sound::clear)
        .def("free", (void(Sound::*)()) &Sound::free)
//        .def("setFrequency", (void(Sound::*)(int)) &Sound::setFrequency)
//        .def("setLoop", (void(Sound::*)(bool)) &Sound::setLoop)
//        .def("setMute", (void(Sound::*)(bool)) &Sound::setMute)
//        .def("setPan", (void(Sound::*)(int)) &Sound::setPan)
//        .def("setPaused", (void(Sound::*)(bool)) &Sound::setPaused)
//        .def("setPriority", (void(Sound::*)(int)) &Sound::setPriority)
//        .def("setReserved", (void(Sound::*)(bool)) &Sound::setReserved)
//        .def("setSurround", (void(Sound::*)(bool)) &Sound::setSurround)
//        .def("setVolume", (void(Sound::*)(int)) &Sound::setVolume)
//        .def("setVolumeAbsolute", (void(Sound::*)(int)) &Sound::setVolumeAbsolute)
//        .def("getVolume", (int(Sound::*)()) &Sound::getVolume)
//        .def("getAmplitude", (int(Sound::*)()) &Sound::getAmplitude)
//        .def("setCurrentPosition", (void(Sound::*)(unsigned int)) &Sound::setCurrentPosition)
//        .def("getCurrentPosition", (unsigned int(Sound::*)()) &Sound::getCurrentPosition)
//        .def("isLoop", (bool(Sound::*)()) &Sound::isLoop)
//        .def("isMute", (bool(Sound::*)()) &Sound::isMute)
//        .def("getSubChannelCount", (int(Sound::*)()) &Sound::getSubChannelCount)
//        .def("getPan", (int(Sound::*)()) &Sound::getPan)
//        .def("isPaused", (bool(Sound::*)()) &Sound::isPaused)
//        .def("setPaused", (void(Sound::*)(bool)) &Sound::setPaused)
//        .def("pause", (void(Sound::*)()) &Sound::pause)
//        .def("resume", (void(Sound::*)()) &Sound::resume)
//        .def("getPriority", (int(Sound::*)()) &Sound::getPriority)
//        .def("getReserved", (bool(Sound::*)()) &Sound::getReserved)
//        .def("getSurround", (bool(Sound::*)()) &Sound::getSurround)
//        .def("isPlaying", (bool(Sound::*)()) &Sound::isPlaying)
    ];
}
