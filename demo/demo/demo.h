
#ifndef DEMO_DEMO_H
#define DEMO_DEMO_H

#include <coordinates.h>
#include "params.h"

class Demo final {
    Params params_;

public:
    Demo(int argc, char **argv) : params_(argc, argv) {};

    void run();

};

#endif //DEMO_DEMO_H
