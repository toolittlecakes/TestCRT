
#ifndef DEMO_ROUTER_H
#define DEMO_ROUTER_H

#include "coordinates.h"
#include "way.h"
#include "board.h"

namespace TaskLib {

/**
 * The base class of the route search implementation.
 */
class BaseRouter {

public:

    virtual TaskLib::Coordinates route(const TaskLib::Way &way) const noexcept = 0;

    virtual ~BaseRouter() = default;

};


/**
 * Implementation of the route search class.
 * The maze map and the starting coordinate are internal variables,
 * and the path is supplied as an argument to the method.
 * @tparam Board
 * Implementation class of the maze map.
 * Has a compile-time check on the implementation of the BaseBoard interface
 */
template<typename Board, typename T = std::enable_if_t<std::is_base_of<BaseBoard, Board>::value>>
class Router : public BaseRouter {

    Board board_;

    Coordinates start_;

    void make_step(TaskLib::Direction direction, Coordinates &current) const noexcept;

public:
    /**
     * The constructor for the class, recording board and initial coordinates in the internal variables.
     * The Board will be moved or copied depending on the transfer semantics to the constructor.
     * @param board already created map of the maze.
     * @param start the start coordinate of the route
     */
    Router(Board board, Coordinates start);

    /**
     *
     * @param way the path consisting of steps up, down, right and left, the route by which is calculated.
     * @return coordinate after passing the path.
     */
    TaskLib::Coordinates route(const TaskLib::Way &way) const noexcept override;

    ~Router() override = default;
};


template<typename Board, typename T>
void TaskLib::Router<Board, T>::make_step(TaskLib::Direction direction,
                                          Coordinates &current) const noexcept {

    Coordinates next = current;

    next.move(direction);

    if (board_.has(next)) {
        current = next;
    }
}

template<typename Board, typename T>
TaskLib::Router<Board, T>::Router(Board board, TaskLib::Coordinates start) : board_(std::move(board)), start_(start) {

    if (!board_.has(start)) {
        throw std::logic_error{"invalid start position: no coordinates in the board"};
    }
}

template<typename Board, typename T>
TaskLib::Coordinates TaskLib::Router<Board, T>::route(const TaskLib::Way &way) const noexcept {
    Coordinates current = start_;

    for (auto direction : way) {
        make_step(direction, current);
    }

    return current;
}
}


#endif //DEMO_ROUTER_H
