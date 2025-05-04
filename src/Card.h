#pragma once 
#include <iostream>
using namespace std;

class Card{
    int Value;
    char House;
    bool isPowerCard;

    public:
    Card(int valueP, char HouseP){
        Value = valueP;
        House = HouseP;
        isPowerCard = valueP == 2 || valueP == 5 || valueP == 10;
    }

    string Convert(){
        string num;
        if(Value == 1){
            num = "Ace";
        }
        else if(Value == 11){
            num = "Jack";
        }

        else if(Value == 12){
            num = "Queen";
        }
        
        else if(Value == 13){
            num = "King";
        }

        else{
            num = to_string(Value);
        }

        return num + " " + House;
    }

    bool isGreater(Card& other){
        if(other.Value > Value){
            return true;
        }
        else{
            return false;
        }
    }

    bool isPower(){
        return isPowerCard;
    }
};