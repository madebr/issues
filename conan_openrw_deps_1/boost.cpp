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
    std::cout << "boost version " << BOOST_LIB_VERSION << "\n";
    const std::string s1 = "random text";
    std::string s2;
    s2.reserve(s1.size()+1);
    std::transform(s1.cbegin(), s1.cend(), std::back_inserter(s2), [](unsigned char c) -> unsigned char {return ::toupper(c);});
    std::cout << "iequals: ";
    if (!boost::algorithm::iequals(s1, s2)) {
        return 1;
    }
    std::cout << "success!\n";

    auto path = boost::filesystem::initial_path();
    std::cout << "initial path = " << path << "\n";
    auto parent_path = path.parent_path();
    std::cout << "parent = " << parent_path << "\n";

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

    namespace pt = boost::property_tree;
    pt::ptree tree;
    const std::string ini_string =
R"(
[head1]
key1=value1
key2=value2
[head2]
key3=value3
key4=value4
)";
    std::istringstream iss(ini_string);
    pt::read_ini(iss, tree);

    if (tree.get<std::string>("head1.key1").compare("value1")) {
        return 1;
    }
    if (tree.get<std::string>("head1.key2").compare("value2")) {
        return 1;
    }
    if (tree.get<std::string>("head2.key3").compare("value3")) {
        return 1;
    }
    if (tree.get<std::string>("head2.key4").compare("value4")) {
        return 1;
    }
    return 0;
}
