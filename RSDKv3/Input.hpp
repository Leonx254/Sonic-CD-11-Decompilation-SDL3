#ifndef INPUT_H
#define INPUT_H

enum InputButtons {
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT,
    INPUT_BUTTONA,
    INPUT_BUTTONB,
    INPUT_BUTTONC,
    INPUT_START,
    INPUT_ANY,
    INPUT_BUTTONCOUNT,
};

struct InputData {
    bool up;
    bool down;
    bool left;
    bool right;
    bool A;
    bool B;
    bool C;
    bool start;
};

struct InputButton {
    bool press, hold;
    int keyMappings, contMappings;

    inline void setHeld()
    {
        press = !hold;
        hold  = true;
    }
    inline void setReleased()
    {
        press = false;
        hold  = false;
    }

    inline bool down() { return (press || hold); }
};

enum DefaultHapticIDs {
    HAPTIC_NONE = -2,
    HAPTIC_STOP = -1,
};

extern InputData keyPress;
extern InputData keyDown;

extern bool anyPress;

extern int touchDown[8];
#if RETRO_USING_SDL3 && !RETRO_USING_ORIGINAL_CODE
#undef SDL_CONTROLLER_BUTTON_MAX
#define SDL_CONTROLLER_BUTTON_MAX SDL_GAMEPAD_BUTTON_MAX
extern float touchX[8];
extern float touchY[8];
#else
extern int touchX[8];
extern int touchY[8];
#endif
extern int touchID[8];
extern int touches;

extern int hapticEffectNum;

#if !RETRO_USE_ORIGINAL_CODE
extern InputButton inputDevice[INPUT_BUTTONCOUNT];
extern int inputType;

extern float LSTICK_DEADZONE;
extern float RSTICK_DEADZONE;
extern float LTRIGGER_DEADZONE;
extern float RTRIGGER_DEADZONE;

extern int mouseHideTimer;
#endif
#if !RETRO_USE_ORIGINAL_CODE
#if RETRO_USING_SDL2 || RETRO_USING_SDL3
// Easier this way
enum ExtraSDLButtons {
    SDL_CONTROLLER_BUTTON_ZL = SDL_CONTROLLER_BUTTON_MAX + 1,
    SDL_CONTROLLER_BUTTON_ZR,
    SDL_CONTROLLER_BUTTON_LSTICK_UP,
    SDL_CONTROLLER_BUTTON_LSTICK_DOWN,
    SDL_CONTROLLER_BUTTON_LSTICK_LEFT,
    SDL_CONTROLLER_BUTTON_LSTICK_RIGHT,
    SDL_CONTROLLER_BUTTON_RSTICK_UP,
    SDL_CONTROLLER_BUTTON_RSTICK_DOWN,
    SDL_CONTROLLER_BUTTON_RSTICK_LEFT,
    SDL_CONTROLLER_BUTTON_RSTICK_RIGHT,
    SDL_CONTROLLER_BUTTON_MAX_EXTRA,
};
void ControllerInit(byte controllerID);
void ControllerClose(byte controllerID);
#endif

#if RETRO_USING_SDL1
extern byte keyState[SDLK_LAST];

extern SDL_Joystick *controller;
#endif

void ProcessInput();
#endif

void CheckKeyPress(InputData *input, byte Flags);
void CheckKeyDown(InputData *input, byte Flags);

#if RETRO_USE_HAPTICS
inline int GetHapticEffectNum()
{
    int num         = hapticEffectNum;
    hapticEffectNum = HAPTIC_NONE;
    return num;
}
void QueueHapticEffect(int hapticID);
void PlayHaptics(int left, int right, int power);
void PlayHapticsID(int hapticID);
void StopHaptics(int hapticID);
#endif

#endif // !INPUT_H
