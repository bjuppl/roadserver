#include "utils.h"
#include <QDateTime>

std::vector<std::string> split( std::string& str, char delim ) {

    std::vector<std::string> ret;

    std::string curChunk = "";

    auto size = str.size();

    for ( auto i = 0; i < size; i++ ) {

        if ( str[i] != delim) {
            curChunk += str.at(i);
        }
        if ( str[i] == delim || i == size-1 ) {

            ret.push_back(curChunk);
            curChunk = "";

        }
    }

    if ( str[str.size()-1] == delim ) {
        ret.push_back("");
    }

    return ret;

}

int random_int(int min, int max) {
    static std::default_random_engine engine { std::random_device{}() };
    std::uniform_int_distribution<int> distro{min, max};
    return distro(engine);
}
