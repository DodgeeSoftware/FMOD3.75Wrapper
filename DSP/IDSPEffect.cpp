#include "IDSPEffect.h"

bool IDSPEffect::create(int priority)
{
    // If there is already a DSP Effect then destroy it
    if (this->pFMODDSPEffect != 0)
        this->destroy();
    // Try and create a DSP Effect
    this->pFMODDSPEffect = FSOUND_DSP_Create((FSOUND_DSPCALLBACK)callBackRouter, priority, (void*)this);
    /* NOTE: This hard type Casting of the CallBackRouter could be a problem
        I had to typecast to get it to build */
    // If creating the DSP effect failed return false
    if (this->pFMODDSPEffect == 0)
    {
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        std::cout << "ERROR: Unable to create DPS Effect" << std::endl;
        std::cout << "*******************************" << std::endl;
        // Failure
        return false;
    }
    // Success
    return true;
}

void IDSPEffect::destroy()
{
    // If there is an effect then destory it
    if (this->pFMODDSPEffect != 0)
    {
        FSOUND_DSP_Free(this->pFMODDSPEffect);
    }
}

void IDSPEffect::activate()
{
    // Activate the DSP Effect
    FSOUND_DSP_SetActive(this->pFMODDSPEffect, true);
}

void IDSPEffect::deactivate()
{
    // Deactivate the DSP Effect
    FSOUND_DSP_SetActive(this->pFMODDSPEffect, false);
}

bool IDSPEffect::isActive()
{
    // Return if the DSP Effect is active or not
    return FSOUND_DSP_GetActive(this->pFMODDSPEffect);
}

int IDSPEffect::getPriority()
{
    // Return the DSP Effect Priority
    return FSOUND_DSP_GetPriority(this->pFMODDSPEffect);
}

void IDSPEffect::setPriority(int priority)
{
    // Set the priority (order) of the DSP Effects application
    FSOUND_DSP_SetPriority(this->pFMODDSPEffect, priority);
}

//void* IDSPEffect::DSPCallBack(void* pOriginalBuffer, void* pNewBuffer, int length, void* pUserData)
//{
//    // This is where the effect code needs to go
//    /* Functions which can be used here
//        - FSOUND_DSP_ClearMixBuffer
//        - FSOUND_DSP_GetBufferLength
//        - FSOUND_DSP_GetBufferLengthTotal
//        - FSOUND_DSP_GetClearUnit // Should this be in the AudioSystem Class?
//        - FSOUND_DSP_GetClipAndCopyUnit // Should this be in the AudioSystem Class?
//        - FSOUND_DSP_GetMusicUnit // Should this be in the AudioSystem Class?
//        - FSOUND_DSP_GetSFXUnit // Should this be in the AudioSystem Class?
//        - FSOUND_DSP_GetFFTUnit
//        - FSOUND_DSP_GetSpectrum  // Should this be in the AudioSystem Class?
//        - FSOUND_DSP_MixBuffers
//    */
//}

void* IDSPEffect::callBackRouter(void* pOriginalBuffer, void* pNewBuffer, int length, void* pUserData)
{
    // If there is no UserData then cannot route information for the DSPEffect
    if (pUserData == 0)
        return 0;
    // Type Cast the UserData into a DSPEffect
    IDSPEffect* pDSPEffect = (IDSPEffect*)pUserData;
    // Route the traffic to the appropriate callback
    pDSPEffect->DSPCallBack(pOriginalBuffer, pNewBuffer, length, pUserData);
}
