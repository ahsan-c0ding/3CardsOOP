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
    vector <Card> Seenblind;
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

    void addSeenBlind(Card& topcard){
        Seenblind.push_back(topcard);
        cout<<"Player.h: Seen Blinds Are Added"<<endl;
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

//seen blinds pickup logic:
    void PickSeenBlinds(){
        if(hand.size() == 2 && Seenblind.size() > 0){
            while(!Seenblind.empty()){
                hand.push_back(Seenblind.back());
                Seenblind.pop_back();
            }
            cout<<"Player.h: Seen Blinds Picked!"<<endl;
        }
    }

    void drawPile(Card topCard){
        // --- Draw top card from the pile in the center ---
    if (!(topCard.getValue() == -1 )) {
        const int pileCardWidth = 120;
        const int pileCardHeight = 160;
        float pileX = GetScreenWidth() / 2 - pileCardWidth / 2;
        float pileY = GetScreenHeight() / 2 - pileCardHeight / 2;

        Rectangle pileCardRect = { pileX, pileY, (float)pileCardWidth, (float)pileCardHeight };
        DrawRectangleRec(pileCardRect, GOLD);
        DrawRectangleLinesEx(pileCardRect, 3, DARKGRAY);

        string pileLabel = "Top: " + topCard.Convert();
        DrawText(pileLabel.c_str(),
                pileX + 10,
                pileY + pileCardHeight / 2 - 10,
                20,
                BLACK);
    }
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

    virtual Card PlayCard(Card& topcard, bool& lowerthanfive) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(("Player: " + Name).c_str(), 20, 20, 20, BLACK);
        DrawText("Click a card to play it", 20, 50, 20, DARKGRAY);

        // 👉 CALL drawPile() to show the current top card
        drawPile(topcard);

        const int cardWidth = 80;
        const int cardHeight = 120;
        const int padding = 20;
        int startX = (GetScreenWidth() - (hand.size() * (cardWidth + padding))) / 2;
        int y = GetScreenHeight() - cardHeight - 40;

        for (size_t i = 0; i < hand.size(); ++i) {
            Rectangle cardRect = {
                (float)(startX + i * (cardWidth + padding)),
                (float)y,
                (float)cardWidth,
                (float)cardHeight
            };

            DrawRectangleRec(cardRect, LIGHTGRAY);
            DrawRectangleLinesEx(cardRect, 2, BLACK);

            // Dynamically scale the card label text and center it
string label = hand[i].Convert();
int maxWidth = cardWidth - 20;
int fontSize = 20;

// Shrink text if it’s too wide
while (MeasureText(label.c_str(), fontSize) > maxWidth && fontSize > 10) {
    fontSize--;
}

// Center horizontally and vertically
int textWidth = MeasureText(label.c_str(), fontSize);
float textX = cardRect.x + (cardWidth - textWidth) / 2;
float textY = cardRect.y + (cardHeight - fontSize) / 2;

DrawText(label.c_str(), textX, textY, fontSize, BLACK);



            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), cardRect)) {
                Card selected = hand[i];

                bool valid = false;
                if (lowerthanfive) {
                    valid = selected.getValue() < 5 || selected.isPower();
                } else {
                    valid = selected.getValue() >= topcard.getValue() || selected.isPower();
                }

                if (valid) {
                    hand.erase(hand.begin() + i);
                    cout << "Player.h: Card Removed " << selected.Convert() << endl;

                    if (lowerthanfive) lowerthanfive = false;
                    EndDrawing();
                    return selected;
                } else {
                    DrawText("Invalid move!", 20, 80, 20, RED);
                }
            }
        }

        EndDrawing();
    }

    return Card(-1, 'X');
}



};