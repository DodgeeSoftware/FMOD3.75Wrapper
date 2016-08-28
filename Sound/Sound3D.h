/**
  * @file   Sound3D.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Sound uses a SoundSample and a Channel to play 3D positional audio
*/

#ifndef SOUND3D_H
#define SOUND3D_H

// C++ Includes
#include <iostream>

// FMOD Includes
#include <fmod.h>

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
#include "Sound/Sound.h"
#include "Sound/SoundSample.h"

/** @class Sound3D
  * @brief Sound uses a SoundSample and a Channel to play 3D positional audio
  * @detail The Sound3D class is used for a 3D sound source and is effectively a wrapper around a reserved channel
        for an instance of Sound (which is referered to as a channel) **/
class Sound3D : public Sound
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        Sound3D()
        {
            // Position
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
            // Velocity
            this->xVelocity = 0.0f;
            this->yVelocity = 0.0f;
            this->zVelocity = 0.0f;
            // Min / Max Distance
            this->minDistance = 0.1f;
            this->maxDistance = 100000.0f;
        }
        //! Destructor
        virtual ~Sound3D() {}

    protected:
        //! Sound3D Copy constructor
        Sound3D(const Sound3D& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! Sound3D Assignment operator
        Sound3D& operator=(const Sound3D& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        /** @brief Play the sound **/
        virtual void play();
        /** @brief Play the sound paused **/
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
          * @param xVelocity x Velocity
          * @param yVelocity y Velocity
          * @param zVelocity z Velocity **/
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
        /** @brief Set min and max distance
          * @param minDisance min distance the sound can be heard
          * @param maxDisance min distance the sound can be heard **/
        virtual void setMinMaxDistance(float minDistance, float maxDistance);

    protected:
        // The smaller (0.1f - 0.3f) this value the shorter range the sound is audible
        float minDistance;
        // Usually 100000.0f and safely ignored
        float maxDistance;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        /** @brief Bind this class to a lua state
          * @param pLuaState The LuaState to bind this class to **/
        static void bindToLua(lua_State* pLuaState);
};

#endif // SOUND3D_H
