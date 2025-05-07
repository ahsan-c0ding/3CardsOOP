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

//Function to distribute cards to players at start of the game
void drawCard(Player& p, Deck& d){
    Card temp = d.Draw();
    p.addCard(temp);
}

void initialiseGame(){
    for(int i=0; i<3; i++){
    drawCard(user, cardDeck);
    drawCard(bot1, cardDeck);
    drawCard(bot2, cardDeck);
    drawCard(bot3, cardDeck);
    }
}

//runs until player has no card or all bots have no cards
void gameloop(){
    cout<<"Game Loop Running"<<endl;
    while(user.hasAnyCard() && (bot1.hasAnyCard() || bot2.hasAnyCard() || bot3.hasAnyCard())){
        if(!table.size()){
            Card nullCard(2,'D');
            user.PlayCard(nullCard);
            bot1.PlayCard(table.back());
        }
        user.PlayCard(table.back());
        bot1.PlayCard(table.back());
    }
    cout<<"Game Loop Ended"<<endl;
}


int main(){
    cout<<"Hello World!"<<endl;
    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "Teen Patti");

    initialiseGame();
    cout<<endl;
    user.DisplayCard();

    while(WindowShouldClose() == false){
        //DrawCircle(screenWidth/2,screenHeight/2,15,BLACK);
        DrawText("Teen Patti Placeholder",(screenWidth/4),screenHeight/2,24,GREEN);
        gameloop();
        EndDrawing();
    }
    
    
}

