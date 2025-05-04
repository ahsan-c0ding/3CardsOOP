#pragma once

#include <iostream>
#include <Player.h>
#include <Card.h>
#include <Deck.h>

using namespace std;

class BotPlayer : protected Player{
    BotPlayer(string bot_name = "Bot", bool flag = true){
        Name = bot_name;
        isBot = flag;
        
    }


    Card PlayCard(Card& topCard) override{  
        for (int i = 0; i < hand.size(); ++i) {
            Card c = hand[i];
            if (c.isGreater(topCard) || c.isPower()) {
                std::cout << Name << " (Bot) plays " << c.Convert() << "\n";
                hand.erase(hand.begin() + i);
                return c;
            }
        }

        return Card(-1, 'X');

    }

};