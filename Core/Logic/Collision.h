//
// Created by Ilias Ahmindach on 16/12/2020.
//

#ifndef DUNGEONRUNNER_COLLISION_H
#define DUNGEONRUNNER_COLLISION_H
#include "Entity.h"
#include "Player.h"
#include "AIPlayer.h"
namespace DungeonRunner {
    class Collision {
    public:
        explicit Collision(std::shared_ptr<Entity> &e1);
        void Move(float deltaX,float deltaY);
        bool checkCollision(std::shared_ptr<Entity> &e2, float push);
        ~Collision();

    private:
        std::shared_ptr<Entity> e1;
    };
}

#endif //DUNGEONRUNNER_COLLISION_H
