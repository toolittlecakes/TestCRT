#include <catch.hpp>
#include <utils.h>
#include <sstream>
TEST_CASE("check_keys", "[utils]") {
    SECTION("good") {
        Params params {
            {"--map", ""},
            {"--way", ""},
            {"-x", ""},
            {"-y", ""},
        };
        REQUIRE_NOTHROW(check_keys(params));
    }

    SECTION("bad: lack of key") {
        Params without_x {
            {"--map", ""},
            {"--way", ""},
            {"-y", ""},
        };
        Params without_y {
            {"--map", ""},
            {"--way", ""},
            {"-x", ""},
        };
        Params without_map {
            {"--way", ""},
            {"-x", ""},
            {"-y", ""},
        };
        Params without_way {
            {"--way", ""},
            {"-x", ""},
            {"-y", ""},
        };
        REQUIRE_THROWS(check_keys(without_x));
        REQUIRE_THROWS(check_keys(without_y));
        REQUIRE_THROWS(check_keys(without_map));
        REQUIRE_THROWS(check_keys(without_way));
    }
}

TEST_CASE("create_map", "[utils]") {
    SECTION("simple") {
        std::stringstream input {"(1, 1), (2, 2)"};
        REQUIRE(create_map(input) == TaskLib::Map {{1, 1}, {2, 2}});
    }
    SECTION("empty") {
        std::stringstream input {""};
        auto map = create_map(input);
        REQUIRE(create_map(input).empty());
    }
}

TEST_CASE("create_way", "[utils]") {
    SECTION("simple") {
        std::string input {"ruld"};
        using TaskLib::Direction;
        REQUIRE(create_way(input) == TaskLib::Way {
            Direction::RIGHT,
            Direction::UP,
            Direction::LEFT,
            Direction::DOWN,
        });
    }
    SECTION("invalid chars") {
        std::string input {"0"};
        using TaskLib::Direction;
        REQUIRE_THROWS(create_way(input));
    }
}


TEST_CASE("set_start_positions", "[utils]") {
    SECTION("simple") {
        std::string x {"0"};
        std::string y {"0"};
        REQUIRE(set_start_position(x, y) == TaskLib::Coordinates {0, 0});
    }
    SECTION("invalid coordinates") {
        std::string x {"0"};
        std::string y {"w"};
        REQUIRE_THROWS(set_start_position(x, y));
    }
}