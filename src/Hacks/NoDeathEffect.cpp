#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "../Client/Client.h"

using namespace geode::prelude;

class $modify (PlayerObject)
{
    void playerDestroyed(bool p0)
    {
        log::info("PlayerObject::playerDestroyed");
        
        if (!Client::GetModuleEnabled("no-death"))
            PlayerObject::playerDestroyed(p0);
    }
};