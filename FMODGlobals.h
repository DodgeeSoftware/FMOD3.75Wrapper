/**
  * @file   FMODGlobals.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  FMODGlobals is a header that we store
  * device globals in such as mute
*/

#ifndef FMOD_GLOBALS_H
#define FMOD_GLOBALS_H

namespace FMODGlobals
{
    /* The Mute Flag is a nasty hack around the fact that there is no mute
        function for the FMOD Sound System. There are three functions

            FSOUND_SetMute(FSOUND_ALL, this->muteFlag);

            FSOUND_SetVolumeAbsolute(FSOUND_ALL, 0);

            FSOUND_SetSFXMasterVolume(0);

            Gotchas!
            1. FSOUND_SetMute and FSOUND_SetVolumeAbsolute only mutes and sets the volumes for channels that are already playing. As a result
               you can call them and mute or silence them but, any new sounds you play will be at normal volumes
            2. FSOUND_SetSFXMasterVolume doesn't actually work at all, does absolutely nothing
        */
    extern bool muteFlag;
}

#endif // FMOD_GLOBALS_H
