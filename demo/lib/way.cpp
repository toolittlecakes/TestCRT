
#include <stdexcept>
#include "way.h"

namespace TaskLib {

Way::Way(const std::string &way_string) {
    data_.reserve(way_string.size());
    for (auto ch : way_string) {
        Direction direction;
        switch (ch) {
            case 'u':
                direction = Direction::UP;
                break;
            case 'd':
                direction = Direction::DOWN;
                break;
            case 'l':
                direction = Direction::LEFT;
                break;
            case 'r':
                direction = Direction::RIGHT;
                break;
            default:
                throw std::logic_error{std::string("invalid char in way: ") + ch};
        }
        data_.push_back(direction);
    }
}

Direction &Way::operator[](size_t idx) {
    return data_[idx];
}

void Way::push_back(Direction direction) {
    data_.push_back(direction);
}

size_t Way::size() const noexcept {
    return data_.size();
}

const Direction &Way::operator[](size_t idx) const {
    return data_[idx];
}

} // Tasklib
