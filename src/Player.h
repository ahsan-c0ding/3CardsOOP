#pragma once

#include <iostream>
#include <vector>
#include <Card.h>
#include <Deck.h>

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
    }

    bool hasPlayableCard(Card& topcard){
        for(Card card : hand){
            if(card.isGreater(topcard) || card.isPower()){
                return true;
            }
            else{
                return false;
            }
        }
    }

    bool addCard(Card& topcard){
        hand.push_back(topcard);
    }

    void PickUpCard(vector<Card>& table){
        hand.insert(hand.begin(), table.begin(), table.end());
        table.clear();
    }

    void DisplayCard(){
        cout<<endl;
        cout<<"Card in "<<Name<<"'s Hand:";
        int count = 1;
        for(Card card : hand){
            cout<<count<<card.Convert()<<" ";
            count++;
        }
    }

    virtual Card PlayCard(Card& topcard){
        while(true){
        DisplayCard();
        cout<<endl;

        cout<<"Select Card Index To Play"<<endl;
        int choice;
        cin>>choice;

        if(choice < 0 || choice >= hand.size()){
            cout<<"Invalid Choice, Try Again"<<endl;
            continue;
        }

        Card selected = hand[choice];
        
        if(selected.isGreater(topcard) || selected.isPower()){
            hand.erase(hand.begin() + choice);
            return selected;
        }
        else{
            cout<<"Invalid Move, You Cannot Play this card"<<endl;
        }

        }
    
    }

};