#include </opt/local/include/SDL2/SDL.h>
#include <iostream>

using namespace std;
int main()
{
        if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
                cout << "Coult not connect with SDL to read joystick." << endl;
                exit (0); }
        int count = SDL_NumJoysticks();
        for (int i = 0; i < count; i++) {
                SDL_JoystickGUID guid = SDL_JoystickGetDeviceGUID(i);
		SDL_Joystick *joy = SDL_JoystickOpen(i);
		SDL_JoystickID joy_id = SDL_JoystickInstanceID(joy);
                char guidStr[33];
                SDL_JoystickGetGUIDString(guid, guidStr, 33);
                cout << "Joystick " << i << " GUID: " << guidStr << " id "<<joy_id << endl; }
}
