//
// Created by Ilias Ahmindach on 16/12/2020.
//

#include "Collision.h"

DungeonRunner::Collision::Collision(std::shared_ptr<Entity>& e1) : e1(e1) {}

DungeonRunner::Collision::~Collision() {}

bool DungeonRunner::Collision::checkCollision(std::shared_ptr<Entity>& e2, float push)
{
        std::pair<float, float> e2Pos = e2->getEPosition();
        std::pair<float, float> e1Pos = e1->getEPosition();
        e2Pos.second += e2->getESize().second / 2.0;
        e1Pos.second += e1->getESize().second / 2.0;
        std::pair<float, float> e2HalfSize = e2->getESize();
        std::pair<float, float> e1HalfSize = e1->getESize();
        e2HalfSize.first /= 2.0;
        e2HalfSize.second /= 2.0;
        e1HalfSize.first /= 2.0;
        e1HalfSize.second /= 2.0;

        float dX = e2Pos.first - e1Pos.first;
        float dY = e2Pos.second - e1Pos.second;

        float intersectX = std::abs(dX) - (e2HalfSize.first + e1HalfSize.first);
        float intersectY = std::abs(dY) - (e2HalfSize.second + e1HalfSize.second);

        if (intersectX < 0.0f and intersectY < 0.0f) {
                if (e1->isNoClip() or e2->isNoClip()) {
                        if (e2->getType() == "Player" and e1->getType() == "Sword") {
                                dynamic_cast<DungeonRunner::Player*>(e2.get())->setPlayerSpeed(
                                    dynamic_cast<DungeonRunner::Player*>(e2.get())->getPlayerSpeed() * 0.75);
                                e2->notifyObservers(DungeonRunner::Observer::hitMovingObstacle);
                        }
                        if (e2->getType() == "AI" and e1->getType() == "Sword") {
                                dynamic_cast<DungeonRunner::AIPlayer*>(e2.get())->setAiSpeed(
                                    dynamic_cast<DungeonRunner::AIPlayer*>(e2.get())->getAiSpeed() * 0.5);
                                e2->notifyObservers(DungeonRunner::Observer::hitMovingObstacle);
                        }
                        return true;
                }
                push = std::min(std::max(push, 0.0f), 1.0f);
                if (intersectX > intersectY) {
                        if (dX > 0.0f) {
                                e1->move(intersectX * (1.0f - push), 0);
                                e2->move(-intersectX * (push), 0);
                        } else {
                                e1->move(-intersectX * (1.0f - push), 0);
                                e2->move(intersectX * (push), 0);
                        }
                } else {
                        if (dY > 0.0f) {
                                e1->move(0, intersectY * (1.0f - push));
                                e2->move(0, -intersectY * (push));
                        } else {
                                if (e2->getType() == "Player" and e1->getType() != "AI") {
                                        dynamic_cast<DungeonRunner::Player*>(e2.get())->setPlayerSpeed(0.3);
                                }
                                if (e2->getType() == "AI" and e1->getType() != "Player" and e1->getType() != "AI") {
                                        dynamic_cast<DungeonRunner::AIPlayer*>(e2.get())->setAiSpeed(0.3);
                                }
                                e1->move(0, -intersectY * (1.0f - push));
                                e2->move(0, intersectY * (push));
                        }
                }
                return true;
        }
        return false;
}
