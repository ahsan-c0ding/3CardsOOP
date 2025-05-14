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
        if(Value == 14){
            num = "A";
        }
        else if(Value == 11){
            num = "J";
        }

        else if(Value == 12){
            num = "Q";
        }
        
        else if(Value == 13){
            num = "K";
        }

        else{
            num = to_string(Value);
        }
           return num + House;
    
        
    }

    int getValue(){
        return Value;
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