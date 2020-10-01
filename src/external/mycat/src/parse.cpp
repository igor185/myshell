#include <iostream>
#include <boost/program_options.hpp>

#include "parse/parse.hpp"

namespace po = boost::program_options;

parse::Args parse::parse_ags(int argc, char **argv) {
    po::options_description desc("General options");

    bool A = false;
    std::vector<std::string> file_names;

    desc.add_options()
            ("help,h", "Show help")
            ("spec-sym,A", "Show special symbol");

    po::options_description hidden("Hidden options");
    hidden.add_options()
            ("filename", po::value<std::vector<std::string>>(), "enter filenames");


    po::options_description options;
    options.add(desc).add(hidden);
    po::positional_options_description positional;
    positional.add("filename", -1);
    po::variables_map vm;

    po::store(po::command_line_parser(argc, argv).options(options).positional(positional).run(), vm);
    po::notify(vm);


    if (vm.count("help")) {
        std::cout << desc << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (vm.count("spec-sym")) {
        A = true;
    }

    if (vm.count("filename")) {
        file_names = vm["filename"].as<std::vector<std::string>>();
    }


    return {file_names, A};
}
