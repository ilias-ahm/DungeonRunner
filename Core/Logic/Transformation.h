//
// Created by Ilias Ahmindach on 12/12/2020.
//

#ifndef DUNGEONRUNNER_TRANSFORMATION_H
#define DUNGEONRUNNER_TRANSFORMATION_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class Transformation
{
private:
        Transformation();
        std::pair<int, int> wSize; // World size (x,y)
        /**
         * Function to convert World coordinates to SFML coordinates
         * @param gWindow SFML Renderwindow
         * @param x x position to convert
         * @param y y position to convert
         * @return tuple (x,y) in SFML coordinates
         */
        std::pair<float, float> _toPixel(std::shared_ptr<sf::RenderWindow> gWindow, float x, float y);
        /**
         * Getter for world size
         * @return
         */
        std::pair<int, int> _getWSize();
        /**
         * Function to convert SFML coordinates to world coordinates
         * @param gWindow SFML Renderwindow
         * @param x x position to convert
         * @param y y position to convert
         * @return tuple (x,y) in World coordinates
         */
        std::pair<float, float> _toCoords(std::shared_ptr<sf::RenderWindow> gWindow, float x, float y);

public:
        /**
         * Function to convert SFML coordinates to world coordinates
         * @param gWindow SFML Renderwindow
         * @param x x position to convert
         * @param y y position to convert
         * @return tuple (x,y) in World coordinates
         */
        static std::pair<float, float> toCoords(std::shared_ptr<sf::RenderWindow> gWindow, float x, float y);
        /**
         * Function to convert World coordinates to SFML coordinates
         * @param gWindow SFML Renderwindow
         * @param x x position to convert
         * @param y y position to convert
         * @return tuple (x,y) in SFML coordinates
         */
        static std::pair<float, float> toPixel(std::shared_ptr<sf::RenderWindow> gWindow, float x, float y);
        /**
         * gets instance
         * @return
         */
        static Transformation& getInstance();
        /**
         * Getter for world size
         * @return
         */
        static std::pair<int, int> getWSize();
};

#endif // DUNGEONRUNNER_TRANSFORMATION_H
