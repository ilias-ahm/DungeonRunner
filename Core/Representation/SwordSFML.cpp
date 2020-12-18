//
// Created by Ilias Ahmindach on 17/12/2020.
//

#include "SwordSFML.h"

DungeonRunnerSFML::Sword::Sword(std::shared_ptr<sf::RenderWindow> &gWindow):
                                gWindow(gWindow) {
    sf::Vector2f swordSize;
    swordTexture = std::make_shared<sf::Texture>();
    swordTexture->loadFromFile("../Resources/obstaclesSprites/swords/sword_1.png");
    swordSize.x = gWindow->getSize().x * 0.0390625;
    swordSize.y = gWindow->getSize().y * 0.08203125;
    sword = std::make_shared<sf::RectangleShape>(swordSize);
    sword->setOrigin(sword->getSize().x/2.0,sword->getSize().y);
    sword->setTexture(&*swordTexture);
    std::pair<float,float> tSize = Transformation::toCoords(gWindow,sword->getSize().x,sword->getSize().y);
    tSize.first+=Transformation::getWSize().first/2.0;
    tSize.second+=Transformation::getWSize().second/2.0;
    tSize.second = 1 - tSize.second;
    eSize = tSize;
    eType = "Sword";
}

void DungeonRunnerSFML::Sword::update() {
    std::pair<float,float> pixelPos = Transformation::toPixel(gWindow,ePosition.first,ePosition.second);
    sword->setPosition(pixelPos.first,pixelPos.second);
}

void DungeonRunnerSFML::Sword::display() {
    gWindow->draw(*sword);
}
