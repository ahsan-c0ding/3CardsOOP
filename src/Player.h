#pragma once

#include <iostream>
#include <vector>
#include "Card.h"
#include "Deck.h"

using namespace std;

class Player{
    protected:
    string Name;
    vector <Card> hand;
    bool isBot;

    public:
    Player(string NameP = "User", bool flag = false){
        Name = NameP;
        isBot = flag;
        cout<<"Player.h: Player: "<<Name<<" created"<<endl;
    }

    bool hasAnyCard(){
        if (hand.size() == 0){
            return false;
        } else {
            return true;
        }
    }

    string getName(){
        return Name;
    }

    bool hasPlayableCard(Card& topcard){
        for(Card card : hand){
            if(card.getValue() >= topcard.getValue() || card.isPower()){
                return true;
            }
        }
        return false;
    }

    //picks from deck
    void addCard(Card& topcard){
        hand.push_back(topcard);
        cout<<"Player.h: Card Added: "<<topcard.Convert()<<" added"<<endl;
    }

    //picks from pile
    void PickUpCard(vector<Card>& table){
        hand.insert(hand.begin(), table.begin(), table.end());
        table.clear();
        for(int i=0; i<hand.size(); i++){
            if(hand[i].getValue() == -1){
                hand.erase(hand.begin() + i); //remove null card when picking up pile
            }
        }
        cout<<"Player.h: Pile Picked! "<<endl;
    }

    void DisplayCard(){
        cout<<endl;
        cout<<"Card in "<<Name<<"'s Hand:";
        int count = 1;
        for(Card card : hand){
            cout<<count<<": "<<card.Convert()<<" ";
            count++;
        }
    }

    virtual Card PlayCard(Card& topcard){
        while(true){
        DisplayCard();
        cout<<endl;
        cout<<"Select Card Index To Play"<<endl;
        size_t choice;
        cin>>choice;

        choice = choice - 1;
        if(choice < 0 || choice >= hand.size()){
            cout<<"Invalid Choice, Try Again"<<endl;
            continue;
        }

        Card selected = hand[choice];
        
        if(!(selected.isGreater(topcard)) || selected.isPower()){
            hand.erase(hand.begin() + choice);
            cout<<"Player.h: Card Removed "<<selected.Convert()<<endl;
            return selected;
        }
        else{
            cout<<"Invalid Move, You Cannot Play this card"<<endl;
        }

        }
    
    }

};