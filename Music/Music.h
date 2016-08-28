/**
  * @file   Music.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Music streams a tracker file (xm, s3m, it, mod) from disk
*/

#ifndef MUSIC_H
#define MUSIC_H

// C++ Includes
#include <iostream>

// FMOD Includes
#include <fmod.h>
#include <fmod_errors.h>

// LUA Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
// LUABIND Includes
#include <luabind/luabind.hpp>

// GAMEAUDIO Includes
#include "FMODGlobals.h"

/** @class Music
    @brief The Music class is a container around a Music Module (tracker music)
    @detail Tracker music is 8bit - 16bit music and is usually in the format xm,
    s3m, mod, it etc **/
class Music
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        Music()
        {
            // Set the pointer to the song
            this->pFMODMusicModule = 0;
            // Clear the filename
            this->filename.clear();
            // Set the default volume
            this->volume = 255;
            // Set default mute flag
            this->muteFlag = false;
        }
        //! Destructor
        virtual ~Music()
        {
            // Free song if not already freed
            this->free();
        }

    protected:
        //! Copy constructor
        Music(const Music& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! Music Assignment operator
        Music& operator=(const Music& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        /** @brief Load a song
          * @param filename the location of the tracker file to load**/
        virtual bool load(std::string filename);
        /** @brief Play the song **/
        virtual void play();
        /** @brief Think **/
        virtual void think();
        /** @brief Update
          * @param dTime difference between last frame and this one **/
        virtual void update(float dTime);
        /** @brief Pause song playback **/
        virtual void pause();
        /** @brief Resume song playback **/
        virtual void resume();
        /** @brief Start the Song **/
        virtual void start();
        /** @brief Stop the song from playing **/
        virtual void stop();
        /** @brief Clear the song **/
        virtual void clear();
        /** @brief Free the song **/
        virtual void free();
        /** @brief Is finished playing
          * @return true if finished, false otherwise **/
        virtual bool isFinished();
        /** @brief Is playing
          * @return true if is playing false otherwise**/
        virtual bool isPlaying();
        /** @brief is Paused?
          * @return true if paused false otherwise **/
        virtual bool isPaused();

    // ********
    // * MUTE *
    // ********
    public:
        /** @brief Is Mute
          * @return true if mute otherwise false **/
        virtual bool isMute();
        /** @brief Mute **/
        virtual void mute();
        /** @brief Unmute **/
        virtual void unmute();

    protected:
        // Muteflag
        bool muteFlag;

    // *******************
    // * MUSIC FUNCTIONS *
    // *******************
    public:
        /** @brief Set Looping
          * @param state true to loop otherwise false **/
        virtual void setLooping(bool state);
        /** @brief Get Track Name
          * @return name of the track **/
        virtual const char* getTrackName();
        /** @brief Optimise Channels
          * @param maxChannels maximum number of channels
          * @param minVolume minimum volume **/
        virtual void optimiseChannels(int maxChannels, int minVolume);
        /** @brief Get Number of Instruments
          * @return number of instruments **/
        virtual int getNumberOfInstruments();
        /** @brief Get Number of Orders
          * @return Number of Orders **/
        virtual int getNumberOfOrders();
        /** @brief Get Number of Patterns
          * @return Number of Patterns */
        virtual int getNumberOfPatterns();
        /** @brief Get Number of Samples
          * @return Number of Samples **/
        virtual int getNumberOfSamples();
        /** @brief Get the songs current order
          * @return Current Order **/
        virtual int getOrder();
        /** @brief Get Row
          * @return Current Row **/
        virtual int getRow();
        /** @brief Get the songs current pattern
          * @return Current Pattern **/
        virtual int getPattern();
        // TODO: Document this better
        /** @brief Get Pattern length for a specified order
          * @param OrderNo Order Number
          * @return Pattern Length **/
        virtual int getPatternLength(int orderNo);
        /** @brief Get the channel the song is playing on
          * @return Channel **/
        virtual int getChannel();
        /** @brief Get Tracker Music Type (ref: FMUSIC_TYPE_NONE in the FMOD API Doco)
          * @return Tracker Music Type (FMUSIC_TYPE_NONE, FMUSIC_TYPE_MOD, FMUSIC_TYPE_S3M, FMUSIC_TYPE_XM, FMUSIC_TYPE_IT, FMUSIC_TYPE_MIDI, FMUSIC_TYPE_FSB) **/
        virtual int getTrackerMusicType();
        /** @brief Get Beats Per Minute
          * @return Beats Per Minute **/
        virtual int getBeatsPerMinute();
        /** @brief Get playback speed
          * @return Speed **/
        virtual int getSpeed();
        /** @brief Get Playback Time
          * @return Current PlayBack Time **/
        virtual int getPlaybackTime();
        // TODO: Document this better
        /** @brief Set Playback speed (1.0 is default)
          * @param speed PlayBack Speed **/
        virtual void setPlayBackSpeed(float speed);
        /** @brief Reset Playbacksped to default **/
        virtual void resetPlayBackSpeed();
        // TODO: Document this better
        /** @brief Set Order position / current playing position
          * @param order Order **/
        virtual void setOrder(int order);
        // TODO: Document this better
        /** @brief Set Pan Separation
          * @param value Pan Seperation **/
        virtual void setPanSeparation(float value);

    // ********************
    // * VOLUME FUNCTIONS *
    // ********************
    public:
        /** @brief Get Master Volume
          * @return Master Volume in range (0-255) (This is playback volume) **/
        virtual int getVolume();
        /** @brief Set Master Volume
          * @param value in range (0-255) (This is playback volume) **/
        virtual void setVolume(int value);

    public:
        /** @brief Get GlobalVolume
          * @return Global Volume in range (0 - 255) (This volume is not playback volume of the audio system rather volume of the song; say a fader is in use then this would decrease while master volume would remain the same) **/
        virtual int getGlobalVolume();

    protected:
        // Playback volume
        int volume;

    // *************
    // * CALLBACKS *
    // *************
    // TODO: We probably don't need this system but it is underdeveloped, I think we need to assume the user will be using a router
    public:
        /* TODO: Remove the get and set userdata here, this should be setup automatically in the load function
            to be a pointer to this class */
        // 88888888888888
        /** @brief Get userdata
          * @return User Data (useful in callbacks and such void* data type) **/
        virtual void* getUserData();
        /** @brief Set user data (extremely important for callbacks, can capture complex gameplay this way such as the player distoring audio)
          * @param pUserData the custom UserData associated with this instance **/
        virtual void setUserData(void* pUserData);
        // 88888888888888
        /** @brief Set instrument callback (everytime an instrument is played this called back will be fired)
          * @param callback our callback function FMUSIC_CALLBACK signature
          * @param instrument the instrument we want to attach the callback to **/
        virtual void setInstrumentCallback(FMUSIC_CALLBACK callback, int instrument);
        /** @brief Set Zxx callback (when Zxx is encountered in a tracker file this callback will be fired)
          * @param callback **/
        virtual void setZxxCallback(FMUSIC_CALLBACK callback);
        /** @brief Set Order callback
          * @param callback a function we want fired
          * @param the orderStep we want to associate the callback with **/
        virtual void setOrderCallback(FMUSIC_CALLBACK callback, int orderStep);

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
    // * FILENAME FUNCTIONS *
    // **********************
    public:
        /** @brief Get filename
          * @return filename **/
        virtual std::string getFilename() { return this->filename; }

    protected:
        // Music filename
        std::string filename;

    // **************************
    // * MUSIC MODULE FUNCTIONS *
    // **************************
    public:
        /** @brief Get the music module
          * @return FMUSIC_MODULE **/
        FMUSIC_MODULE* getMusicModule() { return this->pFMODMusicModule; }

    protected:
        // Pointer to the music module
        FMUSIC_MODULE* pFMODMusicModule;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        /** @brief Bind this class to a lua state
          * @param pLuaState The LuaState to bind this class to **/
        static void bindToLua(lua_State* pLuaState);
};

#endif // MUSIC_H
