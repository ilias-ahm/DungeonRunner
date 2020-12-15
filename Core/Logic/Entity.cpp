//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "Entity.h"


std::string DungeonRunner::Entity::getType() {
    return eType;
}

DungeonRunner::Entity::Entity() {
    eType = "Entity";
}

void DungeonRunner::Entity::setEPosition(const std::pair<float, float> &ePosition) {
    Entity::ePosition = ePosition;
}

const std::pair<float, float> &DungeonRunner::Entity::getEPosition() const {
    return ePosition;
}

void DungeonRunner::Entity::display() {

}

void DungeonRunner::Entity::update() {

}

void DungeonRunner::Entity::action() {

}



