
#include "params.h"

void Params::check_keys() const {
    std::array<std::string, 4> required = {
        "--board",
        "--way",
        "-x",
        "-y",
    };
    for (const auto &key : required) {
        if (data_.find(key) == data_.end()) {
            throw std::logic_error{"missing key required: \"" + key + "\""};
        }
    }
}

Params::Params(int argc, char **argv) {
    for (int i = 1; i < argc - 1; i += 2) {
        data_[argv[i]] = argv[i + 1];
    }
    check_keys();
}

const std::string &Params::at(const std::string &key) {
    return data_.at(key);
}
