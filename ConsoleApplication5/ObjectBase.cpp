#include "fmod/fmod.hpp"
#include <iostream>
#include <Windows.h>
#include <chrono>
using namespace std;
class SoundSystem {
private:
    static SoundSystem* instance;
    FMOD::System* system;
    FMOD::Sound* bgm;
    FMOD::Sound* sfx;
    FMOD::Sound* sfx1;

    FMOD::Channel* bgmChannel;
    FMOD::Channel* sfxChannel;

    FMOD::Channel* sfxChannel1;

    SoundSystem() {
        FMOD::System_Create(&system);
        system->init(32, FMOD_INIT_NORMAL, nullptr);
        bgm = nullptr;
        sfx = nullptr; sfx1 = nullptr;


        bgmChannel = nullptr;
        sfxChannel = nullptr;

        sfxChannel1 = nullptr;
    }

public:
    static SoundSystem* getInstance() {
        if (instance == nullptr) {
            instance = new SoundSystem();
        }
        return instance;
    }

    void playBGM(std::string fileName) {
        if (bgmChannel != nullptr) {
            bgmChannel->stop();
            bgmChannel = nullptr;
        }
        system->createStream(fileName.c_str(), FMOD_LOOP_NORMAL, nullptr, &bgm);
        system->playSound(bgm, nullptr, false, &bgmChannel);
    }

    void playSFX(std::string fileName,int mode, int type) {
        if (type == 0)
        {
            system->createSound(fileName.c_str(), mode, nullptr, &sfx);

            system->playSound(sfx, nullptr, false, &sfxChannel);
        }
        if (type == 1)
        {
            system->createSound(fileName.c_str(), mode, nullptr, &sfx1);
            system->playSound(sfx1, nullptr, false, &sfxChannel1);
        }
    }
};

SoundSystem* SoundSystem::instance = nullptr;
int main()
{
    SoundSystem* soundSystem = SoundSystem::getInstance();

    // Play background music
    soundSystem->playBGM("D:/ContraCE108/Contra/music/2 - Jungle  Hangar (Stages 1  7).mp3");

    // Play one-time sound effect
    soundSystem->playSFX("D:/ContraCE108/Contra/music/sfx/ContraShootSFX.mp3", FMOD_LOOP_NORMAL,0);
    // Wait for input before exiting
        // Wait for user input to play SFX2
    while (true) {
        if (GetAsyncKeyState('P') & 0x8000) { // Check if 'P' is pressed
            soundSystem->playSFX("D:/ContraCE108/Contra/music/sfx/Contra SFX (7).wav", FMOD_DEFAULT,1);
            Sleep(1000);
        }
        Sleep(10);
        if (GetAsyncKeyState('K') & 0x8000) { // Check if 'P' is pressed
            soundSystem->playSFX("D:/ContraCE108/Contra/music/sfx/BulletHit.wav", FMOD_DEFAULT, 1);
            Sleep(250);
        }
        Sleep(10);
    }
    
    return 0;
}
