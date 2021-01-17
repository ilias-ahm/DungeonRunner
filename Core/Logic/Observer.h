//
// Created by Ilias Ahmindach on 23/12/2020.
//

#ifndef DUNGEONRUNNER_OBSERVER_H
#define DUNGEONRUNNER_OBSERVER_H
#include <iostream>
namespace DungeonRunner {
class Observer
{
        float hScore = 100;
        std::string observerName;

public:
        enum Event
        {
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

        /**
         * Constructor for observer
         * @param observerName Player name or AI name
         */
        Observer(std::string observerName);
        /**
         * Getter for observer name aka player/ai name
         * @return
         */
        const std::string& getObserverName() const;
        /**
         * Updates score of observer according to observer event
         * @param event
         * @param dTime
         */
        void update(Event event, float dTime = 1);
        /**
         *
         * @return observer score (hScore variable)
         */
        int getObserverData() const;
};
} // namespace DungeonRunner

#endif // DUNGEONRUNNER_OBSERVER_H
