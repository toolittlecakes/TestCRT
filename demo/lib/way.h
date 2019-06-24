
#ifndef TEST_WAY_H
#define TEST_WAY_H

#include <vector>
#include <string>
#include "coordinates.h"

namespace TaskLib {


/**
 * class implementing path - a series of directions
 */
class Way final {
    std::vector<Direction> data_;
public:
    Way() = default;

    Way(std::initializer_list<Direction> init) : data_(init) {}

    explicit Way(std::vector<Direction> data) : data_(std::move(data)) {}

    explicit Way(const std::string &way_string);

    Direction &operator[](size_t idx);

    const Direction &operator[](size_t idx) const;

    void push_back(Direction direction);

    size_t size() const noexcept;

    auto begin() const { return data_.begin(); }

    auto cbegin() const { return data_.cbegin(); }

    auto end() const { return data_.end(); }

    auto cend() const { return data_.cend(); }
};
}

#endif //TEST_WAY_H
