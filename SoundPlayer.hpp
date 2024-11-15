#ifndef SOUNDPLAYER_HPP
#define SOUNDPLAYER_HPP

#include <iostream>
#include <SDL.h>
#include <string>

class SoundPlayer {
public:
    SoundPlayer() : audioDevice(0), audioData(nullptr), audioSize(0) {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cerr << "Failed to initialize SDL Audio: " << SDL_GetError() << std::endl;
            std::exit(1);
        }
    }

    ~SoundPlayer() {
        cleanup();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }

    bool loadSound(const std::string& filePath) {
        cleanup(); // Cleanup any previously loaded audio
        if (SDL_LoadWAV(filePath.c_str(), &audioSpec, &audioData, &audioSize) == nullptr) {
            std::cerr << "Failed to load WAV file: " << SDL_GetError() << std::endl;
            return false;
        }

        audioDevice = SDL_OpenAudioDevice(NULL, 0, &audioSpec, NULL, 0);
        if (audioDevice == 0) {
            std::cerr << "Failed to open audio device: " << SDL_GetError() << std::endl;
            SDL_FreeWAV(audioData);
            audioData = nullptr;
            return false;
        }
        return true;
    }

    void playSound() const {
        if (audioDevice && audioData) {
            SDL_QueueAudio(audioDevice, audioData, audioSize);
            SDL_PauseAudioDevice(audioDevice, 0); // Unpause to start playing
        } else {
            std::cerr << "No sound loaded or audio device unavailable." << std::endl;
        }
    }

private:
    SDL_AudioSpec audioSpec;
    SDL_AudioDeviceID audioDevice;
    Uint8* audioData;
    Uint32 audioSize;

    void cleanup() {
        if (audioDevice) {
            SDL_PauseAudioDevice(audioDevice, 1);
            SDL_CloseAudioDevice(audioDevice);
            audioDevice = 0;
        }
        if (audioData) {
            SDL_FreeWAV(audioData);
            audioData = nullptr;
        }
    }
};

#endif // SOUNDPLAYER_HPP