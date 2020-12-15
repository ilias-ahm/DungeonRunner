//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_ENTITY_H
#define DUNGEONRUNNER_ENTITY_H
#include <iostream>
#include <memory>
#include <vector>
#include "Transformation.h"
namespace DungeonRunner {
    class Entity {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Variables                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        protected:
        std::string eType;
        std::pair<float,float> ePosition;

        public:


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:

        public:
        Entity();

        const std::pair<float, float> &getEPosition() const;

        void setEPosition(const std::pair<float, float> &ePosition);

        std::string getType();
        virtual void display();

        virtual void update();

        virtual void action();

    };

}
#endif //DUNGEONRUNNER_ENTITY_H
