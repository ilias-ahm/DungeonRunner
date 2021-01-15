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
#include "Subject.h"
namespace DungeonRunner {
    class Entity: public DungeonRunner::Subject {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Variables                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        protected:
        std::string eType; // Entity type
        std::pair<float,float> ePosition; //
        std::pair<float,float> eSize; // x and y value - Entity size
        bool noClip = false; // true: collision control off for this entity

        public:


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:

        public:
        /**
         * Default constructor
         */
        Entity();
        /**
         * setter for variable noClip
         * @param noclip
         */
        void setNoClip(bool noclip);
        /**
         * Constructor to set position and size
         * @param ePosition
         * @param eSize
         */
        Entity(const std::pair<float, float> &ePosition,
               const std::pair<float, float> &eSize);
        /**
         * Getter for position
         * @return returns float tuple(x,y) coordinate
         */
        const std::pair<float, float> &getEPosition() const;
        /**
         * getter for noClip variable
         * @return noclip
         */
        bool isNoClip() const;
        /**
         * Setter for entity position
         * @param ePosition float tuple(x,y)
         */
        void setEPosition(const std::pair<float, float> &ePosition);
        /**
         * Getter for entity size
         * @return float tuple(x,y)
         */
        const std::pair<float, float> &getESize() const;
        /**
         * Setter for entity size
         * @param eSize float tuple(x,y)
         */
        void setESize(const std::pair<float, float> &eSize);
        /**
         * Getter for entity type
         * @return entity type
         */
        std::string getType();
        /**
         * Displays SFML on the renderwindow
         */
        virtual void display();
        /**
         * Moves entity according to game coordinates
         * @param x float
         * @param y float
         */
        void move(float x, float y);
        /**
         * Virtual function that updates Entity
         */
        virtual void update();
        /**
         * Virtual function for an entity Action
         */
        virtual void action();
        /**
         * Creates a new observer in observerlist
         * @param observer
         */
        void registerObserver(std::shared_ptr<Observer> observer) override;
        /**
         * Notifies observer with new game event (game events can be found in Observer)
         * @param event Observer::Event
         * @param dTime delta time to ensure that scores are the same on all fps settings
         */
        void notifyObservers(Observer::Event event, float dTime=1) override;
    };

}
#endif //DUNGEONRUNNER_ENTITY_H
