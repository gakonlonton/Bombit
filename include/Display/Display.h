#ifndef DISPLAY_H
#define DISPLAY_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "../System/KeyboardInput.h"

class Display {
    public:
        Display();
        virtual ~Display() = 0;
        Display(const Display& other) = delete;
        Display& operator= (const Display&) = delete;

        virtual void Init();
        virtual void Enter(int mode = 0);
        virtual void Leave();
        virtual void Update() = 0;
        virtual void Draw(SDL_Renderer* renderer) const = 0;
        virtual int Destroy();

        bool ShouldLeaveToPrevious() {
            return d_leavePrevious;
        }

        bool ShouldLeaveToNext() {
            return d_leaveNext;
        }

        Display* NextDisplay() {
            return d_nextDisplay;
        }

    protected:
        bool d_leavePrevious, d_leaveNext;
        Display* d_nextDisplay;
        KeyboardInput* d_keyboardInput;

    private:
};

#endif // DISPLAY_H
