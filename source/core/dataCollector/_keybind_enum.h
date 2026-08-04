#ifndef _KEY_BINDS_ENUM_H
#define _KEY_BINDS_ENUM_H

// this setup used for mark actions
// gameplay example: ESC for pause menu; E - interact; other keys for gameplay
// actions editor example: ESC for exit from editor; TAB for open sidebar menu;
namespace ActionKeyBind {
// basic actions
const char ACTION_NONE[] = "";      // Default value; no action assigned
const char ACTION_SAVE[] = "ACTION_SAVE"; // A_SAVE used for save game; save settings and etc
const char ACTION_LOAD[] = "ACTION_LOAD";
const char ACTION_APPLY[] = "ACTION_APPLY";
const char ACTION_CLOSE[] = "ACTION_CLOSE"; // A_CLOSE used for close/exit from states
const char ACTION_REMOVE[] = "ACTION_REMOVE";
const char ACTION_TAB_MENU[] = "ACTION_TAB_MENU";
const char ACTION_NEXT_PAGE[] = "ACTION_NEXT_PAGE";
const char ACTION_FORWARD_PAGE[] = "ACTION_FORWARD_PAGE";

const char ACTION_DEBUG_SWITCH[] = "DEBUG";
// settings actions
const char ACTION_SETTINGS_SAVE[] = "ACTION_SETTINGS_SAVE";         // for save settings
const char ACTION_SETTINGS_LOAD[] = "ACTION_SETTINGS_LOAD";         // for load in set
const char ACTION_SETTINGS_NEXT_PAGE[] = "ACTION_SETTINGS_NEXT_PAGE";    // A_NEXT_PAGE change page to right
const char ACTION_SETTINGS_FORWARD_PAGE[] = "ACTION_SETTINGS_FORWARD_PAGE"; // A_FORWARD_PAGE change page to left

// gameplay actions
const char KEY_W[] = "KEY_W";
const char KEY_A[] = "KEY_A";
const char KEY_C[] = "KEY_C";
const char KEY_S[] = "KEY_S";
const char KEY_D[] = "KEY_D";
const char KEY_E[] = "KEY_E";
const char KEY_F[] = "KEY_F";
const char KEY_Q[] = "KEY_Q";
const char KEY_R[] = "KEY_R";
// NUM
const char KEY_NUM_0[] = "KEY_NUM_0";
const char KEY_NUM_1[] = "KEY_NUM_1";
const char KEY_NUM_2[] = "KEY_NUM_2";
const char KEY_NUM_3[] = "KEY_NUM_3";
const char KEY_NUM_4[] = "KEY_NUM_4";
const char KEY_NUM_5[] = "KEY_NUM_5";
const char KEY_NUM_6[] = "KEY_NUM_6";
const char KEY_NUM_7[] = "KEY_NUM_7";
const char KEY_NUM_8[] = "KEY_NUM_8";
const char KEY_NUM_9[] = "KEY_NUM_9";

// const char KEY_NUM_[]="";
// const char KEY_[]="";
// gameplay actions
const char ACTION_INVENTORY[] = "ACTION_INVENTORY";
const char KEY_SPACE[] = "KEY_SPACE"; // for some actions (maybe was move on F)

const char KEY_F1[] = "KEY_F1";
const char KEY_F2[] = "KEY_F2";
const char KEY_F3[] = "KEY_F3";
const char KEY_F4[] = "KEY_F4";
const char KEY_F5[] = "KEY_F5";
const char KEY_F6[] = "KEY_F6";
const char KEY_F7[] = "KEY_F7";
const char KEY_F8[] = "KEY_F8";
const char KEY_F9[] = "KEY_F9";
const char KEY_F10[] = "KEY_F10";
const char KEY_F11[] = "KEY_F11";
const char KEY_F12[] = "KEY_F12";
};
#endif //_KEY_BINDS_ENUM_H