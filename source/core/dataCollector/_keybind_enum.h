#ifndef _KEY_BINDS_ENUM_H
#define _KEY_BINDS_ENUM_H

// this setup used for mark actions
// gameplay example: ESC for pause menu, E - interact, other keys for gameplay
// actions editor example: ESC for exit from editor, TAB for open sidebar menu,
enum class KeyBindsEnum
{
 // basic actions
 ACTION_NONE = 0, // Default value, no action assigned
 ACTION_BACK = 1,
 ACTION_CLOSE = 2, // A_CLOSE used for close/exit from states
 ACTION_SAVE = 3,  // A_SAVE used for save game, save settings and etc
 ACTION_TAB_MENU = 4,
 ACTION_NEXT_PAGE = 5,
 ACTION_FORWARD_PAGE = 6,
 ACTION_DEBUG_SWITCH = 15,
 // editor actions
 ACTION_EDITOR_CLOSE = ACTION_CLOSE,               // A_CLOSE for exit from editor
 ACTION_EDITOR_TAB_MENU = ACTION_TAB_MENU,         // A_TAB_MENU for open sidebar menu
 ACTION_EDITOR_NEXT_PAGE = ACTION_NEXT_PAGE,       // A_NEXT_PAGE (add note)
 ACTION_EDITOR_FORWARD_PAGE = ACTION_FORWARD_PAGE, // A_FORWARD_PAGE (add note)
                                                   // settings actions
 ACTION_SETTINGS = ACTION_NONE,
 ACTION_SETTINGS_BACK = ACTION_BACK,                 // A_BACK for back in settings
 ACTION_SETTINGS_NEXT_PAGE = ACTION_NEXT_PAGE,       // A_NEXT_PAGE change page to right
 ACTION_SETTINGS_FORWARD_PAGE = ACTION_FORWARD_PAGE, // A_FORWARD_PAGE change page to left
 ACTION_SETTINGS_SAVE = ACTION_SAVE,                 // A_SAVE for save settings
                                                     // gameplay actions
 KEY_W = 20,
 KEY_A = 21,
 KEY_S = 22,
 KEY_D = 23,
 KEY_E = 24,
 KEY_Q = 25,
 KEY_R = 26,
 KEY_F = 27,               // just exist
 KEY_SLASH = 30,           // USED FOR DEBUG ONLY
 KEY_SPACE = 31,           // for some actions (maybe was move on F)
 KEY_CLOSE = ACTION_CLOSE, // A_CLOSE for open pause menu
                           // total
 COUNT
};
#endif _KEY_BINDS_ENUM_H