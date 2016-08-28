/**
  * @file   Stream.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Stream provides the ability to load and buffer
  * audio files in real-time so that an entire file
  * need not be loaded. This massively decreases load time
*/

#ifndef STREAM_H
#define STREAM_H

// C++ Includes
#include <iostream>

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

// GameAudio Includes
#include "FMODGlobals.h"

/* TODO: There is a little confusion in the interface here about the difference between channel functions and stream functions
    in FMOD there is overlap where changing a stream option will also automatically affect the properties of a channel its playing on.
    Things like the looping function, isLooping should this query the channel or should this query the stream mode?
    The above sentence is a the heart of the problem */
/** @class Stream
  * @brief The Stream class is a positional stream
  * @detail The Stream class is a container for an instance of an FSOUND_Stream. Streaming audio means we load, decompress and decode the sound
  * in real-time. Although more cpu intensive this allows sound and music to play without any load times. **/
class Stream
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        Stream()
        {
//            this->playingFlag = false; // Not playing
            this->pausedFlag = false; // Not paused
            this->loopFlag = false; // No Loop Flag for Streams
            this->loopCount = -1; // If loopingFlag set to true the default loop count in infinitiy
            this->muteFlag = false; // No Mute Flag for Streams
            this->pan = 128; // Middle Balance
            this->volume = 255; // Max volume
            this->absoluteVolume = 255; // Max absolute volume
            this->surroundFlag = false; // A surroundSound is a flag non positional sound so we assume non surround here
            this->priority = 0; // Mid range priority
            //this->reserved = false;
            this->pFMODSoundStream = 0;
            this->filename.clear();
            this->name.clear();
            this->channel = FSOUND_FREE;
        }
        //! Destructor
        virtual ~Stream()
        {
            // Unreserve the Channel
            if (FSOUND_GetReserved(this->channel) == true)
            {
                FSOUND_SetReserved(this->channel, false);
                this->channel = FSOUND_FREE;
                //this->reserved = false;
            }
        }

    protected:
        //! Stream Copy constructor
        Stream(const Stream& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! Stream Assignment operator
        Stream& operator=(const Stream& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        /** @brief Load Stream
          * @param filename filename to load
          * @return true on success false on failure **/
        virtual bool load(std::string filename);
        /** @brief Think **/
        virtual void think();
        /** @brief Update
          * @param dTime difference between the last frame and this frame **/
        virtual void update(float dTime);
        /** @brief Clear **/
        virtual void clear();
        /** @brief free the stream **/
        virtual void free();

    // PLAYBACK
    public:
        /** @brief Is this sound still playing?
          * @return true if stream is playing false otherwise **/
        virtual bool isPlaying();
        /** @brief Play Stream **/
        virtual void play();
        /** @bief Play StreamEx (stream starts paused) **/
        virtual void playEx();
        /** @brief Start **/
        virtual void start();
        /** @brief Stop Stream **/
        virtual void stop();
        /** @brief Reset Stream **/
        virtual void reset();
        /** @brief Is Paused?
          * @return true if paused false otherwise **/
        virtual bool isPaused();
        /** @brief Set Paused
          * @param true to pause, false to resume **/
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
        /** @brief Get loop mode
          * @return true if looping false otherwise **/
        virtual bool isLoop();
        /** @brief Set loop (turn looping on)
          * @param loopflag true to make loop false to turn looping off **/
        void setLoop(bool loopFlag);
        /** @brief Set the streams loop count
        /** @param count if this is not called or parameter is < 0 then the stream loops forever **/
        void setLoopCount(int count);

    protected:
        // Loop Flag
        bool loopFlag;
        // Loop Count
        int loopCount;

    // ********************************
    // * VOLUME AND BALANCE FUNCTIONS *
    // ********************************
    public:
        /** @brief Get Volume
          * @return volume (0 silent 255 full) **/
        virtual int getVolume();
        /** @brief Set Volume
          * @param volume (0 silent 255 full) **/
        virtual void setVolume(int volume);
        /** @brief Set Volume Absolute
          * @param absoluteVolume **/
        virtual void setVolumeAbsolute(int absoluteVolume);
        /** @brief Get Pan
          * @return Pan (0 full left 255 full right) **/
        virtual int getPan();
        /** @brief Set Pan (Balance)
          * @param pan (0 full left 255 full right) **/
        virtual void setPan(int pan);
        /** @brief Is surround
          * @return true if surround otherwise false **/
        virtual bool isSurround();
        /** @brief Set Surround
          * @param surroundFlag **/
        virtual void setSurround(bool surroundFlag);
        // 888888888888888888888 NOTE: To the best of my knowledge these functions don't work on streams
        /** @brief Is mute?
          * @return true if is muted otherwise false **/
        virtual bool isMute();
        /** @brief Set mute for this sound
          * @return state true to mute false to unmute **/
        virtual void setMute(bool state);
        /** @brief Mute this sound **/
        virtual void mute();
        /** @brief Unmute this sound **/
        virtual void unmute();
        // 888888888888888888888

    protected:
        //// Mute Flag
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
          * @return priority 0 highest 255 lowest) **/
        virtual int getPriority();
        /** @brief Set Priority
          * @param priority **/
        virtual void setPriority(int priority);
        /** @brief Is Reserved
          * @return true if reserved otherwise false **/
        virtual bool isReserved();
        /** @brief Set Reserved
          * @value true if to be reserved otherwise false **/
        virtual void setReserved(bool value);

    protected:
        // Priority
        int priority;

    // *************************************
    // * FREQUENCY AND AMPLITUDE FUNCTIONS *
    // *************************************
    public:
        /** @brief Get the frequency
          * @return frequency **/
        virtual int getFrequency();
        /** @brief Set the frequency
          * @param value **/
        virtual void setFrequency(int value);
        /** @brief Get Amplitude
          * @return amplitude **/
        virtual int getAmplitude();
        /** @brief Set current position
          * @param value postion in samples **/
        virtual void setCurrentPosition(unsigned int value);
        /** @brief Get current position
          * @return current position in samples **/
        virtual unsigned int getCurrentPosition();
        /** @brief Get current sample
          * @return current sample as a pointer to an FSOUND_SAMPLE **/
        virtual FSOUND_SAMPLE* getCurrentSample();
        /* Excluded: FSOUND_GetCurrentLevels
            Reason: complex and obscure return information */

    // MISC ???
    public:
        /** @brief Get number of sub channels
          * @return sub channel count **/
        virtual int getSubChannelCount();
        /* Excluded FSOUND_GetSubChannel
            reason: ?*/

    // ********************
    // * STREAM FUNCTIONS *
    // ********************
    public:
        /** @brief Get the Stream Length in Bytes
          * @return length in bytes **/
        virtual int getLength();
        /** @brief Get the Stream Length
          * @return length in Miliseconds **/
        virtual int getLengthMs();
        //TODO: document better
        /** @brief Get Mode Stream Mode
          * @return mode **/
        //TODO: document better
        virtual unsigned int getMode();
        /** @brief Set the streams modes
          * @param mode **/
        virtual void setMode(unsigned int mode);
        /** @brief Get the OpenState
          * @return 0 = stream is opened and ready.
            -1 = stream handle passed in is invalid.
            -2 = stream is still opening or performing a SetSubStream command.
            -3 = stream failed to open. (file not found, out of memory or other error).
            -4 = connecting to remote host (internet streams only)
            -5 = stream is buffering data (internet streams only) **/
        virtual int getOpenState();
        /** @brief Get Stream Position
          * @return the current FILE position of the stream of the stream in BYTES **/
        virtual unsigned int getStreamPosition();
        /** @brief Set the stream position in Bytes
          * @param position set the positoin of the stream in bytes **/
        virtual void setStreamPosition(unsigned int position);
        /** @brief Get the sample for the stream
          * @param FSOUND_SAMPLE **/
        virtual FSOUND_SAMPLE* getSample();
        /** @brief Get Time
          * @return the current time offset in stream in milliseconds. **/
        virtual int getTime();
        /** @brief Set Stream Time
          * @param ms in miliseconds (seeking) **/
        virtual void setTime(int ms);
        /** @brief Seek to a substream inside an FSB bank file
          * @param index **/
        virtual void setSubStream(int index);
        /** @brief Describe the playback order for the list of substreams (FSB bank file)
          * @param sentenceList an array of ints
          * @param numItems number of items in our sentence **/
        virtual void setSubStreamSentence(const int* sentenceList, int numItems);
        /** @brief Get the number of substreams
          * @return number of sub streams **/
        virtual int getSubStreamCount();

    // ******************************
    // * FMOD SOUNDSTREAM FUNCTIONS *
    // ******************************
    public:
        /** @brief Get the SoundStream (aquired from load method)
          * @return pointer the the FSOUND_STREAM **/
        virtual FSOUND_STREAM* getFMODSoundStream() { return this->pFMODSoundStream; }

    protected:
        // A pointer to the FSOUND_STREAM
        FSOUND_STREAM* pFMODSoundStream;

    // ************
    // * FILENAME *
    // ************
    public:
        /** @brief Get filename
          * @return filename **/
        virtual std::string getFilename() { return this->filename; }

    protected:
        // Sound filename
        std::string filename;

    // CHANNEL
    protected:
        // The playback channel
        int channel;

    // ******************
    // * FMOD CALLBACKS *
    // ******************
    public:
        /** @brief End of Stream Callback FSOUND_STREAMCALLBACK
          * @param pFMODStream a pointer to the incoming stream
          * @param buff a pointer to the buffer to fill
          * @param len in bytes
          * @param pUserData a pointer to user data (usually a StreamObject) **/
        static signed char F_CALLBACKAPI streamEndCallBackRouter(FSOUND_STREAM* pFMODStream, void* buff, int len, void* pUserdata);

    // ***********
    // * ENABLED * // TODO: This needs to actually effect the Stream at the moment it doesn't
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

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        /** @brief Bind this class to a lua state
          * @param pLuaState The LuaState to bind this class to **/
        static void bindToLua(lua_State* pLuaState);
};

#endif // STREAM_H

        /* TODO: EXCLUDED STREAM FUNCTIONS
            FSOUND_Stream_AddSyncPoint - requires callbacks
            FSOUND_Stream_Close - handled by the content manager
            FSOUND_Stream_Create - requires callbacks and not neccessary to our purpose
            FSOUND_Stream_CreateDSP - requires callbacks (DSP Only supported WIN32)
            FSOUND_Stream_DeleteSyncPoint - function related to callbacks
            FSOUND_Stream_FindTagField - exlcuded for now not sure what it does
            FSOUND_Stream_GetNumSyncPoints - requires callbacks
            FSOUND_Stream_GetNumTagFields - exlcuded for now not sure what it does
            FSOUND_Stream_GetSyncPoint - requires callbacks
            FSOUND_Stream_GetSyncPointInfo - requires callbacks
            FSOUND_Stream_GetTagField - exlcuded for now not sure what it does
            FSOUND_Stream_Net_GetBufferProperties - excluded for now complex return types
            FSOUND_Stream_Net_GetLastServerStatus - excluded no net support yet
            FSOUND_Stream_Net_GetStatus - excluded no net support yet
            FSOUND_Stream_Net_SetBufferProperties - excluded no net support yet
            FSOUND_Stream_Net_SetMetadataCallback - excluded no net support yet
            FSOUND_Stream_Net_SetProxy - excluded no net support yet
            FSOUND_Stream_SetBufferSize - Doesn't seem applicable
            FSOUND_Stream_SetEndCallback - requires callbacks
            FSOUND_Stream_SetLoopPoints - Excluding doesn't seem to apply
            FSOUND_Stream_SetSyncCallback - requires callbacks*/
