#pragma once

#include "Client.h"

class ClientUtils
{
public:
	static void Setup(bool android = false)
	{
        SetupSeviye();
        SetupBosgecme();        
        SetupKozmetik();
        SetupSimgeEfektleri();
        SetupHizHilesi();
        //SetupStatus();

        //SetupVariables(android);

        Window* level = new _Replay();
        level->name = "YenidenOynama";
        level->id = "yenidenoynana-window";
        Client::instance->windows.push_back(level);

        SetupOptions(android);

        if (android)
            Client::instance->windows.push_back(new Credits());
	}

#pragma region Setup Windows

    static void SetupHizHilesi()
    {
        Window* hizhilesi = new hizhilesi();
        hizhilesi->name = "HizHilesi";
        speedhack->id = "hizhilesi-window";
        speedhack->windowPos = ImVec2(50 + (50 + (Client::instance->tileSize.x)) * 2, 50);

        speedhack->modules.push_back(new HizHilesiTop());
        speedhack->modules.push_back(new HizHilesiEnabled());
        //speedhack->modules.push_back(new Module("Enabled", "speedhack-enabled", "Is the speedhack enabled?"));
        speedhack->modules.push_back(new HizHilesiMus());
        speedhack->modules.push_back(new HizHilesiGameplay());
        //speedhack->modules.push_back(new Module("Speedhack Music", "speedhack-music", "Speedhack all sound by your speed modifier", true));

        (reinterpret_cast<HizHilesiTop*>(speedhack->modules.front()))->format = "%x";

        Client::instance->windows.push_back(HizHilesi);
    }

    static void SetupSeviye()
    {
        Window* level = new Level();
        level->name = "Seviye";
        level->id = "seviye-window";
        level->windowPos = ImVec2(50 + (50 + (Client::instance->tileSize.x)) * 1, 50);

        level->modules.push_back(new Module("Boşgeç", "boşgeç", "Oyuncuyu olmekten alikoyar."));
        level->modules.push_back(new Module("Aninda tamamla", "aninda", "Aninda seviyeyi tanamlar.\n<cg>Geometry Dash</c>'in anti-hile'si yuzunden calismayabilir..\nBu hileyi <co>oylanmis seviyelerde</c> kullanmak <cr>SIZI LIDERLIK TABLOLARINDAN YASAKLAYABILIR.</c>", false, "<cr>Uyari</c>\nBu hileyi <co>oylanmis seviyelerde</c> kullanmak <cr>SIZI LIDERTABLOLARINDAN YASAKLAYABILIR.</c>", true));

        level->modules.push_back(new Module("Pratik Mod Onaylama", "conf-prac", "confirm practice mode help"));
        level->modules.push_back(new Module("Yeniden Baslatma Onaylama", "conf-res", "confirm restart help"));

        level->modules.push_back(new Module("Platformu Zorla", "force-plat", "Butun Seviyelere platform modunu zorlar"));
        level->modules.push_back(new Module("Seviye Duzenleme", "level-edit", "Herhangi bir seviyeyi duzenlemenize izin verir."));

        level->modules.push_back(new Module("Ayna Portali Yok", "no-reverse", "Ayna Portallarini Devre Disi Birakir,ama sadece bir orospu iseniz<cl>saka yaptim amk</c>"));
        level->modules.push_back(new Module("Aniden Yeniden Baslama", "instant-restart", " Olme aninda seviyeyi yeniden baslatir"));

        level->modules.push_back(new Module("Vuruskutularini Goster", "show-hitboxes", "Obje vuruskutularini gosterir"));
        level->modules.push_back(new Module("Olumde Vuruskutularini Goster", "show-hitboxes-on-death", "Olumde vuruskutularini gosterir.Istanbul Trafigi bunu surekligi yapmaya neden olabilir,<cl>saka saka</c>"));

        level->modules.push_back(new Module("Statik Kamera Yok", "no-static", "Statik Kamerayi Devre Disi Birakir."));

        #ifdef GEODE_IS_WINDOWS
        level->modules.push_back(new Module("All Modes Platformer", "all-plat", "Enabled All Gamemodes in platformer mode. <cl>Windows only</c>"));
        #endif

        //level->modules.push_back(new Module("No Hitboxes", "no-hitboxes", "Disables Object Hitboxes"));

        //level->modules.push_back(new Module("Force Show Player", "show-player", "Force the player to be visible all the time"));
        //level->modules.push_back(new Module("Force Hide Player", "hide-player", "Force the player to be hidden all the time"));


        //level->modules.push_back(new Module("Startpos Switcher", "startpos-switcher", "Switch between start-positions in the level"));
        //level->modules.push_back(new Module("Show Hitboxes", "hitbox"));

        Client::instance->windows.push_back(level);
    }

    static void Bosgecme()
    {
        Window* bypass = new Evrensel();
        bypass->name = "Evrensel";
        bypass->id = "bypass-window";
        bypass->windowPos = ImVec2(50 + (50 + (Client::instance->tileSize.x)) * 0, 50);


        bypass->modules.push_back(new Module("Practice Music Sync", "practice-bypass", "Unlocks the Practice Music Sync button in the pause menu options"));
        bypass->modules.push_back(new Module("Unlock All Icons", "icon-bypass", "It... Unlocks all the icons, You should know what this does"));

        bypass->modules.push_back(new Module("Music Unlocker", "music-bypass", "Unlocks the menu and practice music buttons"));
        bypass->modules.push_back(new Module("Fire in the hole!", "fire-in-the-hole", "Replaces every single sfx with\n<cr>FIRE IN THE HOLE!</c>"));

        bypass->modules.push_back(new Module("Copy any level", "copy-hack", "Allows you to copy any level from the servers\nCode by <co>Firee</c>"));
        bypass->modules.push_back(new Module("No Copy Mark", "noc-hack", "Hides the (c) mark from your levels on publish.\nCode by <co>Firee</c>"));

        bypass->modules.push_back(new Module("Auto Safe mode", "auto-safe-mode", "Automatically enables safe mode if you have cheats enabled", true));
        bypass->modules.push_back(new Module("Safe mode", "safe-mode", "Disables all progress on levels"));

        bypass->modules.push_back(new Module("Character Limit", "char-limit", "Removes the <cl>character limit</c> on input fields", false, "<cr>Warning!</c>\nThis module has been <cl>known</c> to cause issues on <cg>some</c> devices such as:\n<cl>- Crashing when you type</c>\n- Crashing when the input field goes away.\nIf the game crashes pressing an ok button, <cr>Disable</c> this module", true));
        bypass->modules.push_back(new Module("Character Filter", "char-filter", "Allows you to input <cg>any</c> character in input fields", false, "<cr>Warning!</c>\nThis module has been <cl>known</c> to cause issues on <cg>some</c> devices such as:\n<cl>- Crashing when you type</c>\n- Crashing when the input field goes away.\nIf the game crashes pressing an ok button, <cr>Disable</c> this module", true));

        bypass->modules.push_back(new Module("Auto Song Download", "auto-song", "Automatically downloads songs when you open a level"));
        bypass->modules.push_back(new Module("Full Options Menu", "full-options", "Replaces the mini options menu in the pause menu with the full options menu"));

        #ifdef GEODE_IS_ANDROID
        //bypass->modules.push_back(new Module("Slider Limit Bypass", "slider-limit", "Allows sliders to go beyond the limit of the slider. <cr>Doesn't work for scaling in the editor currently</c>"));
        #endif


        Client::instance->windows.push_back(bypass);
    }

    static void SetupCosmetic()
    {
        Window* cosmetic = new Window();
        cosmetic->name = "Cosmetic";
        cosmetic->id = "cosmetic-window";
        cosmetic->windowPos = ImVec2(50 + (50 + (Client::instance->tileSize.x)) * 3, 50);

        //cosmetic->modules.push_back(new Module("Hide Endscreen BTN", "end-screen", "Adds an arrow to hide the end screen"));
        cosmetic->modules.push_back(new Module("No Transition", "no-trans", "Disables the fade scene transitions"));
        cosmetic->modules.push_back(new Module("No Camera Shake", "no-shake", "Disables camera shake globally"));
        //cosmetic->modules.push_back(new Module("Thicker Hitboxes", "thick-hitbox", "Makes the hitboxes in gd thicker ;)"));

        cosmetic->modules.push_back(new Module("No Shaders", "no-shaders", "Disables shaders, <cl>maybe read</c> the name"));
        cosmetic->modules.push_back(new Module("No Death Effect", "no-death", "Disables the death effect on the player"));

        cosmetic->modules.push_back(new Module("No Wave Trail", "no-wave", "Disables the wave trail"));
        cosmetic->modules.push_back(new Module("Solid Wave Trail", "solid-wave", "Makes the wave trail a solid colour"));

        cosmetic->modules.push_back(new Module("Transparent BG", "trans-bg", "Disables the colouring on the gradient backgrounds"));
        cosmetic->modules.push_back(new Module("Transparent Lists", "trans-lists", "Disables the colouring on all cells"));

        cosmetic->modules.push_back(new Module("Force Trail On", "trail-on", "Forces the trail on"));
        cosmetic->modules.push_back(new Module("Force Trail Off", "trail-off", "Forces the trail off"));

        cosmetic->modules.push_back(new Module("No Glow", "no-glow", "Disables Object Glow"));
        cosmetic->modules.push_back(new Module("No Respawn Blink", "no-blink", "Disables the blinking when the player respawns"));

        //cosmetic->modules.push_back(new Module("Force Don't Fade", "dont-fade", "Forces all object to be Don't Fade"));
        //cosmetic->modules.push_back(new Module("Force Don't Enter", "dont-enter", "Forces all object to be Don't Enter"));

        #ifndef GEODE_IS_ANDROID32
        cosmetic->modules.push_back(new Module("No Player Rotation", "no-rot", "Disables rotation on players"));
        #endif
        #ifdef GEODE_IS_WINDOWS
        cosmetic->modules.push_back(new Module("No Particles", "no-particles", "Disables particles, seems pretty obvious what this does imo"));
        #endif

        //cosmetic->modules.push_back(new Module("No Camera Movement", "no-camera", "Disables camera movements that are made with <cl>triggers</c>"));
        //cosmetic->modules.push_back(new Module("No Player Rotation", "no-plr-rot", "Disables Player Rotation :3\nIt looks ugly imo but you do you"));

        Client::instance->windows.push_back(cosmetic);
    }

    static void SetupIconEffects()
    {
        Client::instance->windows.push_back(new IconEffects());
    }

    static void SetupMisc()
    {
        Window* misc = new Window();
        misc->name = "Misc";
        misc->id = "misc-window";
        misc->windowPos = ImVec2(50 + (50 + (Client::instance->tileSize.x)) * 4, 50);

        //misc->modules.push_back(new Module("Use Full Options", "full-options", "Opens the full options menu instead of the mini options in the pause menu.\nAlso adds a button to the normal pause menu to open the mini options."));

        Client::instance->windows.push_back(misc);
    }

    static void SetupReplay()
    {
        Window* replay = new Window();
        replay->name = "Robtop Replay";
        replay->id = "replay-window";
        replay->windowPos = ImVec2(50 + (50 + (Client::instance->tileSize.x)) * 5, 50);

        replay->modules.push_back(new InfoModule("Coming Soon", "This replay bot is called Robtop Replay because it uses Robtop's replay code"));

        Client::instance->windows.push_back(replay);
    }

    static void SetupStatus()
    {
        Window* replay = new Status();
        replay->name = "Status";
        replay->id = "status-window";
        replay->windowPos = ImVec2(50 + (50 + (Client::instance->tileSize.x)) * 6, 50);

        replay->modules.push_back(new StatusOpacity());
        replay->modules.push_back(new StatusScale());

        replay->modules.push_back(new Module("Testmode", "status-testmode", "Show the test mode text if there's a startpos"));
        replay->modules.push_back(new Module("FPS Counter", "status-fps", "Shows your current game fps"));
        replay->modules.push_back(new Module("Noclip Deaths (not fully accurate)", "status-death", "Shows your death count (hidden when noclip is disabled)"));
        replay->modules.push_back(new Module("Noclip Accuracy", "status-accuracy", "Shows your death accuracy (hidden when noclip is disabled)"));
        //replay->modules.push_back(new Module("Attempts", "status-attempts", "Shows your attempt count"));
        //replay->modules.push_back(new Module("Clicks", "status-clicks", "Shows your click count"));
        //replay->modules.push_back(new Module("Message", "status-message", "Write a message of your choice to be shown"));
        //replay->modules.push_back(new StatusMessage());

        Client::instance->windows.push_back(replay);
    }

    static void SetupOptions(bool android)
    {
        if (android)
        {
            auto cfg = new Config();
            
            cfg->modules.push_back(new Module("Draggable Ball", "allow-dragging", "Allow dragging the ball on screen", true));
            cfg->modules.push_back(new Module("Save Ball Position", "save-pos", "Saves the position of the ball on screen between sessions", true));
            cfg->modules.push_back(new Module("Additional Width", "npesta-width", "Add's borders to the sides of the menu. Looks weird with <cl>vanilla gd pack</c> but looks nice with <cg>npesta texture pack</c>"));
            #ifdef GEODE_IS_DESKTOP
            cfg->modules.push_back(new Module("Hide Button", "hide-btn", "Hides the button to open the menu, use the <cl>Tab</c> or <cl>Insert</c> key to open the mod menu", true));
            #endif

            Client::instance->windows.push_back(cfg);
            return;
        }

        Window* replay = new Window();
        replay->name = "Config";
        replay->id = "options-window";
        replay->windowPos = ImVec2(50 + (50 + (Client::instance->tileSize.x)) * 4, 50);

        if (android)
        {
            replay->modules.push_back(new AltModuleLocation());
            replay->modules.push_back(new CompactMode());
        }
        else
        {
            replay->modules.push_back(new Module("Draggable Ball", "allow-dragging", "Allow dragging the ball on screen"));
        }

        Client::instance->windows.push_back(replay);
    }

    /*static void SetupCreator()
    {
        Window* creator = new Window();
        creator->name = "Creator";
        creator->id = "creator-window";
        creator->windowPos = ImVec2(50 + (50 + (Client::instance->tileSize.x)) * 4, 50);

        creator->modules.push_back(new Module("Copy Hack", "copy-hack"));

        Client::instance->windows.push_back(creator);
    }*/

    static void SetupVariables(bool android)
    {
        if (android)
            Client::instance->windows.push_back(new Variables());

        //Client::instance->windows.push_back(new Variables());
    }

#pragma endregion
};
