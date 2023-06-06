#include "Sound.h"

const LPCWSTR SOUND_FILES[] = { TEXT("what.wav"), TEXT("kill.wav"), TEXT("death-horse.wav"), TEXT("ho no.wav"), TEXT("killYourQueen.wav"), TEXT("evolve.wav"), TEXT("cool_kill"), TEXT("move.wav"), TEXT("meow.wav")};

bool onOffSound = true;

void playSound(int op) {
    if(onOffSound){
        PlaySound(NULL, 0, 0);  // stop any played sound
        PlaySound(SOUND_FILES[op], NULL, SND_FILENAME | ((op == checkMate) ? SND_SYNC : SND_ASYNC) | SND_NOSTOP | SND_NODEFAULT);
    }
}