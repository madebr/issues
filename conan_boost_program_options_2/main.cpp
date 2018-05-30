#include <boost/program_options.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

int do_boost_program_opts(int argc, char **argv) {
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
    if (vm.count("value")) {
        std::cout << "value is " << vm["value"].as<size_t>() << "\n";
    }
    return 0;
}

int main(int argc, char* argv[], char* envp[])
{
  int res;
  res |= do_boost_program_opts(argc, argv);
  return res;
}
