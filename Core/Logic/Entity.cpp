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

const std::pair<float, float> &DungeonRunner::Entity::getESize() const {
    return eSize;
}

void DungeonRunner::Entity::move(float x, float y) {
    ePosition.first+=x;
    ePosition.second+=y;
}

bool DungeonRunner::Entity::isNoClip() const {
    return noClip;
}

DungeonRunner::Entity::Entity(const std::pair<float, float> &ePosition,
                              const std::pair<float, float> &eSize) : ePosition(ePosition),
                                                                      eSize(eSize) {}

void DungeonRunner::Entity::setNoClip(bool noclip) {
    Entity::noClip = noclip;
}

void DungeonRunner::Entity::setESize(const std::pair<float, float> &eSize) {
    Entity::eSize = eSize;
}

void DungeonRunner::Entity::registerObserver(std::shared_ptr<Observer> observer) {
    subjectObservers.push_back(observer);
}

void DungeonRunner::Entity::notifyObservers(DungeonRunner::Observer::Event event,float dTime) {
    for(auto &observer:subjectObservers){
        observer->update(event,dTime);
    }
}



