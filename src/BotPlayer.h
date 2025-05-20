#pragma once

#include <iostream>
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Sound.h"

using namespace std;

class BotPlayer : public Player{
    public:
    BotPlayer(string bot_name = "Bot", bool flag = true){
        Name = bot_name;
        isBot = flag;
        Blinds_Used = false;
        
    }


    void addCard(Card& topcard) override{
        hand.push_back(topcard);
    }


    Card PlayCard(Card& topCard, bool& lowerthanfive, TextureManager& textureManager, SoundManager& soundManager) override {
    for (size_t i = 0; i < hand.size(); ++i) {
        Card c = hand[i];
        bool valid = lowerthanfive ? (c.getValue() < 5 || c.isPower()) : (c.getValue() >= topCard.getValue() || c.isPower());

        if (valid) {
            std::cout << Name << " (Bot) plays " << c.Convert() << "\n";
            ShowNotification(Name + " (Bot) plays " + c.Convert());
            hand.erase(hand.begin() + i);


            topCard = c; //update top card if valid card played
            soundManager.playPlaced(); //to fix sound desync issue

            // Show notification briefly
            float startTime = GetTime();
            while (GetTime() - startTime < 1.5f && !WindowShouldClose()) {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                
                drawPile(topCard, textureManager);
                DrawNotification(); // <-- Draw bot's move notification
                

                EndDrawing();
            }

            if (lowerthanfive) lowerthanfive = false;
            
            return c;
            
        }
    }

    return Card(-1, 'X');
}


};