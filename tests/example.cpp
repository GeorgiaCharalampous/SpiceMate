/* Working example from Boost documentation using headers configuration.
 * See https://www.boost.org/doc/libs/1_84_0/more/getting_started/unix-variants.html 
 * Run c++ -I path/to/boost_1_82_0 example.cpp -o example 
 * echo 1 2 3 | ./example 
 * */

#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " " );
}

