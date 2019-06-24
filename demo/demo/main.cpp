#include <iostream>
#include "demo.h"


int main(int argc, char **argv) {

    try {
        Demo demo{argc, argv};
        demo.run();
    }
    catch (std::exception &exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }

    return 0;
}