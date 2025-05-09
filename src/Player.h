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
    vector <Card> blind;
    bool Blinds_Used;
    bool isBot;

    public:
    Player(string NameP = "User", bool flag = false){
        Name = NameP;
        isBot = flag;
        Blinds_Used = false;
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

    bool blindCardsUsed(){
        return Blinds_Used;
    }

    bool hasPlayableCard(Card& topcard, bool& lowerthanfive){
        for(Card card : hand){
            if(lowerthanfive){
                if((card.getValue() < 5) || card.isPower()){
                    return true;
                }
            } else {
                if(card.getValue() >= topcard.getValue() || card.isPower()){
                    return true;
                }
            }
        }
        return false;
    }

    //picks from deck
    void addCard(Card& topcard){
        hand.push_back(topcard);
        cout<<"Player.h: Card Added: "<<topcard.Convert()<<" added"<<endl;
    }

    void addBlind(Card& topcard){
        blind.push_back(topcard);
        cout<<"Player.h: Blinds Are Added"<<endl;
    }

    //picks from pile
    void PickUpCard(vector<Card>& table){
        hand.insert(hand.begin(), table.begin(), table.end());
        table.clear();
        for(size_t i=0; i<hand.size(); i++){
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

    void CallBlind(){
        Card temp = blind[blind.size() - 1];
        blind.erase(blind.begin() + (blind.size() - 1));
        cout<<"Blind Called: Blind Card Removed"<<endl;
        hand.push_back(temp);
        if(blind.empty()){
            Blinds_Used = true;
        }
    }

    virtual Card PlayCard(Card& topcard, bool& lowerthanfive){
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
        
        if(lowerthanfive){
            if(selected.getValue() < 5 || selected.isPower()){
                hand.erase(hand.begin() + choice);
                cout<<"Player.h: Card Removed "<<selected.Convert()<<endl;
                lowerthanfive = !lowerthanfive;
                return selected;
            } else {
                cout<<"Invalid Move. Must play < 5 or Power card."<<endl;
            }
        } else {
            if(!(selected.isGreater(topcard)) || selected.isPower()){
                hand.erase(hand.begin() + choice);
                cout<<"Player.h: Card Removed "<<selected.Convert()<<endl;
                return selected;
            } else {
                cout<<"Invalid Move, You Cannot Play this card"<<endl;
            }
        }

        }
    }

};