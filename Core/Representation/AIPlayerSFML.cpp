//
// Created by Ilias Ahmindach on 18/12/2020.
//

#include "AIPlayerSFML.h"


DungeonRunnerSFML::AIPlayer::AIPlayer(
        std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities,
        std::shared_ptr<sf::RenderWindow> &gWindow): gameEntities(gameEntities),gWindow(gWindow) {
    aiPlayer = sf::RectangleShape(sf::Vector2f(gWindow->getSize().x/12.0,gWindow->getSize().y/8.0));
    aiTexture.loadFromFile("../Resources/characterSprites/aisprite.png");
    std::pair<float,float> aiPos(-0.25,-6.7);
    while(true){
        bool correctPos = true;
        for(auto &entity:gameEntities){
            if(entity->getEPosition() == aiPos){
                aiPos.first+=0.5;
                correctPos = false;
            }
        }
        if(correctPos) break;
    }
    ePosition = aiPos;
    std::pair<float,float> tSize = Transformation::toCoords(gWindow,aiPlayer.getSize().x,aiPlayer.getSize().y);
    tSize.first+=Transformation::getWSize().first/2.0;
    tSize.second+=Transformation::getWSize().second/2.0;
    tSize.second = 1 - tSize.second;
    eSize = tSize;
    aiPos = Transformation::toPixel(gWindow,aiPos.first,aiPos.second);
    aiPlayer.setOrigin(aiPlayer.getSize().x/2.0,aiPlayer.getSize().y);
    aiPlayer.setPosition(aiPos.first,aiPos.second);
    aiSpeed = 0.2;
    eType = "AI";
}

void DungeonRunnerSFML::AIPlayer::display() {
    gWindow->draw(aiPlayer);
}

void DungeonRunnerSFML::AIPlayer::update() {
    std::pair<float,float> pixelC = Transformation::toPixel(gWindow, ePosition.first, ePosition.second);
    aiPlayer.setPosition(pixelC.first,pixelC.second);
}
