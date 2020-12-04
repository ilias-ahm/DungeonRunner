//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "AbstractFactory.h"

std::shared_ptr<DungeonRunner::Entity> DungeonRunner::AbstractFactory::createEntity() {
    return std::shared_ptr<Entity>();
}
