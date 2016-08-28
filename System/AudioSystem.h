/**
  * @file   AudioSystem.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  AudioSystem is a simple wrapper around the FMOD Audio System
  * and provides basic services like initialisation, shutdown, update
  * pause, resume, volume, DSP Effect management and listener position
*/

#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

// C++ Includes
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>

// FMOD Includes
#include <fmod.h>
#include <fmod_errors.h>

// LUA AND LUABIND Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// GAMEAUDIO Includes
#include "FMODGlobals.h"
#include "SoundSample.h"
#include "Sound.h"
#include "Sound2D.h"
#include "Sound3D.h"
#include "Stream.h"
#include "Stream2D.h"
#include "Stream3D.h"
#include "Music.h"
#include "IDSPEffect.h"

/** @class AudioSystem
  * @brief The AudioSystem class is the core of the Sound Wrapper
  * @detail The AudioSystem class intialises and shutdowns the audio system along with
    setting important things like volume, balance, allowing you to mute audio,
    get important information about the driver, record audio, play cds and
    add DSP (Digital Signal Processing) to the Audio Pipeline (for effects like
    echo) **/

/**  **/
class AudioSystem
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default constructor
        AudioSystem()
        {
            // WasInit
            this->wasInitFlag = false;
            // SoundEffectsVolume
            this->soundEffectsVolume = 255;
            // MusicVolume
            this->musicVolume = 255;
            // Frequency
            this->frequency = 44100;
        }
        //! Destructor
        virtual ~AudioSystem() {}

    protected:
        //! Copy constructor
        AudioSystem(const AudioSystem& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Methods and members

    protected:
        //! Assignment operator
        AudioSystem& operator=(const AudioSystem& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        /** @brief Start the audio system
          * @param frequency frequency to init the audiodevice with
          * @param maxChannels the maximum number of channels for the audio system
          * to use **/
        virtual bool init(int frequency, int maxChannels);
        /** @brief Think **/
        virtual void think();
        /** @brief Advance to the next audio frame
          * @param dTime difference between this frame and the last frame **/
        virtual void update(float dTime);
        /** @brief shutdown **/
        virtual void shutdown();
        /** @wasInit Has the audio system been initialised
          * @return true on was initialised otherwise false **/
        virtual bool wasInit() { return this->wasInitFlag; }

    protected:
        // has the system been initialised
        bool wasInitFlag;

    // **********************
    // * LISTENER FUNCTIONS *
    // **********************
    public:
        /** @brief get ListernerX
          * @return Listerner X **/
        virtual float getListenerX();
        /** @brief get ListernerY
          * @return Listerner Y **/
        virtual float getListenerY();
        /** @brief get ListernerZ
          * @return Listerner Z **/
        virtual float getListenerZ();
        /** @brief Set the listeners position
          * @param x x position of the listener
          * @param y y position of the listener **/
        virtual void setListener(float x, float y);
        /** @brief Set the listeners position
          * @param x x position of the listener
          * @param y y position of the listener
          * @param z z position of the listener
          * @param xVelocity xVelocity position of the listener
          * @param yVelocity yVelocity position of the listener
          * @param zVelocity zVelocity position of the listener
          * @param upX upX position of the listener
          * @param upY upY position of the listener
          * @param upZ upZ position of the listener **/
        virtual void setListener(float x, float y, float z, float xVelocity, float yVelocity, float zVelocity, float xForward, float yForward, float zForward, float upX, float upY, float upZ);

    // *********************************
    // * PAUSE, RESUME, STOP FUNCTIONS *
    // *********************************
    public:
        /** @brief Pause the audiosystem **/
        virtual void pause();
        /** @brief Resume the audiosystem **/
        virtual void resume();
        /** @brief Stop the audiosystem **/
        virtual void stop();

    // **********
    // * VOLUME *
    // **********
    public:
        /** @brief Get the sound effects volume
          * @return Sound Effects Volume  in range 0 - 128 **/
        virtual unsigned int getSoundEffectsVolume();
        /** @brief Set the sound effects volume
          * @param volume in range 0 - 128 **/
        virtual void setSoundEffectsVolume(int volume);
        /** @brief Get the music volume
          * @return volume in range 0 - 128 **/
        virtual unsigned int getMusicVolume();
        /** @brief Set the music volume
          * @param volume In range 0 - 128 **/
        virtual void setMusicVolume(int volume);
        /** @brief Is the AudioSystem muted
          * @return true if mute otherwise false **/
        virtual bool isMute() { return FMODGlobals::muteFlag; }
        /** @brief Set MuteState for the AudioSystem
          * @param state true to mute, false to unmute **/
        virtual void setMute(bool state);
        /** @brief Mute the AudioSystem **/
        virtual void mute();
        /** @brief Unmute the AudioSystem **/
        virtual void unmute();

    protected:
        // Sound Effects Volume
        int soundEffectsVolume;
        // Music Volume
        int musicVolume;

    // ***********************************************************
    // * STEREO, MONO, BALANCE, REVERB(only works on midi files) *
    // ***********************************************************
    public:
        /** @brief Make Speakers Mono **/
        virtual void monoSpeakers();
        /** @brief Make Speakers Stereo **/
        virtual void stereoSpeakers();
        /** @brief Set the stereo Balance
          * @param value 0 for full left pan, 128 for centre and 255 for full right **/
        virtual void setStereoBalance(int value);
        // NOTE: Support removed because it only works for midifiles
        ////** @briefSet Reverb for MidiFiles only
        //   * @param state true to apply reverb otherwise false **/
        //virtual void setReverb(bool state) { (state == true) ? FMUSIC_SetReverb(true) : FMUSIC_SetReverb(false); }

    // *************************
    // * INFORMATION FUNCTIONS *
    // *************************
    public:
        // TODO: document this better
        /** @brief get the version information
          * @return the version **/
        virtual float getVersion();
        /** @brief How much processing power is audio taking
          * @return CPU Usage **/
        virtual float getCPUUsage();
        /** @brief Get how many channels are currently playing
          * @return number of channels in use **/
        virtual int getChannelsPlaying();
        // TODO: better documentation
        /** @brief Get the ID for the currently selected driver
          * @return ID of the current driver in use **/
        virtual int getDriver();
        /** @brief Get the Driver capabilites for a driver by ID
          * @param driverID the driverID we want the capabilities for
          * @return the driver capabilites as a string **/
        virtual std::string getDriverCapabilities(int driverID);
        /** @brief Get the Driver name for a driver by ID
          * @param driverID the driverID we want the name for
          * @return driver name as a string **/
        virtual std::string getDriverName(int driverID);
        /** @brief Get the current maximum index for a sample
          * @return maxSamples **/
        virtual int getMaxSamples();
        /** @brief Get the Frequency of the AudioSystem
          * @return frequency of the AudioSystem **/
        virtual int getFrequency();
        /** @brief Get the MaxSoftware Channels
          * @return max software channels **/
        virtual int getMaxSoftwareChannels();
        /** @brief Get the maximum number of channels allocated
          * @return max channels allocated **/
        virtual int getMaxChannels();
        /** @brief Get Memory Statistics
          * @return memory statistics as a string **/
        virtual std::string getMemoryStatistics();
        /** @brief Get the number of drivers
          * @return number of drivers **/
        virtual int getDrivers();
        /** @brief Get the number of available hardware channels
          * @return number of hardware channels **/
        virtual signed char getNumHWChannels();
        // TODO: rename this function
        /** @brief Get the ID for the current output device
          * @return ID of the Output Device **/
        virtual int getOutput();
        /** @brief Get a Handle to the output device
          * @return void* (DirectSound, WinMM, etc) **/
        virtual void* getOutputHandle();
        /** @brief Get the mixing rate
          * @return output rate **/
        virtual int getOutputRate();

    protected:
        // frequency
        int frequency;
        // max Software Channels
        int maxSoftwareChannels;

    // ****************
    // * CD FUNCTIONS *
    // ****************
    public:
        /** @brief Get the Number of tracks on the Compact Disc
          * @return number of cd tracks **/
        virtual int getNumberOfCDTracks();
        /** @brief Get the Number of tracks on the Compact Disc
          * @param drive drive to get number of cd tracks
          * @return number of cd tracks on drive **/
        virtual int getNumberOfCDTracks(char drive);
        /** @brief Get the Pause Status of the current CD Audio Track
          * @return true if cd is paused otherwise false **/
        virtual bool isCDPaused();
        /** @brief Get the Pause Status of the current CD Audio Track
          * @param drive compact disc drive letter as char
          * @return true if cd is paused otherwise false **/
        virtual bool isCDPaused(char drive);
        /** @brief Get the currently playing CD Track Number
          * @return int get Current CD Track **/
        virtual int getCDTrack();
        /** @brief Get the currently playing CD Track Number
          * @param drive compact disc drive letter as char
          * @return the track number on the compact disk drive playing */
        virtual int getCDTrack(char drive);
        /** @brief Get the length of a track on a drive **/
        virtual int getCDTrackLength(int track);
        /** @brief Get the length of a track on a drive **/
        virtual int getCDTrackLength(char drive, int track);
        /** @brief Get Track Time of a currently playing track **/
        virtual int getCDTrackTime();
        /** @brief Get Track Time of a currently playing track **/
        virtual int getCDTrackTime(char drive);
        /** @brief Get Volume (0 min - 255 max) **/
        virtual int getCDVolume();
        /** @brief Get Volume (0 min - 255 max) **/
        virtual int getCDVolume(char drive);
        /** @brief Open the CD Tray of a drive **/
        virtual bool openCDTray();
        /** @brief Open the CD Tray of a drive **/
        virtual bool openCDTray(char drive);
        /** @brief Close the CD Tray of a drive **/
        virtual bool closeCDTray();
        /** @brief Close the CD Tray of a drive **/
        virtual bool closeCDTray(char drive);
        /** @brief Play CD **/
        virtual bool playCD();
        /** @brief Play CD **/
        virtual bool playCD(char drive);
        /** @brief Play CD and track  **/
        virtual bool playCDTrack(int track);
        /** @brief Play CD and track  **/
        virtual bool playCDTrack(char drive, int track);
        /** @brief Pause a CD that is playing  **/
        virtual bool pauseCD();
        /** @brief Pause a CD that is playing  **/
        virtual bool pauseCD(char drive);
        /** @brief Resume a CD that was playing but was paused
          * @return true if successfule otherwise false **/
        virtual bool resumeCD();
        /** @brief Resume a CD that was playing but was paused
          * @param drive the drive to resume
          * @return true if successfule otherwise false **/
        virtual bool resumeCD(char drive);
        /** @brief Set CD PlayMode
          * @param mode use the binary or operator to concatenate values from FSOUND_CDPLAYMODES i.e. a | b | c **/
        virtual void setCDPlayMode(signed char mode);
        /** @brief Set CD PlayMode
          * @param drive drive to set playmode for
          * @param mode use the binary or operator to concatenate values from FSOUND_CDPLAYMODES i.e. a | b | c **/
        virtual void setCDPlayMode(char drive, signed char mode);
        /** @brief Set Track Time  **/
        virtual bool setCDTrackTime(unsigned int ms);
        /** @brief Set Track Time  **/
        virtual bool setCDTrackTime(char drive, unsigned int ms);
        /** @brief Set the CD Volume (0 min - 255 max)
        **/
        virtual bool setCDVolume(int volume);
        /** @brief Set the CD Volume (0 min - 255 max)
        **/

        virtual bool setCDVolume(char drive, int volume);
        /** @brief Stop CD
          * @return true on success otherwise false **/
        virtual bool stopCD();
        /** @brief Stop CD
          * @return true on success otherwise false **/
        virtual bool stopCD(char drive);

    // *****************
    // * DSP FUNCTIONS *
    // *****************
    // TODO: Need to implement this aspect of the AudioSystem
    public:
        /** @brief Add DSP Effect by name
          * @param name name of the DSP effect
          * @param pDSPEffect A pointer to an instance of a DSPEffect **/
        virtual void addDSPEffect(std::string name, IDSPEffect* pDSPEffect);
        /** @brief Get DSP Effect by name
          * @param name name of the DSP effect **/
        virtual IDSPEffect* getDSPEffect(std::string name);
        /** @brief Remove DSP Effect by name
          * @param name name of the DSP effect **/
        virtual void removeDSPEffect(std::string name);
        /** @brief EnableDSP Effect by name
          * @param name name of the DSP effect **/
        virtual void enableDSPEffect(std::string name);
        /** @brief Disable DSP Effect by name
          * @param name name of the DSP effect**/
        virtual void disableDSPEffect(std::string name);
        /** @brief Free DSP Effects **/
        virtual void freeDSPEffects();

    protected:
        // DSP Effects Map
        std::map<std::string, IDSPEffect*> dspEffects;

    // *************
    // * RECORDING *
    // *************
    public:
        /** @brief Get the recording driver
          * @return ID of the recording driver **/
        virtual int getRecordingDriverID();
        /** @brief Get the recording driver name
          * @return name of the recording driver associated with this ID**/
        virtual const char* getRecordingDriverName(int recordingDriverID);
        /** @brief Get the number of recording drivers
          * @return number of recording drivers **/
        virtual int getRecordingDriverCount();
        // TODO: Document better
        /** @brief Get the position in the sample buffer that has been recorded to
          * @return recording positiont **/
        virtual int getRecordingPosition();
        // TODO: Document better
        /** @brief Set the recording driver to use
          * @param recordingDriverID ID of the recording driver **/
        virtual bool setRecordingDriver(int recordingDriverID);
        /** @brief Start recording into a sample
          * @return true if successful false otherwise **/
        virtual bool startRecording(FSOUND_SAMPLE* pFMODSoundSample);
        /** @brief Stop recording
          * @return true if successful, false otherwise **/
        virtual bool stopRecording();

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        /** @brief Bind this class to a lua state
          * @param pLuaState The LuaState to bind this class to **/
        static void bindToLua(lua_State* pLuaState);
};

#endif // AUDIOSYSTEM_H

/* NOTE: This code was cut out because there is no cross platform support for it*/
//    // REVERB
//    public:
//        //! Get Reverb Properties
//        virtual FSOUND_REVERB_PROPERTIES getReverbProperties()
//        {
//            FSOUND_REVERB_PROPERTIES reverbProperties;
//            FSOUND_Reverb_GetProperties(&reverbProperties);
//            return reverbProperties;
//        }
//        //! Set Reverb Properties
//        virtual void setReverbProperties(FSOUND_REVERB_PROPERTIES reverbProperties)
//        {
//            FSOUND_Reverb_SetProperties(&reverbProperties);
//        }
//        //! Get Reverb Channel Properties
//        virtual FSOUND_REVERB_CHANNELPROPERTIES getReverbChannelProperties(int channel)
//        {
//            FSOUND_REVERB_CHANNELPROPERTIES reverbChannelProperties;
//            FSOUND_Reverb_GetChannelProperties(channel, &reverbChannelProperties);
//            return reverbChannelProperties;
//        }
//        //! Set Reverb Channel Properties
//        virtual void setReverbChannelProperties(int channel, FSOUND_REVERB_CHANNELPROPERTIES reverbChannelProperties)
//        {
//            FSOUND_Reverb_SetChannelProperties(channel, &reverbChannelProperties);
//        }

//    // REVERB PRESETS
//    // NOTE: Removed because reverb is only supported for  Win32(DirectX8), XBox(DirectX - prior to xna), PlayStation 2(playstation sound api)
//    public:
//        //! Turn Reverb Off
//        virtual void reverbOff()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_OFF;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Generic
//        virtual void reverbGeneric()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_GENERIC;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb PaddedCell
//        virtual void reverbPaddedCell()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_PADDEDCELL;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Room
//        virtual void reverbRoom()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_ROOM;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb BathRoom
//        virtual void reverbBathRoom()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_BATHROOM;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb BathLivingRoom
//        virtual void reverbLivingRoom()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_LIVINGROOM;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb StoneRoom
//        virtual void reverbStoneRoom()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_STONEROOM;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Auditorium
//        virtual void reverbAuditorium()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_AUDITORIUM;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb ConcertHall
//        virtual void reverbConcertHall()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_CONCERTHALL;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Cave
//        virtual void reverbCave()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_CAVE;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Arena
//        virtual void reverbArena()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_ARENA;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Hanger
//        virtual void reverbHanger()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_HANGAR;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Carpeted Hallway
//        virtual void reverbCarpetedHallway()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_CARPETTEDHALLWAY;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Hallway
//        virtual void reverbHallway()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_HALLWAY;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Stone Corridor
//        virtual void reverbCorridor()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_STONECORRIDOR;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Stone Alley
//        virtual void reverbAlley()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_ALLEY;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Forest
//        virtual void reverbForest()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_FOREST;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb City
//        virtual void reverbCity()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_CITY;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Mountains
//        virtual void reverbMountains()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_MOUNTAINS;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Quarry
//        virtual void reverbQuarry()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_QUARRY;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Plain
//        virtual void reverbPlain()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_PLAIN;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb ParkingLot
//        virtual void reverbParkingLot()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_PARKINGLOT;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb SewerPipe
//        virtual void reverbSewerPipe()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_SEWERPIPE;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb UnderWater
//        virtual void reverbUnderWater()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_UNDERWATER;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Drugged
//        virtual void reverbDrugged()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_DRUGGED;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Dizzy
//        virtual void reverbDizzy()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_DIZZY;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
//        //! Reverb Psychotic
//        virtual void reverbPsychotic()
//        {
//            // Make a Reverb Properties Structure
//            FSOUND_REVERB_PROPERTIES prop = FSOUND_PRESET_PSYCHOTIC;
//            // Set the Reverb Properties
//            FSOUND_Reverb_SetProperties(&prop);
//        }
