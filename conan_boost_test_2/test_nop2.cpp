#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Nop2Tests)

BOOST_AUTO_TEST_CASE(nop2test_1) {
    {
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_CASE(nop2test_2) {
    {
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_SUITE_END()
