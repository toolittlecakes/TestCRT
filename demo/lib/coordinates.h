
#ifndef TEST_COORDINATES_H
#define TEST_COORDINATES_H


#include <string>

namespace TaskLib {

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/**
 * Structure representing the coordinate of an object in two-dimensional space
 */
struct Coordinates {
    int x{}, y{};

    Coordinates() = default;

    Coordinates(int x, int y) : x(x), y(y) {}

    Coordinates(const std::string &x_str, const std::string &y_str);

    /**
     * Changes the current coordinate depending on the Direction:
     * <pre>x increases to the right, y increases to the up.
     * @param direction
     */
    void move(Direction direction);

    virtual ~Coordinates() = default;

};

bool operator==(const Coordinates &lhs, const Coordinates &rhs);

}
#endif //TEST_COORDINATES_H
