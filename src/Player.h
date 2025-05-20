#pragma once

#include <iostream>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Texture.h"
#include "Sound.h"

using namespace std;




class Player{
    protected:
    string Name;
    vector <Card> hand;
    vector <Card> blind;
    vector <Card> Seenblind;
    bool Blinds_Used;
    bool isBot;
    string notificationMessage = "";
    float notificationStartTime = 0.0f;
    float notificationDuration = 2.0f; // show for 2 seconds
    bool move_sucess;
    bool hasSeenBlinds;

    public:
    Player(string NameP = "User", bool flag = false){
        Name = NameP;
        isBot = flag;
        Blinds_Used = false;
        cout<<"Player.h: Player: "<<Name<<" created"<<endl;
    }

    bool getMove_Sucess(){
        return move_sucess;
    }

    bool hasAnyCard(){
        if (hand.size() == 0){
            return false;
        } else {
            return true;
        }
    }
    bool getIsBot(){
        return isBot;
    }

    bool gethasSeenBlinds(){
        if(Seenblind.size()==0){
            hasSeenBlinds = false;
        } else {
            hasSeenBlinds = true;
        }
        return hasSeenBlinds;
    }

    string getName(){
        return Name;
    }

    void ShowNotification(const string& msg) {
        notificationMessage = msg;
        notificationStartTime = GetTime();
    }

    void DrawNotification() {
    if (!notificationMessage.empty() && (GetTime() - notificationStartTime < notificationDuration)) {
            int fontSize = 25;
            int padding = 10;

            int textWidth = MeasureText(notificationMessage.c_str(), fontSize);
            int x = GetScreenWidth() - textWidth - padding * 2;
            int y = padding;

            // Background rectangle
            DrawRectangle(x - padding, y - padding / 2, textWidth + padding * 2, fontSize + padding, Fade(DARKGRAY, 0.8f));
            
            // Text
            DrawText(notificationMessage.c_str(), x, y, fontSize, RAYWHITE);
        }
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
    void virtual addCard(Card& topcard){
        hand.push_back(topcard);
        string c = topcard.Convert();
        string text = Name + " picked up card: " + c; 
        ShowNotification(text);
    }

    void addBlind(Card& topcard){
        blind.push_back(topcard);
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
        ShowNotification(Name+" Pile Picked");
    }

//seen blinds pickup logic:
    void PickSeenBlinds(){
        if(hand.size() == 0 && Seenblind.size() > 0){
            while(!Seenblind.empty()){
                hand.push_back(Seenblind.back());
                Seenblind.pop_back();
            }
            ShowNotification(Name+ " Seen Blinds Picked");
        }
    }

    void drawPile(Card topCard, TextureManager& textureManager) {
        if (topCard.getValue() == -1) return;

        const int cardWidth = 120;
        const int cardHeight = 160;
        float pileX = GetScreenWidth() / 2 - cardWidth / 2;
        float pileY = GetScreenHeight() / 2 - cardHeight / 2;

        std::string cardId = topCard.Convert();
        Texture2D tex = textureManager.Get(cardId);

        Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
        Rectangle dest = { pileX, pileY, (float)cardWidth, (float)cardHeight };
        Vector2 origin = { 0, 0 };
        DrawTexturePro(tex, source, dest, origin, 0.0f, WHITE);
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
        ShowNotification("Blind Called, Blind Cards Removed");
        hand.push_back(temp);
        if(blind.empty()){
            Blinds_Used = true;
        }
    }

    virtual Card PlayCard(Card& topcard, bool& lowerthanfive, TextureManager& textureManager, SoundManager& soundManager) {
    move_sucess = false;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(("Player: " + Name).c_str(), 20, 20, 20, BLACK);
        DrawText("Click a card to play it", 20, 50, 20, DARKGRAY);

        // 👉 CALL drawPile() to show the current top card
        drawPile(topcard, textureManager);

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

            std::string cardId = hand[i].Convert();
            Texture2D tex = textureManager.Get(cardId);

            Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
            Rectangle dest = { cardRect.x, cardRect.y, (float)cardWidth, (float)cardHeight };
            Vector2 origin = { 0, 0 };

            DrawTexturePro(tex, source, dest, origin, 0.0f, WHITE);

            // Dynamically scale the card label text and center it
            string label = hand[i].Convert();
            int maxWidth = cardWidth - 20;
            int fontSize = 20;

            // Shrink text if it’s too wide
            while (MeasureText(label.c_str(), fontSize) > maxWidth && fontSize > 10) {
                fontSize--;
            }

          
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
                    string c = selected.Convert();
                    ShowNotification(Name+ " Card Removed: "+c);
                    move_sucess = true;
                    soundManager.playSucess();

                    if (lowerthanfive) lowerthanfive = false;
                    EndDrawing();
                    return selected;
                } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), cardRect)) {
                    // Only wait *after* clicking an invalid card
                    ShowNotification("Invalid move!");
                    soundManager.playFail();
                    move_sucess = false;
                    DrawNotification();
                    EndDrawing();
                    WaitTime(1.5);
                    continue;
                }
            }
        }
        DrawNotification();
    

        EndDrawing();
    }

    return Card(-1, 'X');
}



};