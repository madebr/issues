#include <boost/version.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

int do_boost(int argc, char **argv) {
    namespace po = boost::program_options;
    po::options_description desc("conan_boost options");
    desc.add_options()(
        "value,v", po::value<size_t>()->value_name("VALUE"), "Set value");

    boost::program_options::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (po::error &ex) {
        std::cout << "Error parsing arguments: " << ex.what() << std::endl;
    }
    return 0;
}
