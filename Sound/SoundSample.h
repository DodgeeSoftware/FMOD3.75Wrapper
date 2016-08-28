/**
  * @file   SoundSample.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  SoundSample is a wrapper around and FSOUNDSample*
*/

#ifndef SOUNDSAMPLE_H
#define SOUNDSAMPLE_H

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

/** @class SoundSample
  * @brief SoundSample is a wrapper around and FSOUNDSample*
  * @detail The Sound Sample class is a wrapper around an FSOUND_SAMPLE object.
    This class is used because the FSOUND_SAMPLE object is actually a predeclaration and using is
    as anything other than a pointer will create compile errors. So it becomes impossible to bind
    the FSOUND_SAMPLE to any scripting language because the object isn't defined **/
class SoundSample
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        SoundSample()
        {
            this->pFMODSoundSample = 0;
            this->filename.clear();
        }
        //! Destructor
        virtual ~SoundSample()
        {
            // Release the SoundSample if that hasn't happened already
            //if (this->pFMODSoundSample != 0)
                //FSOUND_Sample_Free(this->pFMODSoundSample);
            // Reset the pointer to the sound sample
            this->pFMODSoundSample = 0;
            // Clear the filename
            this->filename.clear();
        }

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        //! SoundSample Assignment operator
        SoundSample& operator=(const SoundSample& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        /** @brief Get Sound Sample Name
          * @return name name of this SoundSample **/
        virtual const char* getName() { return FSOUND_Sample_GetName(this->pFMODSoundSample); }
        /** @brief Get Length in samples
          * @return Length in Samples **/
        virtual unsigned int getLength() { return FSOUND_Sample_GetLength(this->pFMODSoundSample); }
        /** @brief Set to Loop
          * @param state true to loop false to unloop **/
        virtual void setLoop(bool state)
        {
            if (state == true)
                FSOUND_Sample_SetMode(this->pFMODSoundSample, FSOUND_LOOP_NORMAL);
            else
                FSOUND_Sample_SetMode(this->pFMODSoundSample, FSOUND_LOOP_OFF);
        }
        /** @brief Is Looping?
          * @return true if looping, false otherwise **/
        bool isLoop() { return (FSOUND_Sample_GetMode(pFMODSoundSample) & FSOUND_LOOP_NORMAL); }

    // **************************
    // * SOUND SAMPLE FUNCTIONS *
    // **************************
    public:
        /** @brief Get the sound sample
          * @return FMOD_SAMPLE pointer **/
        virtual FSOUND_SAMPLE* getFMODSoundSample() { return this->pFMODSoundSample; }
        /** @brief Set the sound sample
          * @param pFMODSOundSample the FSOUND_SAMPLE pointer for thie SoundSample **/
        virtual void setFMODSoundSample(FSOUND_SAMPLE* pFMODSoundSample) { this->pFMODSoundSample = pFMODSoundSample; }

    protected:
        // Handle to the FSOUND_SAMPLE
        FSOUND_SAMPLE* pFMODSoundSample;

    // **********************
    // * FILENAME FUNCTIONS *
    // **********************
    public:
        /** @brief Get filename
          * @return filename **/
        virtual const char* getFilename() { return this->filename.c_str(); }
        /** @brief Set filename
          * @param filename **/
        virtual void setFilename(const char* filename) { this->filename = filename; }

    protected:
        // Sound filename
        std::string filename;

    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        /** @brief Bind this class to a lua state
          * @param pLuaState The LuaState to bind this class to **/
        static void bindToLua(lua_State* pLuaState);
};

#endif // SOUNDSAMPLE_H
