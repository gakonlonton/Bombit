#include "../../include/Display/DisplayManager.h"
#include "../../include/Display/DisplayUtilities.h"

using namespace std;

DisplayManager::DisplayManager(SDL_Texture* texture, SDL_Renderer* renderer,
                               bool* running, int windowWidth, int windowHeight)
    :s_renderer(renderer), s_windowWidth(windowWidth), s_windowHeight(windowHeight) {

    s_displays.push(new WelcomeDisplay(texture, renderer, windowWidth, windowHeight));
}

DisplayManager::~DisplayManager(void) {
    while(!s_displays.empty()) {
        delete s_displays.top();
        s_displays.pop();
    }
}

void DisplayManager::EnterDisplay(Display* display) {
    s_displays.top()->Leave();
    s_displays.push(display);
    s_displays.top()->Init();
}

void DisplayManager::LeaveDisplay(void) {
    int mode = s_displays.top()->Destroy();
    delete s_displays.top();
    s_displays.pop();
    s_displays.top()->Enter(mode);
}

Display* DisplayManager::CurrentDisplay(void) {
    return s_displays.top();
}

void DisplayManager::Update(void) {
    if(CurrentDisplay()->ShouldLeaveToNext()) {
        EnterDisplay(CurrentDisplay()->NextDisplay());
    }
    else if(CurrentDisplay()->ShouldLeaveToPrevious()) {
        LeaveDisplay();
        Update();
    }
    else CurrentDisplay()->Update();
}

void DisplayManager::Draw(SDL_Renderer* renderer) {
    CurrentDisplay()->Draw(renderer);
}
