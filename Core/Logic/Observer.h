//
// Created by Ilias Ahmindach on 23/12/2020.
//

#ifndef DUNGEONRUNNER_OBSERVER_H
#define DUNGEONRUNNER_OBSERVER_H
#include <iostream>
namespace DungeonRunner {
    class Observer {
        float hScore = 100;
        std::string observerName;
    public:
        enum Event {
            finishedFirst,
            finishedSecond,
            finishedThird,
            finishedLast,
            hitMovingObstacle,
            staticObstacleAction,
            firstPlace,
            secondPlace,
            thirdPlace,
            lastPlace
        };

        Observer(std::string observerName);

        const std::string &getObserverName() const;

        void update(Event event,float dTime = 1);
        int getObserverData() const;

    };
}


#endif //DUNGEONRUNNER_OBSERVER_H
