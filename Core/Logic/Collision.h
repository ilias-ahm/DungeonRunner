//
// Created by Ilias Ahmindach on 16/12/2020.
//

#ifndef DUNGEONRUNNER_COLLISION_H
#define DUNGEONRUNNER_COLLISION_H
#include "AIPlayer.h"
#include "Entity.h"
#include "Player.h"
namespace DungeonRunner {
class Collision
{
public:
        /**
         * Constructor
         * @param e1 -- first entity for collision
         */
        explicit Collision(std::shared_ptr<Entity>& e1);
        /**
         *
         * @param e2 -- second entity for collision
         * @param push -- float between 0-1. higher means entity gets pushed easier
         * @return true if entity1 and entity2 are colliding
         */
        bool checkCollision(std::shared_ptr<Entity>& e2, float push);
        ~Collision();

private:
        std::shared_ptr<Entity> e1;
};
} // namespace DungeonRunner

#endif // DUNGEONRUNNER_COLLISION_H
