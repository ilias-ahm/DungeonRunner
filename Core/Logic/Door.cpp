//
// Created by Ilias Ahmindach on 13/12/2020.
//

#include "Door.h"

void DungeonRunner::Door::open() {
    isOpen = true;


}

void DungeonRunner::Door::close() {
    isOpen = false;
}

void DungeonRunner::Door::lockDoor() {
    isLocked = true;
}
