#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <bits/stdc++.h>
#include <SDL_keycode.h>

using namespace std;

class KeyboardInput {
    public:
        static KeyboardInput* Instance();
        void TurnKeyOn(SDL_Keycode key);
        void TurnKeyOff(SDL_Keycode key);
        bool IsKeyOn(SDL_Keycode key);
    protected:
        KeyboardInput();
    private:
        map<SDL_Keycode, bool> m_keyPressed;
        static KeyboardInput* m_instance;
};

#endif // KEYBOARD_INPUT_H

