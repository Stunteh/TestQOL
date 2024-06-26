#ifndef GEODE_IS_MACOS

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/CCScheduler.hpp>
#include <Geode/modify/FMODLevelVisualizer.hpp>
#include "../Client/Client.h"
#include "../Utils/defines.hpp"

//#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
//#define MBO MEMBERBYOFFSET

using namespace geode::prelude;

Module* pulseAll = nullptr;

class MenuPulse : public CCNode
{
    public:
        Module* mod = nullptr;

        CCNode* node = nullptr;
        float v = 1.0f;

        FMODAudioEngine* engine = nullptr;

        bool init()
        {
            if (!CCNode::init())
                return false;

            mod = Client::GetModule("menu-pulse");

            engine = FMODAudioEngine::sharedEngine();

            this->scheduleUpdate();

            return true;
        }

        void update(float dt)
        {
            #ifdef GEODE_IS_APPLE
            engine->update(dt);
            #else
            engine->updateMetering();
            #endif
            
            #ifdef GEODE_IS_WINDOWS
            float met = *(reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(engine) + 0x178));
            #else
            float met = engine->getMeteringValue();
            #endif

            v = as<float>(std::lerp(as<float>(v), as<float>(met), dt * 6.9420f));
            if (node)
                node->setScale(mod->enabled ? (0.85f + clampf(v * 0.25f, 0, 1)) : 1);
        }

        CREATE_FUNC(MenuPulse);
};

class $modify (MenuLayer)
{
    bool init()
    {
        if (!MenuLayer::init())
            return false;

            
        #ifdef GEODE_IS_WINDOWS
        *(reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(FMODAudioEngine::sharedEngine()) + 0x188)) = true;
        #else
        FMODAudioEngine::sharedEngine()->enableMetering();
        #endif

        auto mp = MenuPulse::create();
        mp->node = getChildOfType<CCSprite>(this, 0);

        this->addChild(mp);

        return true;
    }
};

#endif