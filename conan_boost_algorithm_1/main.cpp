#include <boost/algorithm/string/predicate.hpp>

#include <iostream>
#include <string>

int main() {
    const std::string s1 = "random text";
    std::string s2;
    s2.reserve(s1.size()+1);
    std::transform(s1.begin(), s1.end(), std::back_inserter(s2), [](unsigned char c) -> unsigned char {return ::toupper(c);});
    std::cout << "iequals: ";
    if (!boost::algorithm::iequals(s1, s2)) {
        return 1;
    }
    return 0;
}
