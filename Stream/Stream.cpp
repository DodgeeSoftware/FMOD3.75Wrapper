#include "Stream.h"

bool Stream::load(std::string filename)
{
    // If there is an existing sound stream then get rid of it
    if (this->pFMODSoundStream != 0)
    {
        this->stop();
        this->free();
    }
    // Load a flat 2d stream
    this->pFMODSoundStream = FSOUND_Stream_Open(filename.c_str(), FSOUND_NORMAL | FSOUND_2D, 0, 0);
    // If there was a problem
    if (this->pFMODSoundStream == 0)
    {
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        std::cout << "ERROR: Unable to load stream: " << filename.c_str() << std::endl;
        // Send a message to the console
        std::cout << FMOD_ErrorString(FSOUND_GetError()) << std::endl;
        std::cout << "*******************************" << std::endl;
        // Failure
        return false;
    }
    else
    {
        //// Set an end callback for this stream
        //FSOUND_Stream_SetEndCallback(this->pFMODSoundStream, Stream::streamEndCallBack, this);
        // Make the Stream object looped
        if (this->loopFlag == true)
        {
            int mode = FSOUND_Stream_GetMode(this->pFMODSoundStream);
            bool isLooping = mode & 2;
            if (isLooping == false)
            {
                mode = mode xor FSOUND_LOOP_NORMAL;
                FSOUND_Stream_SetMode(this->pFMODSoundStream, mode);
            }
        }
        else
        {
            int mode = FSOUND_Stream_GetMode(this->pFMODSoundStream);
            bool isLooping = mode & 2;
            if (isLooping == true)
            {
                mode = mode xor FSOUND_LOOP_NORMAL;
                FSOUND_Stream_SetMode(this->pFMODSoundStream, mode);
            }
        }
        // Set the loop count
        FSOUND_Stream_SetLoopCount(this->pFMODSoundStream, this->loopCount);
    }
    // Set the filename
    this->filename = filename;
    // Success
    return true;
}

void Stream::think()
{
    // TODO: implement me
}

void Stream::update(float dTime)
{
    // NOTE: Implement me if needed
}

void Stream::clear()
{
    // TODO: Implement me
}

void Stream::free()
{
    // Reset to defaults
//    this->playingFlag = false;
    this->pausedFlag = false;
    this->loopFlag = false; // No Loop Flag for Streams
    this->loopCount = -1; // If loopingFlag set to true the default loop count in infinitiy
    this->muteFlag = false; // No Mute Flag for Streams
    this->pan = 128; // Middle Balance
    this->volume = 255; // Max volume
    this->absoluteVolume = 255; // Max absolute volume
    this->surroundFlag = false; // A Sound is a flag non positional sound so we assume non surround here
    this->priority = 0; // Mid range priority
    //this->reserved = false;
    // Unreserve channel
    if (FSOUND_GetReserved(this->channel) == true)
    {
        FSOUND_SetReserved(this->channel, false);
    }
    this->channel = FSOUND_FREE;
    // Don't do anything unless we have loaded a soundstream
    if (this->pFMODSoundStream != 0)
    {
        // Stop the sound stream
        FSOUND_Stream_Stop(this->pFMODSoundStream);
        // Close / Release a stream
        FSOUND_Stream_Close(this->pFMODSoundStream);
        // Reset the sound stream pointer
        this->pFMODSoundStream = 0;
    }
    // Clear the filename
    this->filename.clear();
    this->name.clear();
}

bool Stream::isPlaying()
{
    /* TODO: What if the stream has stopped playing and another sound/stream is on the channel,
        we are going to get false results here, so we might need to fix this at some point */
    return FSOUND_IsPlaying(this->channel);
}

void Stream::play()
{
    // Don't do anything unless we have loaded a soundstream
    if (this->pFMODSoundStream != 0)
    {
//        // Sound is now playing so set flag
//        this->playingFlag = true;
        // Try and play a sound stream
        this->channel = FSOUND_Stream_Play(FSOUND_FREE, this->pFMODSoundStream);
        if (this->channel == FSOUND_FREE)
        {
            // Send a message to the console
            std::cout << "*******************************" << std::endl;
            std::cout << "ERROR: Stream::play Unable to play stream: " << this->filename.c_str() << std::endl;
            std::cout << FMOD_ErrorString(FSOUND_GetError()) << std::endl;
            std::cout << "*******************************" << std::endl;
        }
//        // Reserve the channel the sound is playing on
//        FSOUND_SetReserved(this->channel, true);
        // Set Paused (if the sound has been paused)
        FSOUND_SetPaused(this->channel, this->pausedFlag);
        /* NOTE: Loop Mode is controlled via the this->pFMODSoundStream object. Since there is one per stream
                    we don't use a flag for looping here */
        //// Set if playback should loop or not
        //FSOUND_SetLoopMode(this->channel, ((this->loopFlag == true) ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF));
        /* NOTE: Muting a channel */
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

        // Set if the Sound should be muted or not
        FSOUND_SetMute(this->channel, this->muteFlag);


        /* A nasty hack to compensate for FMODs lack of a global mute function for the audio system */
        if (FMODGlobals::muteFlag == true)
        {
            // Brute force mute
            FSOUND_SetMute(this->channel, true);
        }
    }
}

void Stream::playEx()
{
    // Don't do anything unless we have loaded a soundstream
    if (this->pFMODSoundStream != 0)
    {
//        // Sound is now playing so set flag
//        this->playingFlag = true;
        // Sound is now paused so set the Flag
        this->pausedFlag = true;
        // Try and play a sound stream
        this->channel = FSOUND_Stream_PlayEx(FSOUND_FREE, this->pFMODSoundStream, 0, true);
//        // Reserve the channel the sound is playing on
//        FSOUND_SetReserved(this->channel, true);
        // Set Paused (if the sound has been paused)
        FSOUND_SetPaused(this->channel, this->pausedFlag);
        /* NOTE: Loop Mode is controlled via the this->pFMODSoundStream object. Since there is one per stream
                    we don't use a flag for looping here */
        //// Set if playback should loop or not
        //FSOUND_SetLoopMode(this->channel, ((this->loopFlag == true) ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF));
        /* NOTE: Muting a channel */
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
    }
}

void Stream::start()
{
    // TODO: Implement me
    this->play();
}

void Stream::stop()
{
//            // Sound is no longer playing so set flag
//            this->playingFlag = false;
    // Sound is no longer paused so set flag
    this->pausedFlag = false;
    // Unreserve channel
    if (FSOUND_GetReserved(this->channel) == true)
    {
        FSOUND_SetReserved(this->channel, false);
        // Reset channel to free
        this->channel = FSOUND_FREE;
    }
    // If there is a stream then stop it from playing
    if (this->pFMODSoundStream != 0)
    {
        // Stop the sound stream
        FSOUND_Stream_Stop(this->pFMODSoundStream);
    }
}

void Stream::reset()
{
    this->stop();
}

bool Stream::isPaused()
{
    //return FSOUND_GetPaused(this->channel);
    return this->pausedFlag;
}

void Stream::setPaused(bool pausedFlag)
{
    this->pausedFlag = pausedFlag;
    FSOUND_SetPaused(this->channel, this->pausedFlag);
}

void Stream::pause()
{
    this->pausedFlag = true;
    FSOUND_SetPaused(this->channel, this->pausedFlag);
}

void Stream::resume()
{
    this->pausedFlag = false;
    FSOUND_SetPaused(this->channel, this->pausedFlag);
}

bool Stream::isLoop()
{
    /* NOTE: Setting the stream to loop automatically sets the channel to loop
        so here we query the channel instead of the stream*/
    //return FSOUND_GetLoopMode(this->channel);
    //int mode = FSOUND_Stream_GetMode(this->pFMODSoundStream);
    //return mode & 2;
    return this->loopFlag;
}

void Stream::setLoop(bool loopFlag)
{
    // Set loop Flag
    this->loopFlag = loopFlag;
    /* NOTE: Cannot use the channel functions to modify loop loopFlag. Must manipulate the stream
        if (loopFlag == true) FSOUND_SetLoopMode(this->channel, FSOUND_LOOP_NORMAL);
        if (loopFlag == false) FSOUND_SetLoopMode(this->channel,  FSOUND_LOOP_OFF); */
    // Make the Stream object looped
    if (this->loopFlag == true)
    {
        int mode = FSOUND_Stream_GetMode(this->pFMODSoundStream);
        bool isLooping = mode & 2;
        if (isLooping == true)
            return;
        mode = mode xor FSOUND_LOOP_NORMAL;
        FSOUND_Stream_SetMode(this->pFMODSoundStream, mode);
    }
    else
    {
        int mode = FSOUND_Stream_GetMode(this->pFMODSoundStream);
        bool isLooping = mode & 2;
        if (isLooping == false)
            return;
        mode = mode xor FSOUND_LOOP_NORMAL;
        FSOUND_Stream_SetMode(this->pFMODSoundStream, mode);
    }
}

void Stream::setLoopCount(int count)
{
    // Set loop count
    this->loopCount = count;
    /* NOTE: For streams the loop count is set by using stream modifiers. I don't believe their is a counterpart to non-streaming sounds */
    FSOUND_Stream_SetLoopCount(this->pFMODSoundStream, this->loopCount);
}

int Stream::getVolume()
{
    //return FSOUND_GetVolume(this->channel);
    return this->volume;
}

void Stream::setVolume(int volume)
{
    this->volume = volume;
    FSOUND_SetVolume(this->channel, this->volume);
}

void Stream::setVolumeAbsolute(int absoluteVolume)
{
    this->absoluteVolume = absoluteVolume;
    FSOUND_SetVolumeAbsolute(this->channel, this->absoluteVolume);
}

int Stream::getPan()
{
    //return FSOUND_GetPan(this->channel);
    return this->pan;
}

void Stream::setPan(int pan)
{
    this->pan = pan;
    FSOUND_SetPan(this->channel, this->pan);
}

bool Stream::isSurround()
{
    //return FSOUND_GetSurround(this->channel);
    return this->surroundFlag;
}

void Stream::setSurround(bool surroundFlag)
{
    this->surroundFlag = surroundFlag;
    FSOUND_SetSurround(this->channel, this->surroundFlag);
}

bool Stream::isMute()
{
    return FSOUND_GetMute(this->channel);
}

void Stream::setMute(bool state)
{
    this->muteFlag = state;
    FSOUND_SetMute(this->channel, this->muteFlag);
}

void Stream::mute()
{
    this->muteFlag = true;
    FSOUND_SetMute(this->channel, this->muteFlag);
}

void Stream::unmute()
{
    this->muteFlag = false;
    FSOUND_SetMute(this->channel, this->muteFlag);
}

int Stream::getPriority()
{
    //return FSOUND_GetPriority(this->channel);
    return this->priority;
}

void Stream::setPriority(int priority)
{
    this->priority = priority;
    FSOUND_SetPriority(this->channel, this->priority);
}

bool Stream::isReserved()
{
    return FSOUND_GetReserved(this->channel);
}

void Stream::setReserved(bool value)
{
    FSOUND_SetReserved(this->channel, value);
}

int Stream::getFrequency()
{
    return FSOUND_GetFrequency(this->channel);
}

void Stream::setFrequency(int value)
{
    FSOUND_SetFrequency(this->channel, value);
}

int Stream::getAmplitude()
{
    return FSOUND_GetAmplitude(this->channel);
}

void Stream::setCurrentPosition(unsigned int value)
{
    FSOUND_SetCurrentPosition(this->channel, value);
}

unsigned int Stream::getCurrentPosition()
{
    return FSOUND_GetCurrentPosition(this->channel);
}

FSOUND_SAMPLE* Stream::getCurrentSample()
{
    return FSOUND_GetCurrentSample(this->channel);
}

int Stream::getSubChannelCount()
{
    return FSOUND_GetNumSubChannels(this->channel);
}

int Stream::getLength()
{
    return FSOUND_Stream_GetLength(this->pFMODSoundStream);
}

int Stream::getLengthMs()
{
    return FSOUND_Stream_GetLengthMs(this->pFMODSoundStream);
}

unsigned int Stream::getMode()
{
    return FSOUND_Stream_GetMode(this->pFMODSoundStream);
}

void Stream::setMode(unsigned int mode)
{
    FSOUND_Stream_SetMode(this->pFMODSoundStream, mode);
}

int Stream::getOpenState()
{
    return FSOUND_Stream_GetOpenState(this->pFMODSoundStream);
}

unsigned int Stream::getStreamPosition()
{
    return FSOUND_Stream_GetPosition(this->pFMODSoundStream);
}

void Stream::setStreamPosition(unsigned int position)
{
    FSOUND_Stream_SetPosition(this->pFMODSoundStream, position);
}

FSOUND_SAMPLE* Stream::getSample()
{
    return FSOUND_Stream_GetSample(this->pFMODSoundStream);
}

int Stream::getTime()
{
    return FSOUND_Stream_GetTime(this->pFMODSoundStream);
}

void Stream::setTime(int ms)
{
    FSOUND_Stream_SetTime(this->pFMODSoundStream, ms);
}

void Stream::setSubStream(int index)
{
    FSOUND_Stream_SetSubStream(this->pFMODSoundStream, index);
}

void Stream::setSubStreamSentence(const int* sentenceList, int numItems)
{
    FSOUND_Stream_SetSubStreamSentence(this->pFMODSoundStream, sentenceList, numItems);
}

int Stream::getSubStreamCount()
{
    return FSOUND_Stream_GetNumSubStreams(this->pFMODSoundStream);
}

signed char F_CALLBACKAPI Stream::streamEndCallBackRouter(FSOUND_STREAM* pFMODStream, void* buff, int len, void* pUserdata)
{
//    // typedef signed char (F_CALLBACKAPI *FSOUND_STREAMCALLBACK)  (FSOUND_STREAM *stream, void *buff, int len, void *userdata);
//    // Grab the Stream
//    Stream* pStream = (Stream*)pUserdata;
//    // Set the playing flag to false
//    pStream->setPlayingFlag(false);
//    // Send a message to the console
//    std::cout << "unsigned char F_CALLBACKAPI Stream::streamEndCallBack(FSOUND_STREAM* pFMODStream, void* buff, int len, void* pUserdata)" << std::endl;
    return true;
}

void Stream::bindToLua(lua_State* pLuaState)
{
    // TODO: More bindings
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        luabind::class_<Stream>("Stream")
        .def(luabind::constructor<>())
        .def("load", (bool(Stream::*)(std::string)) &Stream::load)
        .def("play", (void(Stream::*)()) &Stream::play)
        .def("playEx", (void(Stream::*)()) &Stream::playEx)
        .def("stop", (void(Stream::*)()) &Stream::stop)
        .def("clear", (void(Stream::*)()) &Stream::clear)
        .def("free", (void(Stream::*)()) &Stream::free)


        .def("setLoop", (void(Stream::*)(bool)) &Stream::setLoop)


//        .def("getLength", (int(Stream::*)()) &Stream::getLength)
//        .def("getLengthMs", (int(Stream::*)()) &Stream::getLengthMs)
//        .def("getMode", (unsigned int(Stream::*)()) &Stream::getMode)
//        .def("getSubStreamCount", (int(Stream::*)()) &Stream::getSubStreamCount)
//        .def("getOpenState", (int(Stream::*)()) &Stream::getOpenState)
//        .def("getTime", (int(Stream::*)()) &Stream::getTime)
//        .def("setLoopCount", (void(Stream::*)(int)) &Stream::setLoopCount)
//        .def("setMode", (void(Stream::*)(unsigned int)) &Stream::setLoopCount)
//        .def("setPosition", (void(Stream::*)(unsigned int)) &Stream::setPosition)
//        .def("setSubStream", (void(Stream::*)(int)) &Stream::setSubStream)
//        .def("setSubStreamSentence", (void(Stream::*)(const int* sentenceList, int numItems)) &Stream::setSubStreamSentence)
//        .def("setTime", (void(Stream::*)(int)) &Stream::setTime)
    ];
}
