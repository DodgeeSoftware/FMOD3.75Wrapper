#include "AudioSystem.h"

bool FMODGlobals::muteFlag = false; // NOTE: This is essential. It's part of a hack to get a global mute working

bool AudioSystem::init(int frequency, int maxChannels)
{
    /* NOTE: flags for the sound system are not cross
        platform so I have chosen not to support them  */
    if (FSOUND_Init(frequency, maxChannels, 0) == false)
    {
        // Get the Audio Error
        unsigned errorID = FSOUND_GetError();
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        std::cout << "ERROR: " << errorID << std::endl;
        std::cout << "bool AudioSystem::init() failure. " << std::endl;
        std::cout << "*******************************" << std::endl;
        // Failure
        return false;
    }
    // Set our local reference to the frequency
    this->frequency = frequency;
    // Set our local reference to max software channels
    this->maxSoftwareChannels = maxChannels;

    // Success
    return true;
}

void AudioSystem::setListener(float x, float y)
{
    float position[3] = {x, y, 0.0f};
    float velocity[3] = {0.0f, 0.0f, 0.0f};
    float forward[3] = {0.0f, 0.0f, -1.0f}; // Direction the camera is facing in 3d
    float upVector[3] = {0.0f, 1.0f, 0.0f};
    FSOUND_3D_Listener_SetAttributes(position, velocity, forward[0], forward[1], forward[2], upVector[0], upVector[1], upVector[2]);
}

void AudioSystem::setListener(float x, float y, float z, float xVelocity, float yVelocity, float zVelocity, float xForward, float yForward, float zForward, float upX, float upY, float upZ)
{
    // TODO: for 3d projects we need to feed in more information into this function. This is kinda a placeholder. Needs to be completed with  more params later. 12 Params in total need to be fed in.
    float position[3] = {x, y, z};
    float velocity[3] = {xVelocity, yVelocity, zVelocity};
    float forward[3] = {xForward, yForward, zForward}; // Direction the camera is facing in 3d
    float upVector[3] = {upX, upY, upZ};
    FSOUND_3D_Listener_SetAttributes(position, velocity, forward[0], forward[1], forward[2], upVector[0], upVector[1], upVector[2]);
}

void AudioSystem::think()
{
    // TODO: implement me
}

void AudioSystem::update(float dTime)
{
    FSOUND_Update();
}

void AudioSystem::shutdown()
{
    this->frequency = 441500;
    this->maxSoftwareChannels = 1024;
    FSOUND_Close();
}

float AudioSystem::getVersion()
{
    return FSOUND_GetVersion();
}

void AudioSystem::pause()
{
    FSOUND_SetPaused(FSOUND_ALL, true);
}

void AudioSystem::resume()
{
    FSOUND_SetPaused(FSOUND_ALL, false);
}

void AudioSystem::stop()
{
    FSOUND_StopSound(FSOUND_ALL);
    FMUSIC_StopAllSongs();
}

unsigned int AudioSystem::getSoundEffectsVolume()
{
    //// Volume returned is in the range 0 - 255
    //return FSOUND_GetSFXMasterVolume();
    return this->soundEffectsVolume;
}

void AudioSystem::setSoundEffectsVolume(int volume)
{
    // Volume should be in the range of 0 - 255
    FSOUND_SetSFXMasterVolume(volume);
    // Keep local record of the sound effects volume
    this->soundEffectsVolume = volume;
}

unsigned int AudioSystem::getMusicVolume()
{
    // NOTE: there doesn't seem to be away of getting the system's music audio its by individial music piece
    return this->musicVolume;
}

void AudioSystem::setMusicVolume(int volume)
{
//    // Set the volume of the stream music
//    this->streamMusic.setVolume(volume);
//    //// Set the volume of the tracker music
//    this->trackerMusic.setMasterVolume(volume);
    // NOTE: there doesn't seem to be away of setting the system's music audio its by individial music piece
    this->musicVolume = volume;
}

void AudioSystem::setMute(bool state)
{
    if (state == true)
    {
        this->mute();
    }
    else
    {
        this->unmute();
    }
}

void AudioSystem::mute()
{
    FSOUND_SetMute(FSOUND_ALL, true);
    FSOUND_SetVolumeAbsolute(FSOUND_ALL, 0); // TODO: Is it possible to comment out this line?
    FSOUND_SetSFXMasterVolume(0);

    FMODGlobals::muteFlag = true;
}

void AudioSystem::unmute()
{
    FSOUND_SetMute(FSOUND_ALL, false);
    FSOUND_SetVolumeAbsolute(FSOUND_ALL, 255); // TODO: Is it possible to comment out this line?
    FSOUND_SetSFXMasterVolume(255);

    FMODGlobals::muteFlag = false;

}

void AudioSystem::monoSpeakers()
{
    FSOUND_SetSpeakerMode(FSOUND_SPEAKERMODE_MONO);
}

void AudioSystem::stereoSpeakers()
{
    FSOUND_SetSpeakerMode(FSOUND_SPEAKERMODE_STEREO);
}

void AudioSystem::setStereoBalance(int value)
{
    FSOUND_SetPan(FSOUND_ALL, value);
}

float AudioSystem::getCPUUsage()
{
    return FSOUND_GetCPUUsage();
}

int AudioSystem::getChannelsPlaying()
{
    return FSOUND_GetChannelsPlaying();
}

int AudioSystem::getDriver()
{
    return FSOUND_GetDriver();
}

std::string AudioSystem::getDriverCapabilities(int driverID)
{
    std::string capsBuffer;
    unsigned int caps = 0;
    FSOUND_GetDriverCaps(driverID, &caps);
    if (caps & FSOUND_CAPS_HARDWARE)
        capsBuffer.append("This driver supports hardware accelerated 3d sound. \n" );
    if (caps & FSOUND_CAPS_EAX2)
        capsBuffer.append("This driver supports EAX 2 reverb  \n" );
    if (caps & FSOUND_CAPS_EAX3)
        capsBuffer.append("This driver supports EAX 3 reverb  \n" );
    return capsBuffer;
}

std::string AudioSystem::getDriverName(int driverID)
{
    return std::string(FSOUND_GetDriverName(driverID));
}

int AudioSystem::getMaxSamples()
{
    return FSOUND_GetMaxSamples();
}

int AudioSystem::getFrequency()
{
    return this->frequency;
}

int AudioSystem::getMaxSoftwareChannels()
{
    return this->maxSoftwareChannels;
}

int AudioSystem::getMaxChannels()
{
    return FSOUND_GetMaxChannels();
}

std::string AudioSystem::getMemoryStatistics()
{
    unsigned int currentAllocated = 0;
    unsigned int maxAllocated = 0;
    FSOUND_GetMemoryStats(&currentAllocated, &maxAllocated);
    char* currentlyAllocatedString = 0;
    itoa(currentAllocated, currentlyAllocatedString, 10);
    char* maxAllocatedString = 0;
    itoa(maxAllocated, maxAllocatedString, 10);

    std::string buffer;
    buffer.append("Currently Allocated: ");
    buffer.append(currentlyAllocatedString);
    buffer.append(", ");
    buffer.append("Max Allocated: ");
    buffer.append(maxAllocatedString);
    return buffer;
}

int AudioSystem::getDrivers()
{
    return FSOUND_GetNumDrivers();
}

signed char AudioSystem::getNumHWChannels()
{
    int num2d = 0;
    int num3d = 0;
    int total = 0;
    FSOUND_GetNumHWChannels(&num2d, &num3d, &total);
    return total;
}

int AudioSystem::getOutput()
{
    return FSOUND_GetOutput();
}

void* AudioSystem::getOutputHandle()
{
    return FSOUND_GetOutputHandle();
}

int AudioSystem::getOutputRate()
{
    return FSOUND_GetOutputRate();
}

int AudioSystem::getNumberOfCDTracks()
{
    return FSOUND_CD_GetNumTracks(0);
}

int AudioSystem::getNumberOfCDTracks(char drive)
{
    return FSOUND_CD_GetNumTracks(drive);
}

bool AudioSystem::isCDPaused()
{
    return FSOUND_CD_GetPaused(0);
}

bool AudioSystem::isCDPaused(char drive)
{
    return FSOUND_CD_GetPaused(drive);
}

int AudioSystem::getCDTrack()
{
    return FSOUND_CD_GetTrack(0);
}

int AudioSystem::getCDTrack(char drive)
{
    return FSOUND_CD_GetTrack(drive);
}

int AudioSystem::getCDTrackLength(int track)
{
    return FSOUND_CD_GetTrackLength(0, track);
}

int AudioSystem::getCDTrackLength(char drive, int track)
{
    return FSOUND_CD_GetTrackLength(drive, track);
}

int AudioSystem::getCDTrackTime()
{
    FSOUND_CD_GetTrackTime(0);
}

int AudioSystem::getCDTrackTime(char drive)
{
    FSOUND_CD_GetTrackTime(drive);
}

int AudioSystem::getCDVolume()
{
    return FSOUND_CD_GetVolume(0);
}

int AudioSystem::getCDVolume(char drive)
{
    return FSOUND_CD_GetVolume(drive);
}

bool AudioSystem::openCDTray()
{
    return FSOUND_CD_OpenTray(0, 1);
}

bool AudioSystem::openCDTray(char drive)
{
    return FSOUND_CD_OpenTray(drive, 1);
}

bool AudioSystem::closeCDTray()
{
    return FSOUND_CD_OpenTray(0, 0);
}

bool AudioSystem::closeCDTray(char drive)
{
    return FSOUND_CD_OpenTray(drive, 0);
}

bool AudioSystem::playCD()
{
    return FSOUND_CD_Play(0, 0 );
}

bool AudioSystem::playCD(char drive)
{
    return FSOUND_CD_Play(drive, 0 );
}

bool AudioSystem::playCDTrack(int track)
{
    return FSOUND_CD_Play(0, track);
}

bool AudioSystem::playCDTrack(char drive, int track)
{
    return FSOUND_CD_Play(drive, track);
}

bool AudioSystem::pauseCD()
{
    return FSOUND_CD_SetPaused(0, true);
}

bool AudioSystem::pauseCD(char drive)
{
    return FSOUND_CD_SetPaused(drive, true);
}

bool AudioSystem::resumeCD()
{
    return FSOUND_CD_SetPaused(0, false);
}

bool AudioSystem::resumeCD(char drive)
{
    return FSOUND_CD_SetPaused(0, false);
}

void AudioSystem::setCDPlayMode(signed char mode)
{
    FSOUND_CD_SetPlayMode(0, mode);
}

void AudioSystem::setCDPlayMode(char drive, signed char mode)
{
    FSOUND_CD_SetPlayMode(drive, mode);
}

bool AudioSystem::setCDTrackTime(unsigned int ms)
{
    return FSOUND_CD_SetTrackTime(0, ms);
}

bool AudioSystem::setCDTrackTime(char drive, unsigned int ms)
{
    return FSOUND_CD_SetTrackTime(drive, ms);
}

bool AudioSystem::setCDVolume(int volume)
{
    return FSOUND_CD_SetVolume(0, volume);
}

bool AudioSystem::setCDVolume(char drive, int volume)
{
    return FSOUND_CD_SetVolume(drive, volume);
}

bool AudioSystem::stopCD()
{
    return FSOUND_CD_Stop(0);
}

bool AudioSystem::stopCD(char drive)
{
    return FSOUND_CD_Stop(drive);
}

void AudioSystem::addDSPEffect(std::string name, IDSPEffect* pDSPEffect)
{
    // Validate Incoming DSP Effect Pointer
    if (pDSPEffect == 0)
        return;
    // Try and Find the DSP Effect
    std::map<std::string, IDSPEffect*>::iterator i = this->dspEffects.find(name);
    // if there is already an effect with this name then return
    if (i != this->dspEffects.end())
        return;
    // Add the DSP Effect to the Map
    this->dspEffects[name] = pDSPEffect;
}

IDSPEffect* AudioSystem::getDSPEffect(std::string name)
{
    // Try and Find the DSP Effect
    std::map<std::string, IDSPEffect*>::iterator i = this->dspEffects.find(name);
    // If we didn't find it then return a null pointer
    if (i == this->dspEffects.end())
        return 0;
    // Return the DSP Effect
    return (IDSPEffect*)i->second;
}

void AudioSystem::removeDSPEffect(std::string name)
{
    // Try and Find the DSP Effect
    std::map<std::string, IDSPEffect*>::iterator i = this->dspEffects.find(name);
    // If we didn't find it then return a null pointer
    if (i == this->dspEffects.end())
        return;
    // Grab the DSP Effect
    IDSPEffect* pDSPEffect = (IDSPEffect*) i->second;
    // Deactive the DSP Effect
    pDSPEffect->deactivate();
    // Destroy the DSP Effect
    pDSPEffect->destroy();
    // Remove the dspEffect from our Map
    this->dspEffects.erase(i);
    // Delete the DSPEffect
    delete pDSPEffect;
}

void AudioSystem::enableDSPEffect(std::string name)
{
    // Try and Find the DSP Effect
    std::map<std::string, IDSPEffect*>::iterator i = this->dspEffects.find(name);
    // If we didn't find it then return a null pointer
    if (i == this->dspEffects.end())
        return;
    // Grab the DSP Effect
    IDSPEffect* pDSPEffect = (IDSPEffect*) i->second;
    // Enable DSPEffect
    pDSPEffect->activate();
}

void AudioSystem::disableDSPEffect(std::string name)
{
    // Try and Find the DSP Effect
    std::map<std::string, IDSPEffect*>::iterator i = this->dspEffects.find(name);
    // If we didn't find it then return a null pointer
    if (i == this->dspEffects.end())
        return;
    // Grab the DSP Effect
    IDSPEffect* pDSPEffect = (IDSPEffect*) i->second;
    // Deactivate DSPEffect
    pDSPEffect->deactivate();
}

void AudioSystem::freeDSPEffects()
{
    // Go through all the DSP Effects
    for (std::map<std::string, IDSPEffect*>::iterator i = this->dspEffects.begin(); i != this->dspEffects.end(); i++)
    {
        // Grab the DSP Effect
        IDSPEffect* pDSPEffect = (IDSPEffect*) i->second;
        // Deactivate DSPEffect
        pDSPEffect->deactivate();
        // Destroy the DSP Effect
        pDSPEffect->destroy();
        // Delete DSP Effect
        delete pDSPEffect;
    }
    // Empty DSPEffects Map
    this->dspEffects.clear();
}

int AudioSystem::getRecordingDriverID()
{
    return FSOUND_Record_GetDriver();
}

const char* AudioSystem::getRecordingDriverName(int recordingDriverID)
{
    return FSOUND_Record_GetDriverName(recordingDriverID);
}

int AudioSystem::getRecordingDriverCount()
{
    return FSOUND_Record_GetNumDrivers();
}

int AudioSystem::getRecordingPosition()
{
    return FSOUND_Record_GetPosition();
}

bool AudioSystem::setRecordingDriver(int recordingDriverID)
{
    return FSOUND_Record_SetDriver(recordingDriverID);
}

bool AudioSystem::startRecording(FSOUND_SAMPLE* pFMODSoundSample)
{
    return FSOUND_Record_StartSample(pFMODSoundSample, false);
}

bool AudioSystem::stopRecording()
{
    return FSOUND_Record_Stop();
}

void AudioSystem::bindToLua(lua_State* pLuaState)
{
    // TODO: More bindings
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        luabind::class_<AudioSystem>("AudioSystem")
        .def(luabind::constructor<>())
//        // REVERB
//        .def("reverbOff", (void(AudioSystem::*)()) &AudioSystem::reverbOff)
//        .def("reverbGeneric", (void(AudioSystem::*)()) &AudioSystem::reverbGeneric)
//        .def("reverbPaddedCell", (void(AudioSystem::*)()) &AudioSystem::reverbPaddedCell)
//        .def("reverbRoom", (void(AudioSystem::*)()) &AudioSystem::reverbRoom)
//        .def("reverbBathRoom", (void(AudioSystem::*)()) &AudioSystem::reverbBathRoom)
//        .def("reverbLivingRoom", (void(AudioSystem::*)()) &AudioSystem::reverbLivingRoom)
//        .def("reverbStoneRoom", (void(AudioSystem::*)()) &AudioSystem::reverbStoneRoom)
//        .def("reverbAuditorium", (void(AudioSystem::*)()) &AudioSystem::reverbAuditorium)
//        .def("reverbConcertHall", (void(AudioSystem::*)()) &AudioSystem::reverbConcertHall)
//        .def("reverbCave", (void(AudioSystem::*)()) &AudioSystem::reverbCave)
//        .def("reverbArena", (void(AudioSystem::*)()) &AudioSystem::reverbArena)
//        .def("reverbHanger", (void(AudioSystem::*)()) &AudioSystem::reverbHanger)
//        .def("reverbCarpetedHallway", (void(AudioSystem::*)()) &AudioSystem::reverbCarpetedHallway)
//        .def("reverbHallway", (void(AudioSystem::*)()) &AudioSystem::reverbHallway)
//        .def("reverbCorridor", (void(AudioSystem::*)()) &AudioSystem::reverbCorridor)
//        .def("reverbAlley", (void(AudioSystem::*)()) &AudioSystem::reverbAlley)
//        .def("reverbForest", (void(AudioSystem::*)()) &AudioSystem::reverbForest)
//        .def("reverbCity", (void(AudioSystem::*)()) &AudioSystem::reverbCity)
//        .def("reverbMountains", (void(AudioSystem::*)()) &AudioSystem::reverbMountains)
//        .def("reverbQuarry", (void(AudioSystem::*)()) &AudioSystem::reverbQuarry)
//        .def("reverbPlain", (void(AudioSystem::*)()) &AudioSystem::reverbPlain)
//        .def("reverbParkingLot", (void(AudioSystem::*)()) &AudioSystem::reverbParkingLot)
//        .def("reverbSewerPipe", (void(AudioSystem::*)()) &AudioSystem::reverbSewerPipe)
//        .def("reverbUnderWater", (void(AudioSystem::*)()) &AudioSystem::reverbUnderWater)
//        .def("reverbDrugged", (void(AudioSystem::*)()) &AudioSystem::reverbDrugged)
//        .def("reverbDizzy", (void(AudioSystem::*)()) &AudioSystem::reverbDizzy)
//        .def("reverbPsychotic", (void(AudioSystem::*)()) &AudioSystem::reverbPsychotic)
    ];
}
