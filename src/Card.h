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
        bool isSpace = false; //for formatting purposes only
        if(Value == 14){
            num = "Ace";
            isSpace = true;
        }
        else if(Value == 11){
            num = "Jack";
            isSpace = true;
        }

        else if(Value == 12){
            num = "Queen";
            isSpace = true;
        }
        
        else if(Value == 13){
            num = "King";
            isSpace = true;
        }

        else{
            num = to_string(Value);
        }
        if(isSpace){
            return num + " " + House;
        } else {
            return num + House;
        }
        
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