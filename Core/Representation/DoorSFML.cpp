//
// Created by Ilias Ahmindach on 13/12/2020.
//

#include "DoorSFML.h"
#include "../Logic/Random.h"




void DungeonRunnerSFML::DoorSFML::update() {
    if(isOpen){
        door->setTexture(&*doorStates["door_o"]);
        noclip = true;
    }
    else{
        door->setTexture(&*doorStates["door_c"]);
    }
    std::pair<float,float> pixelC = Transformation::toPixel(gWindow, ePosition.first, ePosition.second);
    door->setPosition(pixelC.first,pixelC.second);
    lFrame.setPosition(door->getPosition().x-door->getSize().x/2.0+lFrame.getSize().x/2.0,door->getPosition().y+lFrame.getSize().y);
    rFrame.setPosition(door->getPosition().x+door->getSize().x/2.0-rFrame.getSize().x/2.0,door->getPosition().y+rFrame.getSize().y);
}

DungeonRunnerSFML::DoorSFML::DoorSFML(std::shared_ptr<sf::RectangleShape> &door,
                                      const std::shared_ptr<sf::RenderWindow> &gWindow,
                                      const std::map<std::string, std::shared_ptr<sf::Texture>> &doorStates) : door(
        door), gWindow(gWindow), doorStates(doorStates) {
    door->setOrigin(door->getSize().x/2.0,door->getSize().y);
    std::pair<float,float> tSize = Transformation::toCoords(gWindow,door->getSize().x,door->getSize().y);
    tSize.first+=Transformation::getWSize().first/2.0;
    tSize.second+=Transformation::getWSize().second/2.0;
    tSize.second = 1 - tSize.second;
    eSize = tSize;
    sf::Texture df = *DoorSFML::doorStates["door_o"];
    sf::Vector2f lfSize(door->getSize().x*3/32.0,door->getSize().y*0.5);
    sf::Vector2f rfSize(door->getSize().x*3/32.0,door->getSize().y*0.5);
    lFrame = sf::RectangleShape(lfSize);
    rFrame = sf::RectangleShape(rfSize);
    lFrame.setOrigin(lFrame.getSize().x/2.0,door->getSize().y);
    rFrame.setOrigin(rFrame.getSize().x/2.0,door->getSize().y);
    lFrame.setFillColor(sf::Color::Transparent);
    rFrame.setFillColor(sf::Color::Transparent);
    eType = "Door";


}

void DungeonRunnerSFML::DoorSFML::display() {
    gWindow->draw(*door);
    gWindow->draw(lFrame);
    gWindow->draw(rFrame);
}

void DungeonRunnerSFML::DoorSFML::action() {
    if(isLocked or isOpen) return;
    if(Random::generateRandomChance()<=0.6) {
        isOpen = true;
        return;
    }
    isLocked = true;
    door->setFillColor(sf::Color::Red);
}
