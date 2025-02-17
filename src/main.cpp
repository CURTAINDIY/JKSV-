#include <switch.h>
#include <curl/curl.h>
#include <cstdio>

#include "gfx.h"
#include "file.h"
#include "data.h"
#include "ui.h"
#include "util.h"
#include "cfg.h"

extern "C"
{
    void userAppInit(void)
    {
        appletInitialize();
        hidInitialize();
        nsInitialize();
        setsysInitialize();
        setInitialize();
        accountInitialize(AccountServiceType_Administrator);
        pmshellInitialize();
        socketInitializeDefault();
        pdmqryInitialize();
    }

    void userAppExit(void)
    {
        appletExit();
        hidExit();
        nsExit();
        setsysExit();
        setExit();
        accountExit();
        pmshellExit();
        socketExit();
        pdmqryExit();
    }
}

int main(int argc, const char *argv[])
{
    // Initialize ROMFS, config, file system, graphics, UI theme, and data.
    romfsInit();
    cfg::resetConfig();
    cfg::loadConfig();
    fs::init();
    gfx::init();
    ui::initTheme();
    ui::showLoadScreen();
    data::init();
    ui::init();
    romfsExit();

    curl_global_init(CURL_GLOBAL_ALL);
    
    // Initialize remote storage if not in applet mode.
    if (!util::isApplet())
        fs::remoteInit();
    else
        ui::showMessage(ui::getUICString("appletModeWarning", 0));
        
    // Main menu loop
    while (true)
    {
        consoleClear();
        printf("Save Manager - Main Menu\n");
        printf("1) Backup/Restore Saves\n");
        printf("2) Convert Save Files (.sav ⇄ .srm)\n");
        printf("3) Sync Game Save (NSO ⇄ Emulator)\n");
        printf("4) Exit\n");

        int option;
        scanf("%d", &option);

        if (option == 1)
        {
            // Call your backup/restore menu (replace with your actual function)
            ui::showBackupRestoreMenu();
        }
        else if (option == 2)
        {
            ui::showConvertSaveMenu();
        }
        else if (option == 3)
        {
            // Calls the sync menu that handles NSO ⇄ Emulator save syncing.
            ui::showSyncSaveMenu();
        }
        else if (option == 4)
        {
            break;
        }
    }

    // Cleanup before exit.
    fs::remoteExit();
    curl_global_cleanup();
    ui::exit();
    data::exit();
    gfx::exit();

    return 0;
}
