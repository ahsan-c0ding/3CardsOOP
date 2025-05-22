#include <iostream>
using namespace std;
#include <raylib.h>
#include "Card.h"
#include "Player.h"
#include "BotPlayer.h"
#include "Texture.h"
#include "Sound.h"

int screenWidth = 800;
int screenHeight = 600;

TextureManager textureManager;

SoundManager soundManager;



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

const int MENU = 0;
const int PLAYING = 1;
const int TUTORIAL = 2;
const int EXIT = -1;

int currentGameState = MENU;


void ShowMainMenu() {
    BeginDrawing();
    ClearBackground(DARKGREEN);

    DrawText("Teen Patti", screenWidth / 2 - 100, 100, 40, GOLD);

    // Define button rectangles
    Rectangle playButton = { screenWidth / 2 - 100, 200, 200, 40 };
    Rectangle tutorialButton = { screenWidth / 2 - 100, 260, 200, 40 };
    Rectangle exitButton = { screenWidth / 2 - 100, 320, 200, 40 };

    // Get mouse position
    Vector2 mousePos = GetMousePosition();

    // Draw buttons with hover effect
    DrawRectangleRec(playButton, CheckCollisionPointRec(mousePos, playButton) ? DARKGRAY : GRAY);
    DrawText("Play", playButton.x + 70, playButton.y + 10, 20, WHITE);

    DrawRectangleRec(tutorialButton, CheckCollisionPointRec(mousePos, tutorialButton) ? DARKGRAY : GRAY);
    DrawText("Tutorial", tutorialButton.x + 55, tutorialButton.y + 10, 20, WHITE);

    DrawRectangleRec(exitButton, CheckCollisionPointRec(mousePos, exitButton) ? DARKGRAY : GRAY);
    DrawText("Exit Game", exitButton.x + 50, exitButton.y + 10, 20, WHITE);

    EndDrawing();

    // Handle mouse input
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mousePos, playButton)) {
            currentGameState = PLAYING;
        } else if (CheckCollisionPointRec(mousePos, tutorialButton)) {
            currentGameState = TUTORIAL;
        } else if (CheckCollisionPointRec(mousePos, exitButton)) {
            currentGameState = EXIT;
        }
    }
}

void ShowTutorial() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Teen Patti Tutorial", 50, 50, 30, DARKBLUE);
    DrawText("1. Each player is dealt 3 cards in-hand initially.", 50, 120, 20, BLACK);
    DrawText("2. You play cards in turns onto the pile.", 50, 150, 20, BLACK);
    DrawText("3. Match or beat the top card, or pick up the pile.", 50, 180, 20, BLACK);
    DrawText("4. Special Cards:\n   - 2: Play Again\n   - 5: Reverse & Lower than 5\n   - 10: Burn Pile", 50, 210, 20, DARKGRAY);
    DrawText("5. Once your hand and deck is empty, pick up the blind cards!.", 50, 300, 20, BLACK);
    DrawText("Click anywhere or press BACKSPACE to return to the menu.", 50, 340, 20, MAROON);
    EndDrawing();

    if (IsKeyPressed(KEY_BACKSPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        currentGameState = MENU;
    }
}


void drawCard(Player& p, Deck& d){
    if(d.IsEmpty() == false){
        Card temp = d.Draw();
        p.addCard(temp);
    }
    else{
        cout<<"Deck Is Empty"<<endl;
        p.ShowNotification("Deck Is Empty");
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

bool isOutOfCards(Player& p) {
    return !p.hasAnyCard() && p.blindCardsUsed() && !p.gethasSeenBlinds();
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
    if(!pile.empty()){
        p.drawPile(pile.back(), textureManager);
    }
    if(!p.hasAnyCard() && !p.blindCardsUsed()){
            p.CallBlind();
        }

    if(!p.hasPlayableCard(pile.back(), lowerthanfive)){
        cout<<"Player: "<<p.getName()<<" has NO playable card"<<endl;
        p.ShowNotification("Player: "+p.getName()+" has NO playable card");
        cout<<"Main: Pickup Card called"<<endl;
        p.PickUpCard(pile);
        pile.push_back(nullcard);
    } 

    else{
        cout<<"Player: "<<p.getName()<<" has playable card"<<endl;
        Card temp = nullcard;
        cout<<"Top Card: "<<pile.back().Convert()<<endl;
        while (true) {
        temp = p.PlayCard(pile.back(), lowerthanfive, textureManager, soundManager);

    if (temp.getValue() == -1) {
        // No card played (or invalid), exit loop
        break;
    }

    pile.push_back(temp);

    if (temp.getValue() == 2) {
    cout << "Power Card 2 Played, Play Another Card" << endl;
    p.ShowNotification("Power Card 2 Played, Play Another Card");

    drawCard(p, cardDeck);
    drawCard(p, cardDeck);

    if (!p.hasPlayableCard(pile.back(), lowerthanfive)) {
        cout << "No playable card after drawing, ending turn." << endl;
        p.ShowNotification("No playable card after drawing, ending turn.");
        break; // Prevent infinite loop of no playable card
    }

    continue; // Allow another card to be played
}


    if (temp.getValue() == 10) {
        cout << "Pile is Burned" << endl;
        p.ShowNotification("Pile is Burned");
        pile.clear();
        pile.push_back(nullcard);
        drawCard(p, cardDeck);
        break;
    }

    if (temp.getValue() == 5) {
        cout << "Order is Reverse, Next Card Should be Lower than 5" << endl;
        p.ShowNotification("Order is Reverse, Next Card Should be Lower than 5");
        ReverseOrder = !ReverseOrder;
        lowerthanfive = true;
        drawCard(p, cardDeck);
        break;
    }

    // If it's a normal card, just draw one and end turn
    drawCard(p, cardDeck);
    break;
}

   if (!p.hasAnyCard() && p.gethasSeenBlinds()) {
    p.PickSeenBlinds();
}

}
}


//runs until player has no card or all bots have no cards
void gameloop(){
    cout << "Game Loop Running" << endl;

    vector<Player*> turnOrder = {&user, &bot1, &bot2, &bot3};  // Player turn order
    static int index = 0;  // Track current player's index in turn order

    // Process one player's turn per frame
    if (!WindowShouldClose() &&
        !isOutOfCards(user) &&
        !isOutOfCards(bot1) &&
        !isOutOfCards(bot2) &&
        !isOutOfCards(bot3)) {

        // Process the current player's turn
        Player* currentPlayer = turnOrder[index];
        if (turnOrder[index] == &bot1 || turnOrder[index] == &bot2 || turnOrder[index] == &bot3) {
            WaitTime(0.5); // Bot delay here
        }

        // Only clear the background if it's the human player's turn.
        if (currentPlayer == &user) {
            ClearBackground(RAYWHITE);  // Clear the background when human plays
        } else {
            // Keep the background the same if it's a bot's turn
            DrawText("Bot's turn", 20, 20, 20, DARKGRAY);  // Show which bot is playing
        }

        checkHandagainstPile(*currentPlayer, table);  // Let the player act (draw cards, play, etc.)

        // Advance to the next player
        if (ReverseOrder) {
            index = (index - 1 + turnOrder.size()) % turnOrder.size();
        } else {
            index = (index + 1) % turnOrder.size();
        }
    } else {
        // Handle game end scenario
        cout << "Game Over!" << endl;
    }
}





int main() {
    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "Teen Patti");
    InitAudioDevice();
    SetMasterVolume(1.0f);

    soundManager.Load();
    textureManager.LoadCardTextures("cards/");

    while (!WindowShouldClose() && currentGameState != EXIT) {
        if (currentGameState == MENU) {
            ShowMainMenu();
        } 
        else if (currentGameState == TUTORIAL) {
            ShowTutorial();
        } 
        else if (currentGameState == PLAYING) {
            initialiseGame();

            while (!WindowShouldClose()) {
                gameloop();
            }

            currentGameState = EXIT;
        }
    }

    soundManager.Unload();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
