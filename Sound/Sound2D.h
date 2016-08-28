/**
  * @file   Sound2D.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  Sound uses a SoundSample and a Channel to play 2D positional audio
*/

#ifndef SOUND2D_H
#define SOUND2D_H

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

/** @class Sound2D
  * @brief Sound2D uses a SoundSample and a Channel to play 2D positional audio
  * @detail The Sound2D class is used for a 2D sound source and is effectively a wrapper around a reserved channel
        for an instance of Sound2D (which is referered to as a channel) **/
class Sound2D : public Sound
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        Sound2D()
        {
            // Position
            this->x = 0.0f;
            this->y = 0.0f;
            // Velocity
            this->xVelocity = 0.0f;
            this->yVelocity = 0.0f;
            // Min and Max Distance
            this->minDistance = 0.1f;
            this->maxDistance = 100000.0f;
        }
        //! Destructor
        virtual ~Sound2D() {}

    protected:
        //! Sound2D Copy constructor
        Sound2D(const Sound2D& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! Sound2D Assignment operator
        Sound2D& operator=(const Sound2D& other) { return *this; }

    // GENERAL FUNCTIONS
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
          * @param xVelocity x Velocity
          * @param yVelocity y Velocity **/
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

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        /** @brief Bind this class to a lua state
          * @param pLuaState The LuaState to bind this class to **/
        static void bindToLua(lua_State* pLuaState);
};

#endif // SOUND2D_H
