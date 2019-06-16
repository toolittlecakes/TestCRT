
#ifndef DEMO_TYPES_H
#define DEMO_TYPES_H

#include <unordered_set>
#include <utility>
#include <vector>

namespace TaskLib {

    using Coordinates = std::pair<int, int>;


    struct Hash {
        size_t operator()(const Coordinates &coordinates) const {
            std::hash<int> hash;
            return hash(coordinates.first) ^ hash(coordinates.second);
        }
    };

    using Map = std::unordered_set<Coordinates, Hash>;


    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    using Way = std::vector<Direction>;

}

#endif //DEMO_TYPES_H
