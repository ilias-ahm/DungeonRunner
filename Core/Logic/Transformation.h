//
// Created by Ilias Ahmindach on 12/12/2020.
//

#ifndef DUNGEONRUNNER_TRANSFORMATION_H
#define DUNGEONRUNNER_TRANSFORMATION_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

class Transformation {
private:
    Transformation();
    std::pair<int,int> wSize;
    std::pair<float,float> _toPixel(std::shared_ptr<sf::RenderWindow> gWindow,float x, float y);
    std::pair<int,int> _getWSize();
    std::pair<float,float> _toCoords(std::shared_ptr<sf::RenderWindow>gWindow,float x, float y);
public:
    static std::pair<float,float> toCoords(std::shared_ptr<sf::RenderWindow>gWindow,float x, float y);
    static std::pair<float,float> toPixel(std::shared_ptr<sf::RenderWindow> gWindow,float x, float y);
    static Transformation& getInstance();
    static std::pair<int, int> getWSize();


};


#endif //DUNGEONRUNNER_TRANSFORMATION_H
