#pragma once

#include <switch.h>
#include <vector>
#include <string>

#include "data.h"
#include "gfx.h"

//ui headers - split up to keep a bit more organized
#include "ui/miscui.h"
#include "ui/uistr.h"
#include "ui/ttlview.h"
#include "ui/thrdProc.h"
#include "ui/sldpanel.h"
#include "ui/usr.h"
#include "ui/ttl.h"
#include "ui/fld.h"
#include "ui/sett.h"
#include "ui/ext.h"
#include "ui/fm.h"

enum menuState
{
    USR_SEL,
    TTL_SEL,
    ADV_MDE,
    EX_MNU,
    OPT_MNU,
    FIL_MDE
};

namespace ui
{
    // Current menu/ui state
    extern int mstate, prevState;

    // Slide/animation scaling
    extern float animScale;

    // Loading glyph
    extern const std::string loadGlyphArray[];

    // Pad data - placed here for convenience
    extern PadState pad;
    extern HidTouchScreenState touchState;
    static inline void updateInput() { touchState = {0}; padUpdate(&pad); hidGetTouchScreenStates(&touchState, 1); }
    inline uint64_t padKeysDown() { return padGetButtonsDown(&pad); }
    inline uint64_t padKeysHeld() { return padGetButtons(&pad); }
    inline uint64_t padKeysUp() { return padGetButtonsUp(&pad); }

    inline void changeState(int newState)
    {
        prevState = mstate;
        mstate = newState;
    }

    // Holds theme set id
    extern ColorSetId thmID;

    // Both UI modes need access to this
    extern std::string folderMenuInfo;

    /* Colors:
         clearClr  = color to clear buffer
         txtCont   = text that contrasts clearClr
         txtDiag   = text color for dialogs
    */
    extern SDL_Color clearClr, transparent, txtCont, txtDiag, rectLt, rectSh, tboxClr, sideRect, divClr, heartColor, slidePanelColor;

    // Textbox graphics
    extern SDL_Texture *cornerTopLeft, *cornerTopRight, *cornerBottomLeft, *cornerBottomRight;
    // Menu bounding textures
    extern SDL_Texture *mnuTopLeft, *mnuTopRight, *mnuBotLeft, *mnuBotRight;

    // Covers for progress bar
    extern SDL_Texture *progCovLeft, *progCovRight, *diaBox;

    // Side bar texture
    extern SDL_Texture *sideBar;

    // Sets colors and loads font for icon creation
    void initTheme();

    // Loads graphics and other assets
    void init();
    void exit();

    // Inits HID (input)
    void hidInit();

    // Adds a panel pointer to a vector (for drawing order)
    int registerMenu(ui::menu *m);
    int registerPanel(ui::slideOutPanel *sop);
    threadInfo *newThread(ThreadFunc func, void *args, funcPtr _drawFunc);

    // Displays the load screen
    void showLoadScreen();

    // Draws the UI elements
    void drawUI();

    // Main application loop
    bool runApp();

    // Displays a pop-up message
    void showPopMessage(int frameCount, const char *fmt, ...);

    // Callback used by various menu functions
    void toTTL(void *);

    // -------------------------------------------------------------------------
    // NEW: Sync Save Menu Function Declaration
    // Displays a menu to sync NSO and Emulator saves.
    void showSyncSaveMenu();
}
