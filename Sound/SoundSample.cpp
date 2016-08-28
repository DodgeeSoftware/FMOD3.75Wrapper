#include "SoundSample.h"

void SoundSample::bindToLua(lua_State* pLuaState)
{
    // TODO: More bindings
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        /* An FSOUND_SAMPLE is a predeclared datatype from the FMOD Library we have had problems
        with this design pattern from other 3rd party libraries. I created an intermediatery object
        called a sound sample which is used in place of an FSOUND_SAMPLE */
        luabind::class_<SoundSample>("SoundSample")
        .def(luabind::constructor<>())
    ];
}
