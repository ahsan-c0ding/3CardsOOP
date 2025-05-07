#pragma once

#include <iostream>
#include <vector>
#include "Card.h"
#include <random>
#include <algorithm>

using namespace std;

class Deck{
    private:
    vector <Card> cards;
    
    public:

    Deck(){
        char suits[] = {'H', 'S', 'D', 'C'};
        for(char suit : suits){
            for(int i = 1; i < 14; i++){
                cards.push_back(Card(i, suit));
            }
        }
        Shuffle();
    }

    void Shuffle(){
        random_device rd;
        mt19937 g(rd());
        shuffle(cards.begin(), cards.end(), g);
        cout<<"Deck.h: Deck Shuffled"<<endl;
    }

    Card Draw(){
        Card top = cards.back();
        cards.pop_back();
        cout<<"Deck.h: Card Drawn"<<endl;
        return top;
    }

    bool IsEmpty(){
        return cards.empty();
    }

};