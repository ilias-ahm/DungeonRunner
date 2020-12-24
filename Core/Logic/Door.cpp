//
// Created by Ilias Ahmindach on 13/12/2020.
//

#include "Door.h"

bool DungeonRunner::Door::IsLocked() const {
    return isLocked;
}

bool DungeonRunner::Door::IsOpen() const {
    return isOpen;
}

void DungeonRunner::Door::action() {
    if(isLocked or isOpen) return;
    if(Random::generateRandomChance()<=1) {
        isOpen = true;
        return;
    }
}
