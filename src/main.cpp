#include <string>


#include <util/util.hpp>

using namespace std;

int main(int argc, char **argv) {
    env::add_to_path(argv[0]);

    std::string filename;

    if(argc >= 2){
        filename = argv[1];
    }

    util::infinity_loop(filename);

    return EXIT_SUCCESS;
}