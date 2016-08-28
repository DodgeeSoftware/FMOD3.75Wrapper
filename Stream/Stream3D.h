/**
  * @file   Stream.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Stream provides the ability to load and buffer
  * audio files in real-time so that an entire file
  * need not be loaded. This massively decreases load time
*/

#ifndef STREAM3D_H
#define STREAM3D_H

// FMOD Includes
#include <fmod.h>
#include <fmod_errors.h>

// LUA / LUABIND Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>

// GameAudio Includes
#include "FMODGlobals.h"
#include "Stream.h"

/** @class Stream3D
  * @brief The Stream3D class is a positional stream
  * @detail The Stream3D Class creates a 3 dimension (aka x,y) representation of a streaming audio. Streaming in that
    no loading is done, sound is read directly from disc **/
class Stream3D : public Stream
{
    public:
        //! Default Constructor
        Stream3D()
        {
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
            this->xVelocity = 0.0f;
            this->yVelocity = 0.0f;
            this->zVelocity = 0.0f;
            this->minDistance = 0.1f;
            this->maxDistance = 100000.0f;
        }
        //! Destructor
        virtual ~Stream3D() {}

    protected:
        //! Stream2D Copy constructor
        Stream3D(const Stream3D& other) : Stream() {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! Stream3D Assignment operator
        Stream3D& operator=(const Stream3D& other) { return *this; }

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
        /** @brief Get Z Position
          * @return z z position **/
        virtual float getZ();
        /** @brief Set Position
          * @param x x position
          * @param y y position
          * @param z z position **/
        virtual void setPosition(float x, float y, float z);
        /** @brief Get X Velocity
          * @return x velocity **/
        virtual float getXVelocity();
        /** @brief Get Y Velocity
          * @return y velocity **/
        virtual float getYVelocity();
        /** @brief Get Z Velocity
          * @return z velocity **/
        virtual float getZVelocity();
        /** @brief Set Velocity
          * @param xVelocity x velocity
          * @param yVelocity y velocity
          * @param zVelocity z velocity **/
        virtual void setVelocity(float xVelocity, float yVelocity, float zVelocity);

    protected:
        // Horizontal Position
        float x;
        // Vertical Position
        float y;
        // Depth Position
        float z;
        // Horizontal Velocity
        float xVelocity;
        // Vertical Velocity
        float yVelocity;
        // Depth Velocity
        float zVelocity;

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

#endif // STREAM3D_H
