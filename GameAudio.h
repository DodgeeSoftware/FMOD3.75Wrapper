/**
  * @file   GameAudio.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  GameAudio is a cover all include header
  * that pulls in all of the classes for our OpenALWrapper
*/

/** @mainpage GameAudio (OpenALWrapper)
  *
  * @section intro_sec Introduction
  *
  * The GameAudio OpenALWrapper is an easy to use c++ wrapper
  * around core features of OpenAL. The CaptureDevice class is a
  * wrapper around a recoring device. The Music class is a wrapper
  * around a streaming tracker file. A SoundBuffer is an OpenAL
  * Buffer for Audio that has been loaded (usually wav or ogg NOT MP3)
  * The Sound Class is a playable instance of a Sound Buffer. The
  * Sound2D Class is a positional instance of a SoundBuffer. The Sound3D
  * Class is a potisitional instance of a SoundBuffer. The Stream Class
  * Allows you to load sound into buffers from a file as you go rather than
  * loading an entire audio file in one go. The Stream2D and Stream3D classes
  * are positional counterparts to the Stream Class. The Source Class is a base
  * for many of our SoundEmitting classes and wraps up functions relating to
  * an OpenAL Source. The AudioSystem Class is a simply container for functions
  * that relate to the AudioDevice and allows you to query it's features, frequency
  * volume and mute status as well as grab handles to recoring devices. And finally the
  * AudioManager class which is responsible for loading instancable SoundBuffers
  *
  * @section install_sec Installation
  *
  * @subsection step1 Step 1: Dependencies
  * This project is dependant on OpenAL, LibSND and LibXMP so you must link to them.
  * The CBP file for this project uses global variables to find these libraries on your
  * disk so make sure you add them to CodeBlocks (or simply add your search paths and
  * pragma preprocessors if using visual studio). You can obtain binaries for these libraries at
  * https://www.openal.org/
  * http://www.mega-nerd.com/libsndfile/
  * http://xmp.sourceforge.net/
  *
  * @subsection step2 Step 2: Search Paths
  * You will need to add search paths to the folders where the headers and implementation files are
  * to your project. Paths such as "GameAudio" "GameAudio\CaptureDevice" "GameAudio\System" etc because
  * I don't prefix includes in this library with the locations of these headers (this may be changed later)
  *
  * @subsection step3 Step 3: Use
  * Take a look at main.cpp that comes with this OpenAL Wrapper and see unit tests to learn how
  * all the components work. You need to simply include "GameAudio.h" in your project and away you go.
  *
  * @section Warning Warning
  * OpenAL only supports 16-32-64 channels playing simultaniously and this varies depending on if sources are
  * mono and stereo and depends upon the driver in use. This library behing this wrapper may not meet your
  * needs. It is perfectly useful for very small projects. But for larger more commerically oriented projects
  * I recomment you look into FMOD (http://www.fmod.org/) or any other library that supports virtual mixing - which OpenAL does not.
  *
  * @section Credits Credits
  * Wrapper was developed by Sergeant Neipo of Dodgee Software 2016
  * Project is release under GPLv3
  **/

#ifndef GAMEAUDIO_H
#define GAMEAUDIO_H

#include "FMODGlobals.h"
#include "DSP/IDSPEffect.h"
#include "DSP/DSPEffectEcho.h"
#include "Music/Music.h"
#include "Sound/Sound.h"
#include "Sound/Sound2D.h"
#include "Sound/Sound3D.h"
#include "Sound/SoundSample.h"
#include "Stream/Stream.h"
#include "Stream/Stream2D.h"
#include "Stream/Stream3D.h"
#include "System/AudioSystem.h"

#endif // GAMEAUDIO_H
