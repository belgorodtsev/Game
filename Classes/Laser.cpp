#include "Laser.h"

Laser::Laser(Point pos, const std::string & filenamePicture)
    : GameObject(pos, filenamePicture)
{}

std::string Laser::getNumberLaser()
{
    size_t number_laser;
    std::string tmp = ".png";
    std::string str;
    number_laser = 1 + rand() % 6;
    str = std::to_string(number_laser);
    str += tmp;
    return str;
}


