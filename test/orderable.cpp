/*!
 * @file
 * Contains unit tests for the @ref Orderable typeclass.
 */

#include <boost/mpl11/orderable.hpp>

#include <boost/mpl11/core.hpp>
#include <boost/mpl11/detail/std_is_same.hpp>
#include <boost/mpl11/integral_c.hpp>


using namespace boost::mpl11;
using detail::std_is_same;

///////////////////////////
// Test method dispatching
///////////////////////////
struct OrderableArchetype;
struct archetype {
    struct type { using mpl_datatype = OrderableArchetype; };
};
struct less_tag;
struct less_equal_tag;
struct greater_tag;
struct greater_equal_tag;
struct min_tag;
struct max_tag;

namespace boost { namespace mpl11 {
    template <>
    struct Orderable<OrderableArchetype, OrderableArchetype> {
        template <typename, typename>
        struct less_impl { using type = less_tag; };

        template <typename, typename>
        struct less_equal_impl { using type = less_equal_tag; };

        template <typename, typename>
        struct greater_impl { using type = greater_tag; };

        template <typename, typename>
        struct greater_equal_impl { using type = greater_equal_tag; };

        template <typename, typename>
        struct min_impl { using type = min_tag; };

        template <typename, typename>
        struct max_impl { using type = max_tag; };
    };
}} // end namespace boost::mpl11

static_assert(std_is_same<
    less<archetype, archetype>::type,
    less_tag
>::value, "");

static_assert(std_is_same<
    less_equal<archetype, archetype>::type,
    less_equal_tag
>::value, "");

static_assert(std_is_same<
    greater<archetype, archetype>::type,
    greater_tag
>::value, "");

static_assert(std_is_same<
    greater_equal<archetype, archetype>::type,
    greater_equal_tag
>::value, "");

static_assert(std_is_same<
    min<archetype, archetype>::type,
    min_tag
>::value, "");

static_assert(std_is_same<
    max<archetype, archetype>::type,
    max_tag
>::value, "");


///////////////////////////
// Test provided defaults
///////////////////////////
struct x_datatype;
template <int i>
struct x {
    struct type {
        static constexpr int value = i;
        using mpl_datatype = x_datatype;
    };
};
namespace boost { namespace mpl11 {
    template <>
    struct Orderable<x_datatype, x_datatype>
        : Orderable<typeclass<Orderable>, typeclass<Orderable>>
    {
        template <typename x, typename y>
        using less_impl = bool_<(x::value < y::value)>;
    };
}}

template <int from, int to>
struct test_operators : test_operators<from, to+1> {
    static_assert(less<x<from>, x<to>>::value == from < to, "");
    static_assert(less_equal<x<from>, x<to>>::value == from <= to, "");
    static_assert(greater<x<from>, x<to>>::value == from > to, "");
    static_assert(greater_equal<x<from>, x<to>>::value == from >= to, "");
};

template <int from>
struct test_operators<from, 5> : test_operators<from+1, 0> { };

template <>
struct test_operators<5, 5> { };

static_assert(sizeof(test_operators<0, 0>), "");

// Test short-circuiting
static_assert(!less<x<1>, x<0>, undefined>::value, "");
static_assert(!less_equal<x<1>, x<0>, undefined>::value, "");
static_assert(!greater<x<0>, x<1>, undefined>::value, "");
static_assert(!greater_equal<x<0>, x<1>, undefined>::value, "");


// min
static_assert(min<x<0>, x<0>>::type::value == 0, "");
static_assert(min<x<0>, x<1>>::type::value == 0, "");
static_assert(min<x<1>, x<0>>::type::value == 0, "");
static_assert(min<x<0>, x<1>, x<2>>::type::value == 0, "");
static_assert(min<x<2>, x<1>, x<0>>::type::value == 0, "");

// max
static_assert(max<x<0>, x<0>>::type::value == 0, "");
static_assert(max<x<0>, x<1>>::type::value == 1, "");
static_assert(max<x<1>, x<0>>::type::value == 1, "");
static_assert(max<x<0>, x<1>, x<2>>::type::value == 2, "");
static_assert(max<x<2>, x<1>, x<0>>::type::value == 2, "");


int main() { }
