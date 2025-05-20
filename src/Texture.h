#pragma once

#include "raylib.h"
#include <map>
#include <string>
#include <iostream>

class TextureManager {
private:
    std::map<std::string, Texture2D> textures;

public:
    void LoadCardTextures(const std::string& folder = "cards/") {
        const char suits[] = {'H','C','S','D'};
        const std::string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

        for (char s : suits) {
            for (const std::string& r : ranks) {
                std::string id = r + s;                   // e.g., "10H"
                std::string path = folder + id + ".png";  // cards/10H.png
                Texture2D tex = LoadTexture(path.c_str());
                textures[id] = tex;
                std::cout << "Loaded texture: " << path << std::endl;
            }
        }

        // Optional: fallback "null" card image
        textures["null"] = LoadTexture((folder + "null.png").c_str());
    }

    Texture2D Get(const std::string& id) {
        if (textures.count(id)) return textures[id];
        return textures["null"];
    }

    void UnloadAll() {
        for (auto& pair : textures) {
            UnloadTexture(pair.second);
        }
        textures.clear();
    }

    ~TextureManager() {
        UnloadAll();
    }
};