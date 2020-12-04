//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_ABSTRACTFACTORY_H
#define DUNGEONRUNNER_ABSTRACTFACTORY_H
#include "Entity.h"

namespace DungeonRunner {
    class AbstractFactory {
    public:
        std::shared_ptr<Entity> createEntity();
    };
}

#endif //DUNGEONRUNNER_ABSTRACTFACTORY_H
