
#ifndef DEMO_PARAMS_H
#define DEMO_PARAMS_H

#include <string>
#include <unordered_map>

class Params final {
    std::unordered_map<std::string, std::string> data_;
    void check_keys() const;

public:
    Params(int argc, char **argv);
    const std::string& at(const std::string& key);
};

#endif //DEMO_PARAMS_H
