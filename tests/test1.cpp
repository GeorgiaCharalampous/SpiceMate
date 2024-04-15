/* An attempt at example unit test adapted from Boost documentation. 
 * See https://www.boost.org/doc/libs/1_84_0/more/getting_started/unix-variants.html
 */

#define BOOST_TEST_MODULE test1
#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace boost::unit_test;
BOOST_AUTO_TEST_CASE(FailTest) {
	BOOST_CHECK_EQUAL(5, 3);
       }
BOOST_AUTO_TEST_CASE(PassTest) {
       BOOST_CHECK_EQUAL(5, 5);
       }

