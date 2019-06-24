#include <fstream>
#include <router.h>
#include <iostream>
#include <coordinates.h>

#include "demo.h"

void Demo::run() {

    std::ifstream board_stream{params_.at("--board")};
    TaskLib::HashBoard board{board_stream};
    TaskLib::Way way{params_.at("--way")};
    TaskLib::Coordinates start{params_.at("-x"), params_.at("-y")};

    TaskLib::Router<TaskLib::HashBoard> router{board, start};
    TaskLib::Coordinates finish = router.route(way);

    std::cout << "coordinates in the end: " <<
              finish.x << ' ' << finish.y << std::endl;

}



