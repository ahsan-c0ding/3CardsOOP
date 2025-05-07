#include <iostream>
using namespace std;
#include <raylib.h>
#include "Card.h"
#include "Player.h"
#include "BotPlayer.h"

int screenWidth = 800;
int screenHeight = 600;

//Intialising Players
Player user("HumanUser",true);
BotPlayer bot1;
BotPlayer bot2;
BotPlayer bot3;
Deck cardDeck;
//Function to distribute cards to players at start of the game

void initialiseGame(){
    Card topCard = cardDeck.Draw();
    user.addCard(topCard);
    topCard = cardDeck.Draw();
    bot1.addCard(topCard);
    topCard = cardDeck.Draw();
    bot2.addCard(topCard);
    topCard = cardDeck.Draw();
    bot3.addCard(topCard);
    
}



int main(){
    cout<<"Hello World!"<<endl;
    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "Teen Patti");

    initialiseGame();

    while(WindowShouldClose() == false){
        //DrawCircle(screenWidth/2,screenHeight/2,15,BLACK);
        DrawText("Teen Patti Placeholder",(screenWidth/4),screenHeight/2,12,GREEN);
        EndDrawing();
    }
    
    
}

