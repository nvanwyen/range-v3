// Range v3 library
//
//  Copyright Eric Niebler 2013-2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Acknowledgements: Thanks for Paul Fultz for the suggestions that
//                   concepts can be ordinary Boolean metafunctions.
//
// Project home: https://github.com/ericniebler/range-v3
//

#include <tuple>
#include <memory>
#include <range/v3/utility/swap.hpp>
#include <range/v3/utility/concepts.hpp>
#include <range/v3/utility/iterator.hpp> // for iter_swap, which uses indirect_swap
#include "../simple_test.hpp"
#include "../test_utils.hpp"

int main()
{
    int a=0,b=42;
    ranges::swap(a,b);
    CHECK(a == 42);
    CHECK(b == 0);

    CONCEPT_ASSERT(!ranges::Swappable<std::pair<int,int>&&,std::pair<int,int>&&>());
    CONCEPT_ASSERT(ranges::Swappable<std::pair<int&,int&>&&,std::pair<int&,int&>&&>());

    int c=24,d=82;
    ranges::swap(std::tie(a,b),std::tie(c,d));
    CHECK(a == 24);
    CHECK(b == 82);
    CHECK(c == 42);
    CHECK(d == 0);

    // Swap pairs of tuple proxies
    int e=1,f=2,g=3,h=4;
    ranges::swap(std::make_pair(std::tie(a,b), std::tie(c,d)), std::make_pair(std::tie(e,f), std::tie(g,h)));
    CHECK(a == 1);
    CHECK(b == 2);
    CHECK(c == 3);
    CHECK(d == 4);
    CHECK(e == 24);
    CHECK(f == 82);
    CHECK(g == 42);
    CHECK(h == 0);

#ifndef _LIBCPP_VERSION
    // Swap tuples of pair proxies
    ranges::swap(std::make_tuple(std::make_pair(std::ref(a),std::ref(b)), std::make_pair(std::ref(c),std::ref(d))),
                 std::make_tuple(std::make_pair(std::ref(e),std::ref(f)), std::make_pair(std::ref(g),std::ref(h))));
    CHECK(a == 24);
    CHECK(b == 82);
    CHECK(c == 42);
    CHECK(d == 0);
    CHECK(e == 1);
    CHECK(f == 2);
    CHECK(g == 3);
    CHECK(h == 4);
#endif

    int aa=24,bb=82;
    ranges::iter_swap(&aa, &bb);
    CHECK(aa == 82);
    CHECK(bb == 24);

    std::unique_ptr<int> u0{new int{1}};
    std::unique_ptr<int> u1{new int{2}};
    int *p0 = u0.get();
    int *p1 = u1.get();
    ranges::iter_swap(&u0, &u1);
    CHECK(u0.get() == p1);
    CHECK(u1.get() == p0);

    return ::test_result();
}
