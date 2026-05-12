#ifndef KEYBOARD_COCOA_H
#define KEYBOARD_COCOA_H

#include <cstdint>

namespace keyboardCocoa {

void setupCocoaKeyboard(void *windowHandle = nullptr);
bool keyIsPressed(uint16_t keyCode);
bool keyIsReleased(uint16_t keyCode);
void clearKeyStates();

}

#endif