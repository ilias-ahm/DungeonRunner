//
// Created by Ilias Ahmindach on 23/12/2020.
//

#include "Observer.h"
#include <cmath>
#include <utility>

void DungeonRunner::Observer::update(DungeonRunner::Observer::Event event, float dTime)
{
        switch (event) {
        case Observer::finishedFirst:
                hScore += 100;
                break;
        case Observer::finishedSecond:
                hScore += 75;
                break;
        case Observer::finishedThird:
                hScore += 50;
                break;
        case Observer::finishedLast:
                hScore += 0;
                break;
        case Observer::hitMovingObstacle:
                hScore -= 20;
                break;
        case Observer::staticObstacleAction:
                hScore -= 50;
                break;
        case Observer::firstPlace:
                hScore += 8 * dTime;
                break;
        case Observer::secondPlace:
                hScore += 7 * dTime;
                break;
        case Observer::thirdPlace:
                hScore += 6 * dTime;
                break;
        case Observer::lastPlace:
                hScore += 5 * dTime;
                break;
        }
}

int DungeonRunner::Observer::getObserverData() const { return std::round(hScore); }

DungeonRunner::Observer::Observer(std::string observerName) : observerName(std::move(observerName)) {}

const std::string& DungeonRunner::Observer::getObserverName() const { return observerName; }
