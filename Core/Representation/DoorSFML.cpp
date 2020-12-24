//
// Created by Ilias Ahmindach on 13/12/2020.
//

#include "DoorSFML.h"
#include "../Logic/Random.h"




void DungeonRunnerSFML::DoorSFML::update() {
    if(isOpen){
        door->setTexture(&*doorStates["door_o"]);
        noClip = true;
    }
    else{
        door->setTexture(&*doorStates["door_c"]);
    }
    std::pair<float,float> pixelC = Transformation::toPixel(gWindow, ePosition.first, ePosition.second);
    door->setPosition(pixelC.first,pixelC.second);
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
    eType = "Door";


}

void DungeonRunnerSFML::DoorSFML::display() {
    gWindow->draw(*door);
}


DungeonRunnerSFML::DoorSFML::~DoorSFML() {

}
