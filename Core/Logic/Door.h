//
// Created by Ilias Ahmindach on 13/12/2020.
//

#ifndef DUNGEONRUNNER_DOOR_H
#define DUNGEONRUNNER_DOOR_H
#include "Entity.h"
#include <memory>
namespace DungeonRunner {
    class Door: public Entity{
    protected:
        bool isOpen = false;
        bool isLocked = false;

    public:
    };

}
#endif //DUNGEONRUNNER_DOOR_H
