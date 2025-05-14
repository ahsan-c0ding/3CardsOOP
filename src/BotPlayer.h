#pragma once

#include <iostream>
#include "Player.h"
#include "Card.h"
#include "Deck.h"

using namespace std;

class BotPlayer : public Player{
    public:
    BotPlayer(string bot_name = "Bot", bool flag = true){
        Name = bot_name;
        isBot = flag;
        Blinds_Used = false;
        
    }


    Card PlayCard(Card& topCard, bool& lowerthanfive, TextureManager& textureManager) override{ 
        for (size_t i = 0; i < hand.size(); ++i) {
            Card c = hand[i];
            if(lowerthanfive){
                if(c.getValue() < 5 || c.isPower()){
                    std::cout << Name << " (Bot) plays " << c.Convert() << "\n";
                    hand.erase(hand.begin() + i);
                    lowerthanfive = !lowerthanfive;
                    return c;
                }
            } else {
                if (!(c.isGreater(topCard)) || c.isPower()) {
                    std::cout << Name << " (Bot) plays " << c.Convert() << "\n";
                    hand.erase(hand.begin() + i);
                    return c;
                }
            }
        }

        return Card(-1, 'X');

    }

};