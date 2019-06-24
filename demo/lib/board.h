#ifndef TEST_BIARD_H
#define TEST_BIARD_H


#include <unordered_set>
#include "coordinates.h"

namespace TaskLib {

/**
 * Maze map interface
 */
class BaseBoard {
public:
    virtual bool has(Coordinates coordinates) const noexcept = 0;

    virtual void add_coordinates(Coordinates coordinates) noexcept = 0;

    virtual ~BaseBoard() = default;
};

/**
 * An implementation of a maze map that uses unordered_set as a container.
 * The container stores the coordinates of the cells, on which you can move in the maze
 */
class HashBoard : public BaseBoard {
protected:
    struct Hash {
        std::size_t operator()(const Coordinates &coordinates) const {
            std::hash<int> hash;
            return hash(coordinates.x) ^ (hash(coordinates.y) << 1);
        }
    };

    std::unordered_set<Coordinates, Hash> data_;
public:
    HashBoard() = default;

    HashBoard(std::initializer_list<Coordinates> init) : data_(init) {}

    HashBoard(HashBoard &&board) noexcept : data_(std::move(board.data_)) {}

    HashBoard(const HashBoard &board) : data_(board.data_) {};

    /**
     * A method that deserializes a maze from a stream
     *
     * @param input  in which coordinates are written in the format
     * <pre> (1, 1), (0, 0), (-1, -1)
     */
    explicit HashBoard(std::istream &input);

    /**
     * Method that checks for a coordinate in the maze.
     *
     * @param coordinates that are searched on the board
     * @return true if the coordinate exists in the maze, otherwise false
     */
    bool has(Coordinates coordinates) const noexcept override;

    /**
     * Adds a coordinate to the maze
     * @param coordinates
     */
    void add_coordinates(Coordinates coordinates) noexcept override;

    ~HashBoard() override = default;
};

}

#endif //TEST_BIARD_H
