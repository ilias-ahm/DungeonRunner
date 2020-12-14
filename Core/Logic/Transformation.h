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
     std::shared_ptr<sf::RenderWindow> gWindow;
     std::pair<int,int> wSize;
public:
    std::pair<float,float> toCoords(float x, float y);
    std::pair<float,float> toPixel(float x, float y);

    const std::pair<int, int> &getWSize() const;

    Transformation(const std::shared_ptr<sf::RenderWindow> &gWindow, const std::pair<int, int> &wSize);
};


#endif //DUNGEONRUNNER_TRANSFORMATION_H
