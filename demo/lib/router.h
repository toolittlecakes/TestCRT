
#ifndef DEMO_ROUTER_H
#define DEMO_ROUTER_H


#include "types.h"

namespace TaskLib {

    class Router {

        Map map_;

        Coordinates start_;

        void make_step(TaskLib::Direction direction, Coordinates &current) const noexcept;

    public:

        Router(Map map, Coordinates start);

        TaskLib::Coordinates route(const TaskLib::Way &way) const noexcept;

        virtual ~Router() = default;
    };
}


#endif //DEMO_ROUTER_H
