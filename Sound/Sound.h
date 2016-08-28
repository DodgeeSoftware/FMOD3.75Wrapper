/**
  * @file   Sound.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Sound uses a SoundSample and a Channel to play audio
*/

#ifndef SOUND_H
#define SOUND_H

// C++ Includes
#include <iostream>

// FMOD Includes
#include <fmod.h>

// LUA Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
// LUABIND Includes
#include <luabind/luabind.hpp>

// GameAudio Includes
#include "FMODGlobals.h"
#include "Sound/SoundSample.h"

/** @class Sound
  * @brief Sound uses a SoundSample and a Channel to play audio
  * @detail The Sound class is used for a non-positional sound source and is effectively a wrapper around a reserved channel
        for an instance of Sound (which is referered to as a channel) **/
class Sound
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        Sound()
        {
//            this->playingFlag = false; // Not playing
            this->pausedFlag = false; // Not paused
            this->loopFlag = false; // Not looping
            this->muteFlag = false; // Not muted
            this->pan = 128; // Middle Balance
            this->volume = 255; // Max volume
            this->absoluteVolume = 255; // Max absolute volume
            this->surroundFlag = false; // A Sound is a flag non positional sound so we assume non surround here
            this->priority = 0; // Mid range priority
            //this->reserved = false;
            this->pSoundSample = 0; // Clear the soundsample pointer
            this->filename.clear();
            this->name.clear();
            this->channel = FSOUND_FREE; // Clear the channel
        }
        //! Destructor
        virtual ~Sound()
        {
            // Unreserve the Channel
            if (FSOUND_GetReserved(this->channel) == true)
            {
                FSOUND_SetReserved(this->channel, false);
                //this->reserved = false;
            }
        }

    protected:
        //! Sound Copy constructor
        Sound(const Sound& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! Sound Assignment operator
        Sound& operator=(const Sound& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        /** @brief Think **/
        virtual void think();
        /** @brief Update
          * @param dTime difference between last frame and this one **/
        virtual void update(float dTime);
        /** @brief Clear the sound **/
        virtual void clear();
        /** @brief Free **/
        virtual void free();

    // ************
    // * PLAYBACK *
    // ************
    public:
        /** @brief Is this sound still playing?
          * @return true if playing false otherwise **/
        virtual bool isPlaying()
        {
            /* TODO: What if the stream has stopped playing and another sound/stream is on the channel,
                we are going to get false results here, so we might need to fix this at some point */
            return FSOUND_IsPlaying(this->channel);
            //return this->playingFlag;
        }
        /** @brief Play the sound **/
        virtual void play();
        /** @brief Play the sound paused **/
        virtual void playEx();
        /** @brief Start **/
        virtual void start();
        /** @brief Stop the sound **/
        virtual void stop();
        /** @brief Restart **/
        virtual void reset();
        /** @briefIs Paused? **/
        virtual bool isPaused();
        /** @brief Set Paused **/
        virtual void setPaused(bool pausedFlag);
        /** @brief Pause Sound Playback **/
        virtual void pause();
        /** @brief Resume Sound Playback **/
        virtual void resume();

    protected:
//        // Playing Flag
//        bool playingFlag;
        // Paused Flag
        bool pausedFlag;

    // ***********
    // * LOOPING *
    // ***********
    public:
        /** @brief Set the loop mode
          * @param loopFlag **/
        virtual void setLoop(bool loopFlag);
        /** @brief Get loop mode
          * @return true if looping false otherwise **/
        virtual bool isLoop();

    protected:
        // Loop Flag
        bool loopFlag;

    // *********************
    // * PLAYBACK POSITION *
    // *********************
    public:
        /** @brief Get current position  (only works when sound is playing)
          * @return current position **/
        virtual unsigned int getCurrentPosition();
        // TODO: Document better
        /** @brief Set current position (only works when sound is playing)
          * @param value current position **/
        virtual void setCurrentPosition(unsigned int value);

    // ********************************
    // * VOLUME AND BALANCE FUNCTIONS *
    // ********************************
    public:
        /** @brief Is mute?
          * @return true if mute false otherwise **/
        virtual bool isMute();
        /** @brief Set Mute for this sound
          * @param muteFlag true to mute false to unmute **/
        virtual void setMute(bool muteFlag);
        /** @brief Mute this sound **/
        virtual void mute();
        /** @brief Unmute this sound **/
        virtual void unmute();
        /** @brief Get Pan
          * @return pan (0 full left 255 full right) **/
        virtual int getPan();
        /** @brief Set Pan (Balance)
          * @param pan (0 full left 255 full right) **/
        virtual void setPan(int pan);
        /** @brief Get Volume
          * @return volume (0 silent 255 fullblast) **/
        virtual int getVolume();
        /** @brief Set Volume
          * @param volume (0 silent 255 fullblast) **/
        virtual void setVolume(int volume);
        /** @brief Set Volume Absolute
          * @param absoluteVolume (0 silent 255 fullblast) **/
        virtual void setVolumeAbsolute(int absoluteVolume);
        /** @brief is surround
          * @return true if surround otherwise false **/
        virtual bool isSurround();
        /** @brief Get Surround
          * @return true if surround otherwise false **/
        virtual bool getSurround();
        /** @brief Set Surround
          * @param surroundFlag **/
        virtual void setSurround(bool surroundFlag);

    protected:
        // Mute Flag
        bool muteFlag;
        // Balance 128 equal 0 hard left 255 hard right
        int pan;
        // Volume 0 silent 255 full voltume
        int volume;
        // Absolute Volume 0 silent 255 full voltume
        int absoluteVolume;
        // Surround Flag
        bool surroundFlag;

    // **************************************
    // * PRIORITY AND RESERVATION FUNCTIONS *
    // **************************************
    public:
        /** @brief Get Priority
          * @return Priority (0 Highest priority, 255 lowest) **/
        virtual int getPriority();
        /** @brief Set Priority (0 Highest priority, 255 lowest)
          * @param priority (0 Highest priority, 255 lowest) **/
        virtual void setPriority(int priority);
        /** @brief Is Reserved
          * @return true if reserved false otherwise **/
        virtual bool isReserved();
        /** @brief Set Reserved
          * @param reserved **/
        virtual void setReserved(bool reserved);

    protected:
        // Priority
        int priority;
        // Is channel reserved?
        bool reserved;

    // *************************************
    // * FREQUENCY AND AMPLITUDE FUNCTIONS *
    // *************************************
    public:
        /** @brief Get the frequency
          * @return frequency **/
        virtual int getFrequency();
        /** @brief Set the frequency
          * @param frequency **/
        virtual void setFrequency(int frequency);
        /** @brief Get Amplitude
          * @return amplitude **/
        virtual int getAmplitude();
        /** @brief Get current sample playing on this Sounds channel
          * @return current sample **/
        virtual FSOUND_SAMPLE* getCurrentSample();
        /** @brief Get number of sub channels
          * @return sub channel count **/
        virtual int getSubChannelCount();
        /*  Excluded: FSOUND_GetSubChannel, FSOUND_GetCurrentLevels
            Reason: complex and obscure return information */

    // **************************
    // * SOUND SAMPLE FUNCTIONS *
    // **************************
    public:
        /** @brief Get the Sound Sample
          * @return SoundSample **/
        virtual SoundSample* getSoundSample();
        /** @brief Get the Sound Sample
          * @param pSoundSample pointer to a SoundSample **/
        virtual void setSoundSample(SoundSample* pSoundSample);

    protected:
        // The sound sample for this sound
        SoundSample* pSoundSample;

    // ***********
    // * ENABLED * // TODO: This needs to actually effect the Sound at the moment it doesn't
    // ***********
    public:
        /** @breif Is Enabled
          * @return true if is enabled false otherwise **/
        virtual bool isEnabled() { return this->enabledFlag; }
        /** @brief Set Enabled
          * @param state true to enable false to disable
        virtual void setEnabled(bool state) { this->enabledFlag = state; }
        /** @brief Enable the Sound **/
        virtual void enable() { this->enabledFlag = true; }
        /** @brief Disable the Sound **/
        virtual void disable() { this->enabledFlag = false; }

    protected:
        // Enabled Flag
        bool enabledFlag;

    // ********
    // * NAME *
    // ********
    public:
        /** @brief Get Name
          * @return name **/
        virtual std::string getName() { return this->name; }
        /** @brief Set Name
          * @param name **/
        virtual void setName(std::string name) { this->name = name; }
        /** @brief Is Named
          * @return true if named, false otherwise **/
        virtual bool isNamed() { return (this->name.size() > 0); }
        /** @brief Clear Name **/
        virtual void clearName() { this->name.clear(); }

    protected:
        // unique name
        std::string name;

    // **********************
    // * FILENAME FUNCTIONS * (TODO: I need to review this because I am duplicating functionality from the SoundSample Class)
    // **********************
    public:
        /** @brief Get filename
          * @return filename **/
        virtual std::string getFilename() { return this->filename; }
        /** @brief Set filename
          * @param filename the filename **/
        virtual void setFilename(const char* filename) { this->filename = filename; }

    protected:
        // Sound filename
        std::string filename;

    // THE CHANNEL THE SOUND IS PLAYING ON
    protected:
        // The playback channel
        int channel;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        /** @brief Bind this class to a lua state
          * @param pLuaState The LuaState to bind this class to **/
        static void bindToLua(lua_State* pLuaState);
};

#endif // SOUND_H
