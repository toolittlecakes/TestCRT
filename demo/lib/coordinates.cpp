
#include <stdexcept>
#include "coordinates.h"

namespace TaskLib {

Coordinates::Coordinates(const std::string &x_str, const std::string &y_str) {
    try {
        x = std::stoi(x_str);
        y = std::stoi(y_str);
    }
    catch (...) {
        throw std::logic_error{"invalid start position: not a number"};
    }

}

void Coordinates::move(Direction direction) {
    switch (direction) {
        case Direction::UP:
            y++;
            break;
        case Direction::DOWN:
            y--;
            break;
        case Direction::LEFT:
            x--;
            break;
        case Direction::RIGHT:
            x++;
            break;
    }
}


bool operator==(const Coordinates &lhs, const Coordinates &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

}