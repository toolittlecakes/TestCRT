
#include "router.h"

void TaskLib::Router::make_step(TaskLib::Direction direction, Coordinates &current) const noexcept {

    Coordinates next = current;

    switch (direction) {
        case Direction::UP:
            next.second++;
            break;
        case Direction::DOWN:
            next.second--;
            break;
        case Direction::LEFT:
            next.first--;
            break;
        case Direction::RIGHT:
            next.first++;
            break;
    }

    if (map_.find(next) != map_.end()) {
        current = next;
    }
}

TaskLib::Coordinates TaskLib::Router::route(const TaskLib::Way &way) const noexcept {
    Coordinates current = start_;
    for (auto direction : way) {
        make_step(direction, current);
    }
    return current;
}

TaskLib::Router::Router(TaskLib::Map map, TaskLib::Coordinates start)
    : map_(std::move(map)), start_(std::move(start)) {

    if (map_.find(start_) == map_.end()) {
        throw std::logic_error{"invalid start position: no coordinates in the map"};
    }
}


