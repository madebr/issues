#define BOOST_TEST_MODULE conan_boost_test_1
#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/unit_test.hpp>

// entry point:
int main(int argc, char* argv[], char* envp[])
{
  return boost::unit_test::unit_test_main(init_unit_test, argc, argv);
}
