//
// Created by Ilias Ahmindach on 23/12/2020.
//

#ifndef DUNGEONRUNNER_SUBJECT_H
#define DUNGEONRUNNER_SUBJECT_H
#include "Observer.h"
#include <iostream>
#include <memory>
#include <vector>

namespace DungeonRunner {
    class Subject {
    protected:
        std::vector<std::shared_ptr<Observer>> subjectObservers;
    public:
        /**
         * pure virtual function to add new observers
         * @param observer
         */
        virtual void registerObserver(std::shared_ptr<Observer> observer) = 0;
        /**
         * pure virtual function to notify new observers
         * @param event
         * @param dTime
         */

        virtual void notifyObservers(Observer::Event event,float dTime =1) = 0;

        const std::vector<std::shared_ptr<Observer>> &getSubjectObservers() const;
    };
}


#endif //DUNGEONRUNNER_SUBJECT_H
