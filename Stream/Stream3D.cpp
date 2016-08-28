#include "Stream3D.h"

bool Stream3D::load(std::string filename)
{
    this->pFMODSoundStream = FSOUND_Stream_Open(filename.c_str(), FSOUND_FORCEMONO, 0, 0);
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
//        // Set an end callback for this stream
//        FSOUND_Stream_SetEndCallback(this->pFMODSoundStream, Stream::streamEndCallBack, this);
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

void Stream3D::play()
{
    // Don't do anything unless we have loaded a soundstream
    if (this->pFMODSoundStream == 0)
        return;

//        // Sound is now playing so set flag
//        this->playingFlag = true;
    // Try and play a sound stream
    this->channel = FSOUND_Stream_Play(FSOUND_FREE, this->pFMODSoundStream);
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

void Stream3D::playEx()
{
    // Don't do anything unless we have loaded a soundstream
    if (this->pFMODSoundStream != 0)
        return;

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

float Stream3D::getX()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return position[0];
    return this->x;
}

float Stream3D::getY()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return position[1];
    return this->y;
}

float Stream3D::getZ()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return position[2];
    return this->z;
}

void Stream3D::setPosition(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    float position[3] = {this->x, this->y, this->z};
    float velocity[3] = {this->xVelocity, this->yVelocity, this->zVelocity};
    FSOUND_3D_SetAttributes(this->channel, position, velocity);
}

float Stream3D::getXVelocity()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return velocity[0];
    return this->xVelocity;
}

float Stream3D::getYVelocity()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return velocity[1];
    return this->yVelocity;            // OLD CODE
}

float Stream3D::getZVelocity()
{
    // OLD CODE
    //float position[3] = {0.0f, 0.0f, 0.0f};
    //float velocity[3] = {0.0f, 0.0f, 0.0f};
    //FSOUND_3D_GetAttributes(this->channel, position, velocity);
    //return velocity[2];
    return this->zVelocity;
}

void Stream3D::setVelocity(float xVelocity, float yVelocity, float zVelocity)
{
    this->xVelocity = xVelocity;
    this->yVelocity = yVelocity;
    this->zVelocity = zVelocity;
    float position[3] = {this->x, this->y, this->z};
    float velocity[3] = {this->xVelocity, this->yVelocity, this->zVelocity};
    FSOUND_3D_SetAttributes(this->channel, position, velocity);
}

float Stream3D::getMinDistance()
{
    // OLD CODE
    //if (this->channel == -1)
        //return 0.0f;
    //float min = 0.0f, max = 0.0f;
    //FSOUND_3D_GetMinMaxDistance(this->channel, &min, &max);
    //return min;
    return this->minDistance;
}

float Stream3D::getMaxDistance()
{
    // OLD CODE
    //if (this->channel == -1)
        //return 0.0f;
    //float min = 0.0f, max = 0.0f;
    //FSOUND_3D_GetMinMaxDistance(this->channel, &min, &max);
    //return max;
    return this->maxDistance;
}

void Stream3D::setMinDistance(float minDistance)
{
    this->minDistance = minDistance;
    FSOUND_3D_SetMinMaxDistance(this->channel, this->minDistance, this->maxDistance);
}

void Stream3D::setMaxDistance(float maxDistance)
{
    this->maxDistance = maxDistance;
    FSOUND_3D_SetMinMaxDistance(this->channel, this->minDistance, this->maxDistance);
}

void Stream3D::setMinMaxDistance(float minDistance, float maxDistance)
{
    this->minDistance = minDistance;
    this->maxDistance = maxDistance;
    FSOUND_3D_SetMinMaxDistance(this->channel, this->minDistance, this->maxDistance);
}

signed char F_CALLBACKAPI Stream3D::streamEndCallBackRouter(FSOUND_STREAM* pFMODStream, void* buff, int len, void* pUserdata)
{
//    // Grab the Stream
//    Stream* pStream = (Stream*)pUserdata;
//    // Set the playing flag to false
//    pStream->setPlayingFlag(false);
//    // Send a message to the console
//    std::cout << "unsigned char F_CALLBACKAPI Stream3D::streamEndCallBack(FSOUND_STREAM* pFMODStream, void* buff, int len, void* pUserdata)" << std::endl;
    return true;
}

void Stream3D::bindToLua(lua_State* pLuaState)
{
    // TODO: More bindings
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        luabind::class_<Stream3D>("Stream3D")
        .def(luabind::constructor<>())
        .def("play", (void(Stream3D::*)()) &Stream3D::play)
        .def("playEx", (void(Stream3D::*)()) &Stream3D::playEx)
        .def("stop", (void(Stream3D::*)()) &Stream3D::stop)
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
