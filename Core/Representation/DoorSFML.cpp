//
// Created by Ilias Ahmindach on 13/12/2020.
//

#include "DoorSFML.h"

void DungeonRunnerSFML::DoorSFML::setDoorTexture(const std::shared_ptr<sf::Texture> &doorTexture) {
    DoorSFML::doorTexture = doorTexture;
}

void DungeonRunnerSFML::DoorSFML::setDoor(const std::shared_ptr<sf::RectangleShape> &door) {
    DoorSFML::door = door;
}



void DungeonRunnerSFML::DoorSFML::update() {
    if(isOpen){
        door->setTexture(&*doorStates["door_o"]);
    }
    else{
        door->setTexture(&*doorStates["door_o"]);
    }
    lFrame.setPosition(door->getPosition());
    rFrame.setPosition(door->getPosition().x+door->getSize().x-rFrame.getSize().x,door->getPosition().y);
}

DungeonRunnerSFML::DoorSFML::DoorSFML(const std::shared_ptr<sf::RectangleShape> &door,
                                      const std::shared_ptr<sf::RenderWindow> &gWindow,
                                      const std::map<std::string, std::shared_ptr<sf::Texture>> &doorStates) : door(
        door), gWindow(gWindow), doorStates(doorStates) {
    sf::Texture df = *DoorSFML::doorStates["door_o"];
    sf::Vector2f lfSize(door->getSize().x*7/32.0,door->getSize().y);
    sf::Vector2f rfSize(door->getSize().x*3/32.0,door->getSize().y);
    lFrame = sf::RectangleShape(lfSize);
    rFrame = sf::RectangleShape(rfSize);
    lFrame.setFillColor(sf::Color::Transparent);
    rFrame.setFillColor(sf::Color::Transparent);


}

void DungeonRunnerSFML::DoorSFML::display() {
    gWindow->draw(*door);
    gWindow->draw(lFrame);
    gWindow->draw(rFrame);
}

void DungeonRunnerSFML::DoorSFML::action() {
    if(isLocked) return;
    //insert chance here
    isOpen = true;
    // if failed
    // isLocked = true;
}
