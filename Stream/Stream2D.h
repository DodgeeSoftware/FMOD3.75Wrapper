/**
  * @file   Stream2D.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Stream2D provides the ability to load and buffer
  * audio files in real-time so that an entire file
  * need not be loaded. This massively decreases load time.
*/

#ifndef STREAM2D_H
#define STREAM2D_H

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
#include "Stream/Stream.h"

/** @class Stream2D
  * @brief The Stream2D class is a positional stream
  * @detail The Stream2D Class creates a 2 dimension (aka x,y) representation of a streaming audio. Streaming in that
    no loading is done, sound is read directly from disc **/
class Stream2D : public Stream
{
    // CONSTRUCTOR / DESTRUCTOR
    public:
        //! Default Constructor
        Stream2D()
        {
            this->x = 0.0f;
            this->y = 0.0f;
            this->xVelocity = 0.0f;
            this->yVelocity = 0.0f;
            this->minDistance = 0.1f;
            this->maxDistance = 100000.0f;
        }
        //! Destructor
        virtual ~Stream2D() {}

    protected:
        //! Stream2D Copy constructor
        Stream2D(const Stream2D& other) : Stream() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! Stream2D Assignment operator
        Stream2D& operator=(const Stream2D& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        /** @brief Load Stream
          * @param filename filename to load
          * @return true on success false on failure **/
        virtual bool load(std::string filename);

    // PLAYBACK
    public:
        /** @brief Play **/
        virtual void play();
        /** @brief PlayEx (play paused) **/
        virtual void playEx();

    // ***********************
    // * TRANSFORM FUNCTIONS *
    // ***********************
    public:
        /** @brief Get X Position
          * @return x x position **/
        virtual float getX();
        /** @brief Get Y Position
          * @return y y position **/
        virtual float getY();
        /** @brief Set Position
          * @param x x position
          * @param y y position **/
        virtual void setPosition(float x, float y);
        /** @brief Get X Velocity
          * @return x velocity **/
        virtual float getXVelocity();
        /** @brief Get Y Velocity
          * @return y velocity **/
        virtual float getYVelocity();
        /** @brief Set Velocity
          * @param xVelocity x velocity
          * @param yVelocity y velocity **/
        virtual void setVelocity(float xVelocity, float yVelocity);

    protected:
        // Horizontal Position
        float x;
        // Vertical Position
        float y;
        // Horizontal Velocity
        float xVelocity;
        // Vertical Velocity
        float yVelocity;

    // **********************
    // * DISTANCE FUNCTIONS *
    // **********************
    public:
        /** @brief Get min distance
          * @return min Distance the sound can be heard **/
        virtual float getMinDistance();
        /** @brief Get max distance
          * @return max distance the sound can be heard **/
        virtual float getMaxDistance();
        /** @brief Set min distance
          * @param minDistance the min distance the sound is audible **/
        virtual void setMinDistance(float minDistance);
        /** @brief Set max distance
          * @param maxDistance max distance the sound is audible **/
        virtual void setMaxDistance(float maxDistance);
        /** @brief Set min and max distance
          * @param minDisance min distance the sound can be heard
          * @param maxDisance min distance the sound can be heard **/
        virtual void setMinMaxDistance(float minDistance, float maxDistance);

    protected:
        // The smaller (0.1f - 0.3f) this value the shorter range the sound is audible
        float minDistance;
        // Usually 100000.0f and safely ignored
        float maxDistance;

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

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        /** @brief Bind this class to a lua state
          * @param pLuaState The LuaState to bind this class to **/
        static void bindToLua(lua_State* pLuaState);
};

#endif // STREAM2D_H
