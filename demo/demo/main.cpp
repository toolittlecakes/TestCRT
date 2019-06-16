#include <iostream>
#include "utils.h"



int main(int argc, char **argv) {

    try {
        run_demo(parse_params(argc, argv));
    }
    catch (std::exception &exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }

    return 0;
}