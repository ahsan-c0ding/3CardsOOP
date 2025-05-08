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

void drawCard(Player& p, Deck& d){
    Card temp = d.Draw();
    p.addCard(temp);
}

//Function to distribute cards to players at start of the game
void initialiseGame(){
    for(int i=0; i<3; i++){
    drawCard(user, cardDeck);
    drawCard(bot1, cardDeck);
    drawCard(bot2, cardDeck);
    drawCard(bot3, cardDeck);
    }
    
    table.push_back(nullcard);
}


//function to pick pile if no playable card (defacto turn function)
void checkHandagainstPile(Player &p, vector<Card> &pile){
    if(!p.hasPlayableCard(pile.back())){
        cout<<"Player: "<<p.getName()<<" has NO playable card"<<endl;
        cout<<"Main: Pickup Card called"<<endl;
        p.PickUpCard(pile);
        pile.push_back(nullcard);
    } else{
        cout<<"Player: "<<p.getName()<<" has playable card"<<endl;
        Card temp = nullcard;
        cout<<"Top Card: "<<pile.back().Convert()<<endl;
        temp = p.PlayCard(pile.back());
        pile.push_back(temp);
        drawCard(p, cardDeck);
    }
}


//runs until player has no card or all bots have no cards
void gameloop(){
    cout<<"Game Loop Running"<<endl;
    while(user.hasAnyCard() && (bot1.hasAnyCard() || bot2.hasAnyCard() || bot3.hasAnyCard())){
       checkHandagainstPile(user, table);
       checkHandagainstPile(bot1, table);
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

