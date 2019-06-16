#include <catch.hpp>
#include <router.h>


TEST_CASE("Router constructor", "[Router]") {
    SECTION("successfully") {
        TaskLib::Map map{
            {0, 0},
        };
        TaskLib::Coordinates coordinates{0, 0};


        REQUIRE_NOTHROW(TaskLib::Router{map, coordinates});
    }
    SECTION("invalid coordinates") {
        TaskLib::Map map{};
        TaskLib::Coordinates coordinates{0, 0};
        try {
            TaskLib::Router router{map, coordinates};
        }
        catch (std::exception &exception) {
            REQUIRE(std::string{exception.what()} == "invalid start position: no coordinates in the map");
        }
    }
}

TEST_CASE("route()", "[Router]") {
    SECTION("one position") {
        TaskLib::Map map{
            {0, 0},
        };
        TaskLib::Coordinates coordinates{0, 0};
        TaskLib::Router router{map, coordinates};

        TaskLib::Way way{TaskLib::Direction::RIGHT,};
        REQUIRE(router.route(way) == TaskLib::Coordinates{0, 0});
    }

    SECTION("simple step") {
        TaskLib::Map map{
            {0, 0},
            {1, 0},
        };
        TaskLib::Coordinates coordinates{0, 0};
        TaskLib::Router router{map, coordinates};

        TaskLib::Way way{TaskLib::Direction::RIGHT,};
        REQUIRE(router.route(way) == TaskLib::Coordinates{1, 0});
    }

    SECTION("there and back") {
        TaskLib::Map map{
            {0, 0},
            {1, 0},
        };
        TaskLib::Coordinates coordinates{0, 0};
        TaskLib::Router router{map, coordinates};

        TaskLib::Way way{
            TaskLib::Direction::RIGHT,
            TaskLib::Direction::LEFT,
        };
        REQUIRE(router.route(way) == TaskLib::Coordinates{0, 0});
    }

    SECTION("roundtrip") {
        TaskLib::Map map{
            {0, 0},
            {1, 0},
            {1, 1},
            {0, 1},
        };
        TaskLib::Coordinates coordinates{0, 0};
        TaskLib::Router router{map, coordinates};

        TaskLib::Way way{
            TaskLib::Direction::RIGHT,
            TaskLib::Direction::UP,
            TaskLib::Direction::LEFT,
            TaskLib::Direction::DOWN,
        };
        REQUIRE(router.route(way) == TaskLib::Coordinates{0, 0});
    }

    SECTION("long way") {
        TaskLib::Map map{{0,0}};
        TaskLib::Way way{};
        int lenght = 1000000;
        for(int i = 0; i < lenght; i++) {
            map.emplace(i + 1, 0);
            way.emplace_back(TaskLib::Direction::RIGHT);
        }
        TaskLib::Coordinates coordinates{0, 0};
        TaskLib::Router router{map, coordinates};

        REQUIRE(router.route(way) == TaskLib::Coordinates{lenght, 0});
    }
}


