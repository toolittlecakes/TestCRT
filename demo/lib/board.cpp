
#include <algorithm>
#include <string>
#include <sstream>
#include "board.h"

namespace TaskLib {

bool HashBoard::has(Coordinates coordinates) const noexcept {
    return data_.find(coordinates) != data_.end();
}

void HashBoard::add_coordinates(Coordinates coordinates) noexcept {
    data_.emplace(std::move(coordinates));
}

HashBoard::HashBoard(std::istream &input) {
    std::string raw;

    // creating string without '(' ')' ','
    std::string prepared;
    std::getline(input, raw);
    std::copy_if(raw.begin(), raw.end(), std::back_inserter(prepared),
                 [](char ch) -> bool { return ch != '(' && ch != ')' && ch != ','; });


    std::stringstream ss(prepared);

    int x, y;
    while (ss >> x >> y) {
        add_coordinates({x, y});
    }
}

}
