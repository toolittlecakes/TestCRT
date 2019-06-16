
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <router.h>
#include <types.h>

#include "utils.h"

Params parse_params(int argc, char **argv) {
    Params params{};
    for (int i = 1; i < argc - 1; i += 2) {
        params[argv[i]] = argv[i + 1];
    }
    return params;
}

void check_keys(const Params &params) {
    std::array<std::string, 4> required = {
        "--map",
        "--way",
        "-x",
        "-y",
    };
    for (const auto &key : required) {
        if (params.find(key) == params.end()) {
            throw std::logic_error{"missing key required: \"" + key + "\""};
        }
    }
}


TaskLib::Map create_map(std::istream &input) {
    TaskLib::Map map;
    std::string raw;

    // creating string without (),
    std::string prepared;
    std::getline(input, raw);
    std::copy_if(raw.begin(), raw.end(), std::back_inserter(prepared),
                 [](char ch) -> bool { return ch != '(' && ch != ')' && ch != ','; });


    std::stringstream ss(prepared);

    int x, y;
    while (ss >> x >> y) {
        map.emplace(x, y);
    }
    return map;
}


TaskLib::Way create_way(const std::string &way_str) {
    TaskLib::Way way;
    way.reserve(way_str.size());
    using TaskLib::Direction;
    for (auto ch : way_str) {
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
        way.push_back(direction);
    }
    return way;
}

TaskLib::Coordinates set_start_position(const std::string &x, const std::string &y) {
    TaskLib::Coordinates start_position;
    try {
        start_position.first = std::stoi(x);
        start_position.second = std::stoi(y);
    }
    catch (...) {
        throw std::logic_error{"invalid start position: not a number"};
    }

    return start_position;
}

void run_demo(const Params &params) {

    check_keys(params); // throw exceptions if error

    std::ifstream map_stream(params.at("--map"));
    TaskLib::Map map = create_map(map_stream);
    TaskLib::Way way = create_way(params.at("--way"));
    TaskLib::Coordinates start = set_start_position(params.at("-x"), params.at("-y"));

    TaskLib::Router router{map, start};
    TaskLib::Coordinates finish = router.route(way);

    std::cout << "coordinates in the end: " <<
              finish.first << ' ' << finish.second << std::endl;

}


