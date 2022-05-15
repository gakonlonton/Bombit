#include <bits/stdc++.h>
#include "../../include/System/KeyboardInput.h"

using namespace std;

KeyboardInput* KeyboardInput::m_instance;
KeyboardInput::KeyboardInput(void){}

KeyboardInput* KeyboardInput::Instance() {
    if(m_instance == 0) {
        m_instance = new KeyboardInput();
    }
    return m_instance;
}

void KeyboardInput::TurnKeyOn(SDL_Keycode key) {
    if(key == SDLK_DOWN || key == SDLK_UP ||
       key == SDLK_LEFT || key == SDLK_RIGHT) {
        m_keyPressed[SDLK_DOWN] = false;
        m_keyPressed[SDLK_UP]    = false;
        m_keyPressed[SDLK_LEFT]  = false;
        m_keyPressed[SDLK_RIGHT] = false;
    }
    m_keyPressed[key] = true;
    return;
}

void KeyboardInput::TurnKeyOff(SDL_Keycode key) {
    m_keyPressed[key] = false;
    return;
}

bool KeyboardInput::IsKeyOn(SDL_Keycode key) {
    if(m_keyPressed.count(key) > 0) {
        return m_keyPressed[key];
    }
    else return false;
}
