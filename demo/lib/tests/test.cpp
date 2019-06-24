#include <catch.hpp>
#include <router.h>
#include <sstream>


using TaskLib::Coordinates;
using TaskLib::HashBoard;
using TaskLib::Direction;
using TaskLib::Way;
using TaskLib::Router;


TEST_CASE("coordinates constructor", "[Coordinates]") {
    SECTION("default") {
        Coordinates coordinates{};
        REQUIRE(coordinates.x == 0);
        REQUIRE(coordinates.y == 0);
    }

    SECTION("simple") {
        Coordinates coordinates{1,-1};
        REQUIRE(coordinates.x == 1);
        REQUIRE(coordinates.y == -1);
    }
    SECTION("from string") {
        Coordinates coordinates{"1","-1"};
        REQUIRE(coordinates == Coordinates{1,-1});
    }

    SECTION("from invalid string") {
        REQUIRE_THROWS(Coordinates {"w","-1"});
    }
}

TEST_CASE("way constructor", "[Way]") {
    SECTION("default") {
        Way way{};
        REQUIRE(way.size() == 0);
    }

    SECTION("from vector") {
        Way way{
            {
                Direction::RIGHT,
                Direction::LEFT,
                Direction::UP,
                Direction::DOWN,
            }
        };
        REQUIRE(way.size() == 4);
    }

    SECTION("from initializer list") {
        Way way{
            Direction::RIGHT,
            Direction::LEFT,
            Direction::UP,
            Direction::DOWN,
        };
        REQUIRE(way.size() == 4);
    }

    SECTION("from string") {
        Way way{"rlud"};
        REQUIRE(way.size() == 4);
    }

    SECTION("from invalid string") {
        REQUIRE_THROWS(Way{"w"});
    }
}


TEST_CASE("hashboard constructor", "[HashBoard]") {
    SECTION("default") {
        REQUIRE_NOTHROW(HashBoard{});
    }

    SECTION("from initializer list") {
        REQUIRE_NOTHROW(HashBoard{{0, 0}});
    }

    SECTION("from stream") {
        std::stringstream ss{"(0, 0), (1, 1)"};
        HashBoard board{ss};
        REQUIRE(board.has({0, 0}));
        REQUIRE(board.has({1, 1}));
        REQUIRE(!board.has({0, 1}));
    }
}

TEST_CASE("hashboard methods", "[HashBoard]") {
    SECTION("has") {
        HashBoard empty{};
        REQUIRE(!empty.has({0, 0}));
        HashBoard board{{0,  0},
                        {-1, -1},
                        {1,  1}};
        REQUIRE(board.has({0, 0}));
        REQUIRE(board.has({-1, -1}));
        REQUIRE(board.has({1, 1}));
    }
    SECTION("add_coordinates") {
        HashBoard board{};
        board.add_coordinates({-1,-1});
        REQUIRE(board.has({-1, -1}));
    }
}


TEST_CASE("Router constructor", "[Router]") {
    SECTION("successfully") {
        HashBoard board{
            {0, 0},
        };
        Coordinates coordinates{0, 0};


        REQUIRE_NOTHROW(Router<HashBoard>{board, coordinates});
    }
    SECTION("invalid coordinates") {
        TaskLib::HashBoard board{};
        TaskLib::Coordinates coordinates{0, 0};
        try {
            TaskLib::Router<HashBoard> router{board, coordinates};
        }
        catch (std::exception &exception) {
            REQUIRE(std::string{exception.what()} == "invalid start position: no coordinates in the board");
        }
    }
}

TEST_CASE("route()", "[Router]") {
    SECTION("one position") {
        TaskLib::HashBoard board{
            {0, 0},
        };
        TaskLib::Coordinates coordinates{0, 0};
        TaskLib::Router<HashBoard> router{board, coordinates};

        TaskLib::Way way{{TaskLib::Direction::RIGHT,}};
        REQUIRE(router.route(way) == TaskLib::Coordinates{0, 0});
    }

    SECTION("simple step") {
        TaskLib::HashBoard board{
            {0, 0},
            {1, 0},
        };
        TaskLib::Coordinates coordinates{0, 0};
        TaskLib::Router<HashBoard> router{board, coordinates};

        TaskLib::Way way{{TaskLib::Direction::RIGHT,}};
        REQUIRE(router.route(way) == TaskLib::Coordinates{1, 0});
    }

    SECTION("there and back") {
        TaskLib::HashBoard board{
            {0, 0},
            {1, 0},
        };
        TaskLib::Coordinates coordinates{0, 0};
        TaskLib::Router<HashBoard> router{board, coordinates};

        TaskLib::Way way{{
                             TaskLib::Direction::RIGHT,
                             TaskLib::Direction::LEFT,
                         }};
        REQUIRE(router.route(way) == TaskLib::Coordinates{0, 0});
    }

    SECTION("roundtrip") {
        TaskLib::HashBoard board{
            {0, 0},
            {1, 0},
            {1, 1},
            {0, 1},
        };
        TaskLib::Coordinates coordinates{0, 0};
        TaskLib::Router<HashBoard> router{board, coordinates};

        TaskLib::Way way{{
                             TaskLib::Direction::RIGHT,
                             TaskLib::Direction::UP,
                             TaskLib::Direction::LEFT,
                             TaskLib::Direction::DOWN,
                         }};
        REQUIRE(router.route(way) == TaskLib::Coordinates{0, 0});
    }

    SECTION("long way") {
        TaskLib::HashBoard board{{0, 0}};
        TaskLib::Way way{};
        int lenght = 1000000;
        for (int i = 0; i < lenght; i++) {
            board.add_coordinates({i + 1, 0});
            way.push_back(TaskLib::Direction::RIGHT);
        }
        TaskLib::Coordinates coordinates{0, 0};
        TaskLib::Router<HashBoard> router{board, coordinates};

        REQUIRE(router.route(way) == TaskLib::Coordinates{lenght, 0});
    }
}


