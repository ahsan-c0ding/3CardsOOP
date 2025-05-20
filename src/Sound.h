#pragma once

#include <raylib.h>

class SoundManager {
    Sound click_success;
    Sound click_fail;
    Sound place_card;

    public:
    void Load() {
        click_success = LoadSound("audio/click_sucess.wav");
        click_fail = LoadSound("audio/click_failed.wav");
        place_card = LoadSound("audio/place_card.wav");
    }

    void Unload() {
        UnloadSound(click_success);
        UnloadSound(click_fail);
        UnloadSound(place_card);
    }

    void playSucess(){
        PlaySound(click_success);
    }
     void playFail(){
        PlaySound(click_fail);
    }
     void playPlaced(){
        PlaySound(place_card);
    }
    
};