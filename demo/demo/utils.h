
#ifndef DEMO_UTILS_H
#define DEMO_UTILS_H

#include <unordered_map>
#include <types.h>


using Params = std::unordered_map<std::string, std::string>;

Params parse_params(int argc, char **argv);

void check_keys(const Params &params);

TaskLib::Map create_map(std::istream &input);

TaskLib::Way create_way(const std::string &raw);

TaskLib::Coordinates set_start_position(const std::string &x, const std::string &y);

void run_demo(const Params &params);

#endif //DEMO_UTILS_H
