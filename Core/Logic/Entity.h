//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_ENTITY_H
#define DUNGEONRUNNER_ENTITY_H
#include <iostream>
#include <memory>
#include <vector>
#include "Transformation.h"
#include "Random.h"
namespace DungeonRunner {
    class Entity {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Variables                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        protected:
        std::string eType;
        std::pair<float,float> ePosition;
        std::pair<float,float> eSize;
        bool noclip = false;

        public:


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:

        public:
        Entity();

        void setNoclip(bool noclip);

        Entity(const std::pair<float, float> &ePosition,
               const std::pair<float, float> &eSize);

        const std::pair<float, float> &getEPosition() const;

        bool isNoclip() const;

        void setEPosition(const std::pair<float, float> &ePosition);

        const std::pair<float, float> &getESize() const;

        void setESize(const std::pair<float, float> &eSize);

        std::string getType();
        virtual void display();
        void move(float x, float y);
        virtual void update();

        virtual void action();

    };

}
#endif //DUNGEONRUNNER_ENTITY_H
