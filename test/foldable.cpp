/*!
 * @file
 * Contains unit tests for `boost::mpl11::Foldable`.
 */

#include <boost/mpl11/foldable.hpp>

#include <boost/mpl11/detail/is_same.hpp>


using namespace boost::mpl11;
using detail::is_same;

///////////////////////////
// Test method dispatching
///////////////////////////
struct archetype { struct mpl_tag; };
struct foldr_tag;
struct foldl_tag;

namespace boost { namespace mpl11 {
    template <>
    struct Foldable<archetype::mpl_tag> {
        template <typename, typename, typename>
        struct foldr_impl { using type = foldr_tag; };

        template <typename, typename, typename>
        struct foldl_impl { using type = foldl_tag; };
    };
}} // end namespace boost::mpl11

struct F; struct State;
static_assert(is_same<foldr_t<F, State, archetype>, foldr_tag>::value, "");
static_assert(is_same<foldl_t<F, State, archetype>, foldl_tag>::value, "");


int main() { }