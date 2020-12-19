//
// Created by Ilias Ahmindach on 18/12/2020.
//

#ifndef DUNGEONRUNNER_AIPLAYER_H
#define DUNGEONRUNNER_AIPLAYER_H
#include "Entity.h"
namespace DungeonRunner {
    class AIPlayer: public Entity {
    protected:
        float aiSpeed;
    public:
        float getAiSpeed() const;

        void setAiSpeed(float aiSpeed);
    };
}


#endif //DUNGEONRUNNER_AIPLAYER_H
