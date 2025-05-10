#include <iostream>
using namespace std;
#include <raylib.h>
#include "Card.h"
#include "Player.h"
#include "BotPlayer.h"

int screenWidth = 800;
int screenHeight = 600;

//Intialising Players
Player user("Human User",false);
BotPlayer bot1;
BotPlayer bot2;
BotPlayer bot3;
Deck cardDeck; //Deck of Cards
vector <Card> table; //Pile of cards on table

Card nullcard(-1,'X');

bool ReverseOrder = false;
bool lowerthanfive = false;

void drawCard(Player& p, Deck& d){
    if(d.IsEmpty() == false){
        Card temp = d.Draw();
        p.addCard(temp);
    }
    else{
        cout<<"Deck Is Empty"<<endl;
    }
}

void drawBlind(Player&p, Deck& d){
    Card temp = d.Draw();
    p.addBlind(temp);
}

void drawSeenBlind(Player&p, Deck& d){
    Card temp = d.Draw();
    p.addSeenBlind(temp);
}

//Function to distribute cards to players at start of the game
void initialiseGame(){
    for(int i=0; i<3; i++){
    drawCard(user, cardDeck);
    drawCard(bot1, cardDeck);
    drawCard(bot2, cardDeck);
    drawCard(bot3, cardDeck);
    }

    for(int i = 0; i<3; i++){
        drawBlind(user, cardDeck);
        drawBlind(bot1, cardDeck);
        drawBlind(bot2, cardDeck);
        drawBlind(bot3, cardDeck);
    }

    for(int i = 0; i<3; i++){
        drawSeenBlind(user, cardDeck);
        drawSeenBlind(bot1, cardDeck);
        drawSeenBlind(bot2, cardDeck);
        drawSeenBlind(bot3, cardDeck);
    }
    
    table.push_back(nullcard);
}


//function to pick pile if no playable card (defacto turn function)
void checkHandagainstPile(Player &p, vector<Card> &pile){
    if(!p.hasAnyCard() && !p.blindCardsUsed()){
            p.CallBlind();
        }

    if(!p.hasPlayableCard(pile.back(), lowerthanfive)){
        cout<<"Player: "<<p.getName()<<" has NO playable card"<<endl;
        cout<<"Main: Pickup Card called"<<endl;
        p.PickUpCard(pile);
        pile.push_back(nullcard);
    } 

    else{
        cout<<"Player: "<<p.getName()<<" has playable card"<<endl;
        Card temp = nullcard;
        cout<<"Top Card: "<<pile.back().Convert()<<endl;
        temp = p.PlayCard(pile.back(), lowerthanfive);
        if(temp.getValue() == 2){
            pile.push_back(temp);
            cout<<"Power Card 2 Played, Play Another Card"<<endl;
            temp = p.PlayCard(pile.back(), lowerthanfive);
            pile.push_back(temp);
            drawCard(p, cardDeck);
            drawCard(p, cardDeck);
        }

        else if(temp.getValue() == 10){
            pile.push_back(temp);
            pile.clear();
            cout<<"Pile is Burned"<<endl;
            pile.push_back(nullcard);
            drawCard(p, cardDeck);
        }

        else if(temp.getValue() == 5){
            pile.push_back(temp);
            cout<<"Order is Reverse, Next Card Should be Lower than 5"<<endl;
            ReverseOrder = !ReverseOrder;
            lowerthanfive = true;
            drawCard(p, cardDeck);
        }

        else{
            pile.push_back(temp);
            drawCard(p, cardDeck);
        }
    }
    p.PickSeenBlinds();
}


//runs until player has no card or all bots have no cards
void gameloop(){
    cout<<"Game Loop Running"<<endl;

    vector<Player*> turnOrder = {&user, &bot1, &bot2, &bot3};
    int index = 0;
    while((user.hasAnyCard() || !user.blindCardsUsed()) && (bot1.hasAnyCard() || !bot1.blindCardsUsed()) && (bot2.hasAnyCard() || !bot2.blindCardsUsed()) && (bot3.hasAnyCard() || !bot3.blindCardsUsed())){
        checkHandagainstPile(*turnOrder[index], table);

        if (ReverseOrder) {
            index = (index - 1 + turnOrder.size()) % turnOrder.size();
        } 
        else {
            index = (index + 1) % turnOrder.size();
        }
    }
    cout<<"Game Loop Ended"<<endl;
}



int main(){
    cout<<"Hello World!"<<endl;
    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "Teen Patti");

    initialiseGame();
    cout<<endl;
    gameloop();

    return 0;
}

