#include "Music.h"

bool Music::load(std::string filename)
{
    // load a music file
    FMUSIC_MODULE* pFMODMusicModule = FMUSIC_LoadSong(filename.c_str());
    // handle any problems loading this file
    if (pFMODMusicModule == 0)
    {
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        std::cout << "ERROR: Could not load tracker music: " << filename.c_str() << std::endl;
        std::cout << "FMOD error! (" << FMOD_ErrorString(FSOUND_GetError()) << ") " << std::endl;
        std::cout << "*******************************" << std::endl;
        // Failure
        return false;
    }
    //// Free the song
    //this->free();
    // Store local pointer to the song
    this->pFMODMusicModule = pFMODMusicModule;
    // Store local filename
    this->filename = filename;
    // send a message to the console
    std::cout << "Tracker Music: " << filename.c_str() << " Loaded." << std::endl;
    // Success
    return true;
}

void Music::play()
{
    // If there is a song
    if (this->pFMODMusicModule != 0)
    {
        if (this->isPlaying() == false)
        {
            // Play Song
            FMUSIC_PlaySong(this->pFMODMusicModule);
        }
    }
}

void Music::think()
{
    // TODO: implement me
}

void Music::update(float dTime)
{
    // TODO: implement me
}

void Music::pause()
{
    // If there is a song
    if (this->pFMODMusicModule != 0)
    {
        // Resume song
        FMUSIC_SetPaused(this->pFMODMusicModule, true);
    }
}

void Music::resume()
{
    // If there is a song
    if (this->pFMODMusicModule != 0)
    {
        // Resume the song
        FMUSIC_SetPaused(this->pFMODMusicModule, false);
    }
}

void Music::start()
{
    this->play();
}

void Music::stop()
{
    // If there is a song
    if (this->pFMODMusicModule != 0)
    {
        // Stop the song
        FMUSIC_StopSong(this->pFMODMusicModule);
    }
}

void Music::clear()
{
    // do nothing
}

void Music::free()
{
    // If there is a music module then stop all songs and free it
    if (this->pFMODMusicModule != 0)
    {
        // Stop the Song
        FMUSIC_StopSong(this->pFMODMusicModule);
        // Free the Song
        FMUSIC_FreeSong(this->pFMODMusicModule);
    }
    // Clear pointer
    this->pFMODMusicModule = 0;
    // Clear filename
    this->filename.clear();
    // Reset Volume
    this->volume = 255;
    // Clear mute flag
    this->muteFlag = false;
}

bool Music::isFinished()
{
    // If there is no song then return true TODO: Review this behaviour one day
    if (this->pFMODMusicModule == 0)
        return true;
    // Return true if the song is finished
    return FMUSIC_IsFinished(this->pFMODMusicModule);
}

bool Music::isPlaying()
{
    // If there is no song then return false
    if (this->pFMODMusicModule == 0)
        return false;
    // Return true if the song is playing
    return FMUSIC_IsPlaying(this->pFMODMusicModule);
}

bool Music::isPaused()
{
    // If there is no song return false
    if (this->pFMODMusicModule == 0)
        return false;
    // Return true if the song is paused
    return FMUSIC_GetPaused(this->pFMODMusicModule);
}

bool Music::isMute()
{
    return this->muteFlag;
}

void Music::mute()
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    // Set the Volume for the music
    FMUSIC_SetMasterVolume(this->pFMODMusicModule, 0);
}

void Music::unmute()
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    // Set the Volume for the music
    FMUSIC_SetMasterVolume(this->pFMODMusicModule, this->volume);
}

void Music::setLooping(bool state)
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    // Set Looping state for the Song
    FMUSIC_SetLooping(this->pFMODMusicModule, true);
}

const char* Music::getTrackName()
{
    // If there is no song return false
    if (this->pFMODMusicModule == 0)
        return false;
    // Return the name of this song
    return FMUSIC_GetName(this->pFMODMusicModule);
}

void Music::optimiseChannels(int maxChannels, int minVolume)
{
    // If there is no song then do nothing
    if (this->pFMODMusicModule == 0)
        return;
    // Optimise Channels for this song
    FMUSIC_OptimizeChannels(this->pFMODMusicModule, maxChannels, minVolume);
}

int Music::getNumberOfInstruments()
{
    // If there is no song return no instruments
    if (this->pFMODMusicModule == 0)
        return 0;
    // Return the Number of Instruments used in this song
    return FMUSIC_GetNumInstruments(this->pFMODMusicModule);
}

int Music::getNumberOfOrders()
{
    // If there is no song there are no orders
    if (this->pFMODMusicModule == 0)
        return 0;
    // Return the Number of orders in the song
    return FMUSIC_GetNumOrders(this->pFMODMusicModule);
}

int Music::getNumberOfPatterns()
{
    // If there is no song there are no patterns
    if (this->pFMODMusicModule == 0)
        return 0;
    // Return the number of patterns in the song
    return FMUSIC_GetNumPatterns(this->pFMODMusicModule);
}

int Music::getNumberOfSamples()
{
    // If there is no song there are no samples
    if (this->pFMODMusicModule == 0)
        return 0;
    // Return the number of samples in the song
    return FMUSIC_GetNumSamples(this->pFMODMusicModule);
}

int Music::getOrder()
{
    // If there is no song there are no orders
    if (this->pFMODMusicModule == 0)
        return 0;
    // Return the current order
    return FMUSIC_GetOrder(this->pFMODMusicModule);
}

int Music::getRow()
{
    // If there is no song there are no rows
    if (this->pFMODMusicModule == 0)
        return 0;
    // Return the current row
    return FMUSIC_GetRow(this->pFMODMusicModule);
}

int Music::getPattern()
{
    // If there is no song there are no patterns
    if (this->pFMODMusicModule == 0)
        return 0;
    // Return the current pattern
    return FMUSIC_GetPattern(this->pFMODMusicModule);
}

int Music::getPatternLength(int orderNo)
{
    // If there is no song there are no patterns  so pattern list is 0
    if (this->pFMODMusicModule == 0)
        return 0;
    // Return the Length of a particular pattern
    return FMUSIC_GetPatternLength(this->pFMODMusicModule, orderNo);
}

int Music::getChannel()
{
    // If there is no song there is no channel its playing on
    if (this->pFMODMusicModule == 0)
        return -1;
    // If the song isn't playing there is no channel
    if (FMUSIC_IsPlaying(this->pFMODMusicModule) == false)
        return -1;
    // Return the real channel this song is playing on
    return FMUSIC_GetRealChannel(this->pFMODMusicModule, -1);
}

int Music::getTrackerMusicType()
{
    // If there is no song return -1
    if (this->pFMODMusicModule == 0)
        return -1;
    return FMUSIC_GetType(this->pFMODMusicModule);
}

int Music::getBeatsPerMinute()
{
    // If there is no song return -1
    if (this->pFMODMusicModule == 0)
        return -1;
    return FMUSIC_GetBPM(this->pFMODMusicModule);
}

int Music::getSpeed()
{
    // If there is no song return -1
    if (this->pFMODMusicModule == 0)
        return -1;
    return FMUSIC_GetSpeed(this->pFMODMusicModule);
}

int Music::getPlaybackTime()
{
    // If there is no song return -
    if (this->pFMODMusicModule == 0)
        return -1;
    return FMUSIC_GetTime(this->pFMODMusicModule);
}

void Music::setPlayBackSpeed(float speed)
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    FMUSIC_SetMasterSpeed(this->pFMODMusicModule, speed);
}

void Music::resetPlayBackSpeed()
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    FMUSIC_SetMasterSpeed(this->pFMODMusicModule, 1.0f);
}

void Music::setOrder(int order)
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    FMUSIC_SetOrder(this->pFMODMusicModule, order);
}

void Music::setPanSeparation(float value)
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    FMUSIC_SetPanSeperation(this->pFMODMusicModule, value);
}

int Music::getGlobalVolume()
{
    // If there is no song return 0
    if (this->pFMODMusicModule == 0)
        return 0;
    return FMUSIC_GetGlobalVolume(this->pFMODMusicModule);
}

int Music::getVolume()
{
    //return FMUSIC_GetMasterVolume(this->pFMODMusicModule);
    return this->volume;
}

void Music::setVolume(int value)
{
    // Keep a local copy of the volume
    this->volume = value;
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    // Set the Volume for the music
    FMUSIC_SetMasterVolume(this->pFMODMusicModule, value);
}

void* Music::getUserData()
{
    // If there is no song return 0
    if (this->pFMODMusicModule == 0)
        return 0;
    return FMUSIC_GetUserData(this->pFMODMusicModule);
}

void Music::setUserData(void* pUserData)
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    FMUSIC_SetUserData(this->pFMODMusicModule, pUserData);
}

void Music::setInstrumentCallback(FMUSIC_CALLBACK callback, int instrument)
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    FMUSIC_SetInstCallback(this->pFMODMusicModule, callback, instrument);
}

void Music::setZxxCallback(FMUSIC_CALLBACK callback)
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    FMUSIC_SetZxxCallback(this->pFMODMusicModule, callback);
}

void Music::setOrderCallback(FMUSIC_CALLBACK callback, int orderStep)
{
    // If there is no song return
    if (this->pFMODMusicModule == 0)
        return;
    FMUSIC_SetOrderCallback(this->pFMODMusicModule, callback, orderStep);
}

void Music::bindToLua(lua_State* pLuaState)
{
    // TODO: More bindings
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        luabind::class_<Music>("Music")
        .def(luabind::constructor<>())
        // GENERAL FUNCTIONS
        .def("load", (bool(Music::*)(std::string)) &Music::load)
        .def("play", (void(Music::*)()) &Music::play)
        .def("pause", (void(Music::*)()) &Music::pause)
        .def("resume", (void(Music::*)()) &Music::resume)
        .def("stop", (void(Music::*)()) &Music::stop)
        .def("free", (void(Music::*)()) &Music::free)
        .def("isFinished", (bool(Music::*)()) &Music::isFinished)
        .def("isPlaying", (bool(Music::*)()) &Music::isPlaying)
        .def("isPaused", (bool(Music::*)()) &Music::isPaused)
        // MUTE
        .def("isMute", (bool(Music::*)()) &Music::isMute)
        .def("mute", (void(Music::*)()) &Music::mute)
        .def("unmute", (void(Music::*)()) &Music::unmute)
//        .def("getName", (const char*(Music::*)()) &Music::getName)
//        .def("optimiseChannels", (void(Music::*)(int, int)) &Music::optimiseChannels)
//        .def("getNumberOfInstruments", (int(Music::*)()) &Music::getNumberOfInstruments)
//        .def("getNumberOfOrders", (int(Music::*)()) &Music::getNumberOfOrders)
//        .def("getNumberOfPatterns", (int(Music::*)()) &Music::getNumberOfPatterns)
//        .def("getNumberOfSamples", (int(Music::*)()) &Music::getNumberOfSamples)
//        .def("getOrder", (int(Music::*)()) &Music::getOrder)
//        .def("getRow", (int(Music::*)()) &Music::getRow)
//        .def("getPattern", (int(Music::*)()) &Music::getPattern)
//        .def("getPatternLength", (int(Music::*)(int)) &Music::getPatternLength)
//        .def("getChannel", (int(Music::*)()) &Music::getChannel)
//        .def("getTrackerMusicType", (int(Music::*)()) &Music::getTrackerMusicType)
//        .def("getBeatsPerMinute", (int(Music::*)()) &Music::getBeatsPerMinute)
//        .def("getSpeed", (int(Music::*)()) &Music::getSpeed)
//        .def("getPlaybackTime", (int(Music::*)()) &Music::getPlaybackTime)
//        .def("isPaused", (bool(Music::*)()) &Music::isPaused)
//        .def("setLooping", (void(Music::*)(bool)) &Music::setLooping)
//        .def("setPlayBackSpeed", (void(Music::*)(float)) &Music::setPlayBackSpeed)
//        .def("resetPlayBackSpeed", (void(Music::*)()) &Music::resetPlayBackSpeed)
//        .def("getGlobalVolume", (int(Music::*)()) &Music::getGlobalVolume)
//        .def("getMasterVolume", (int(Music::*)()) &Music::getMasterVolume)
//        .def("setMasterVolume", (void(Music::*)(int)) &Music::setMasterVolume)
//        .def("setOrder", (void(Music::*)(int)) &Music::setOrder)
//        .def("setPanSeparation", (void(Music::*)(float)) &Music::setPanSeparation)
    ];
}
