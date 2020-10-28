#include <string>

#include <util/util.h>
#include <IO/IO.h>



int main(int argc, char **argv) {
    env::add_to_path(argv[0]);

    std::string filename;

    bool server = false;
    int port = -1;

    for(int i = 1; i < argc; i++){
        std::string temp = argv[i];
        if(temp == "--server"){
            server = true;
        }else if(temp == "--port"){
            if(i+1 == argc || !util::is_integer(argv[i+1])){
                IO::err("Please, provide port number");
                IO::help();
                exit(EXIT_FAILURE);
            }
            port = util::to_number(argv[i+1]);
            i++;
        }else if(temp == "--help" || temp == "-h"){
            IO::help();
            exit(EXIT_SUCCESS);
        }else{
            filename = temp;
        }
    }

    if(!server)
        util::infinity_loop(filename);
    else{
        server::init(port);
    }

    exit(EXIT_SUCCESS);
}