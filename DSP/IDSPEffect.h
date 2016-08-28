/**
  * @file   IDSPEffect.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  IDSPEffect defines an interface class for a Digital
  * Signal Processing Effect. A DSP effect is similar to an graphics
  * shader accept it works transforming and mixing sound channels
*/

#ifndef IDSPEFFECT_H
#define IDSPEFFECT_H

// C++ Includes
#include <iostream>

// FMOD Includes
#include <fmod.h>
#include <fmod_errors.h>

// GameAudio Includes
#include "FMODGlobals.h"

/** @class IDSPEffect
  * @brief An Interface Class that builds basic functions required for a DSP Effect
  * @detail A Digital Signal Processing Effect is similar to a graphics shader accept that it operates on sounds.
  * They are applied according to priority which can be changed at run time **/
class IDSPEffect
{
    // ****************************
    // * CONSTRUCTOR / DESTRUCTOR *
    // ****************************
    public:
        //! Constructor
        IDSPEffect()
        {
            // FMODDSPEffect
            this->pFMODDSPEffect = 0;
        }
        //! Destructor
        virtual ~IDSPEffect() {}

    protected:
        //! Copy Constructor
        IDSPEffect(IDSPEffect& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Members and Methods

    protected:
        //! IDSPEffect Assignment operator
        IDSPEffect& operator=(const IDSPEffect& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        /** @brief Create the DSP Effect
          * @param priority set the placement of the Effect
          * @return true on success, false on failure **/
        virtual bool create(int priority);
        /** @brief Destroy the DSP Effect **/
        virtual void destroy();
        /** @brief Activate the DSP Effect **/
        virtual void activate();
        /** @brief Deactivate the DSP Effect **/
        virtual void deactivate();
        /** @brief Is the DSP Effect Active
          * @return true if active, false if not active **/
        virtual bool isActive();
        /** @brief Get the DSP Effect Priorty
          * @return the DSP Effect Priority **/
        virtual int getPriority();
        /** @brief Set the DSP Effect Priority
          * @param priority the DSP Effect Priority */
        virtual void setPriority(int priority);

    protected:
        // No functions or members

    // *******************
    // * FMOD DSP EFFECT *
    // *******************
    public:
        /** @brief Get FMODDSPEffect
          * @return FSOUND_DSPUNIT **/
        virtual FSOUND_DSPUNIT* getFMODDSPEffect() { return this->pFMODDSPEffect; }

    // DSPCALLBACK ROUTER
    public:
        /** @brief This static function serves to route traffic to the appropriate DSP Effect
          * @param pOriginalBuffer is the untransformed buffer being fed into this callback (I assume 16bit pcm data but not sure)
          * @param pNewBuffer is the transformed buffer, int length is the size of the buffer in bytes
          * @param pUserData is a pointer to the instance of the DSPEffect
          * @returns I am not sure what the function should return */ // TODO: Research more about return type
        static void* callBackRouter(void* pOriginalBuffer, void* pNewBuffer, int length, void* pUserData);

    protected:
        // Pointer to the FMOD DSP Effect
        FSOUND_DSPUNIT* pFMODDSPEffect;

    // ****************
    // * DPS CALLBACK *
    // ****************
    public:
        /** @brief The DSP CallBack for this effect
          * @param pOriginalBuffer is the untransformed buffer being fed into this callback (I assume 16bit pcm data but not sure)
          * @param pNewBuffer is the transformed buffer, int length is the size of the buffer in bytes
          * @param pUserData is a pointer to the instance of the DSPEffect
          * @returns I am not sure what the function should return */ // TODO: Research more about return type
        virtual void* DSPCallBack(void* pOriginalBuffer, void* pNewBuffer, int length, void* pUserData) = 0;
};

#endif // IDSPEFFECT_H
