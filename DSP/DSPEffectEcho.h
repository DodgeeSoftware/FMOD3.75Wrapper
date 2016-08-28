/**
  * @file   DSPEffectEcho.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  DSPEffectEcho implements an eccho DSPEffect
*/

#ifndef DSPEFFECTECHO_H
#define DSPEFFECTECHO_H

// FMOD Includes
#include <fmod.h>
#include <fmod_errors.h>

// GAMEAUDIO Includes
#include "FMODGlobals.h"
#include "DSP/IDSPEffect.h"

// TODO: Implement me
/** The DSPEffectEcho is a DSP Effect which will make audio echo **/
class DSPEffectEcho : public IDSPEffect
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        DSPEffectEcho()
        {

        }
        //! Destructor
        virtual ~DSPEffectEcho() {}

    protected:
        //! Copy Constructor
        DSPEffectEcho(DSPEffectEcho& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Methods and Members

    protected:
        //! DSPEffectEcho Assignment operator
        DSPEffectEcho& operator=(const DSPEffectEcho& other) { return *this; }

    // ****************
    // * DPS CALLBACK *
    // ****************
    public:
        /** @brief The DSP CallBack for this effect
          * @param pOriginalBuffer is the untransformed buffer being fed into this callback (I assume 16bit pcm data but not sure)
          * @param pNewBuffer is the transformed buffer, int length is the size of the buffer in bytes
          * @param pUserData is a pointer to the instance of the DSPEffect
          * @returns I am not sure what the function should return */ // TODO: Research more about return type
        virtual void* DSPCallBack(void* pOriginalBuffer, void* pNewBuffer, int length, void* pUserData);

};

#endif // DSPEFFECTECHO_H
