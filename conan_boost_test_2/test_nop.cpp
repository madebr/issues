#include <boost/test/unit_testmonitor.hpp>

BOOST_AUTO_TEST_SUITE(NopTests)

BOOST_AUTO_TEST_CASE(noptest_1) {
    {
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_CASE(noptest_2) {
    {
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_SUITE_END()
