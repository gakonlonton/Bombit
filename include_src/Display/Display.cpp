#include "../../include/Display/Display.h"

Display::Display(void)
    : d_leavePrevious(false), d_leaveNext(false),
      d_nextDisplay(nullptr), d_keyboardInput(KeyboardInput::Instance()) {}

Display::~Display(void) {}
void Display::Init(void) {}
void Display::Leave(void) {}

void Display::Enter(int mode) {
    d_leavePrevious = false;
    d_leaveNext = false;
}

int Display::Destroy(void) {
    return 0;
}

