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
        door->setTexture(&*doorStates["door_c"]);
    }
}

DungeonRunnerSFML::DoorSFML::DoorSFML(const std::shared_ptr<sf::RectangleShape> &door,
                                      const std::shared_ptr<sf::RenderWindow> &gWindow,
                                      const std::map<std::string, std::shared_ptr<sf::Texture>> &doorStates) : door(
        door), gWindow(gWindow), doorStates(doorStates) {

}

void DungeonRunnerSFML::DoorSFML::display() {
    gWindow->draw(*door);
}

void DungeonRunnerSFML::DoorSFML::action() {
    if(isLocked) return;
    //insert chance here
    isOpen = true;
    // if failed
    // isLocked = true;
}
