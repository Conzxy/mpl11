/*!
 * @file
 * Defines `boost::mpl11::intrinsic::erase`.
 */

#ifndef BOOST_MPL11_INTRINSIC_ERASE_HPP
#define BOOST_MPL11_INTRINSIC_ERASE_HPP

#include <boost/mpl11/algorithm/copy.hpp>
#include <boost/mpl11/detail/doxygen_only.hpp>
#include <boost/mpl11/detail/forward_decls.hpp>
#include <boost/mpl11/detail/optional.hpp>
#include <boost/mpl11/dispatch.hpp>
#include <boost/mpl11/intrinsic/begin.hpp>
#include <boost/mpl11/intrinsic/clear.hpp>
#include <boost/mpl11/intrinsic/end.hpp>
#include <boost/mpl11/intrinsic/equal_to.hpp>
#include <boost/mpl11/intrinsic/next.hpp>
#include <boost/mpl11/tags.hpp>
#include <boost/mpl11/view/bounded_by.hpp>
#include <boost/mpl11/view/joined.hpp>


namespace boost { namespace mpl11 {
namespace intrinsic {
    /*!
     * @ingroup intrinsic
     *
     * Overloaded intrinsic for removing elements from a sequence.
     */
    template <typename Sequence,
              typename First,
              typename Last = detail::optional>
    struct erase;

    /*!
     * @ingroup intrinsic
     *
     * Removes several adjacent elements in a sequence starting from an
     * arbitrary position.
     *
     *
     * ### Semantics and default implementation
     *
     * Equivalent to copying the whole sequence except for the content of the
     * range delimited by [`First`, `Last`).
     *
     *
     * @warning
     * Differences from the original MPL:
     * - It is possible to erase a range of elements in an
     *   `AssociativeSequence`.
     */
    template <typename Sequence, typename First, typename Last>
    struct erase BOOST_MPL11_DOXYGEN_ONLY(<Sequence, First, Last>)
        : dispatch<tag::erase, Sequence, First, Last>
    { };

    /*!
     * @ingroup intrinsic
     *
     * Removes an element at a position in a sequence.
     *
     *
     * ## Semantics and default implementation
     *
     * Equivalent to `erase<Sequence, Position, next<Position>::type>`.
     *
     *
     * @warning
     * Differences from the original MPL:
     * - The semantics are the same for all types of sequences.
     */
    template <typename Sequence, typename Position>
    struct erase<Sequence, Position>
        : dispatch<tag::erase, Sequence, Position>
    { };
} // end namespace intrinsic

namespace erase_detail {
    template <typename Sequence, typename First, typename Last,
              bool = intrinsic::equal_to<
                Last, typename intrinsic::end<Sequence>::type
              >::type::value>
    struct erase_impl
        : algorithm::copy<
            view::bounded_by<
                typename intrinsic::begin<Sequence>::type, First
            >,
            typename intrinsic::clear<Sequence>::type
        >
    { };

    template <typename Sequence, typename First, typename Last>
    struct erase_impl<Sequence, First, Last, false>
        : algorithm::copy<
            view::joined<
                view::bounded_by<
                    typename intrinsic::begin<Sequence>::type, First
                >,
                view::bounded_by<
                    typename intrinsic::next<Last>::type,
                    typename intrinsic::end<Sequence>::type
                >
            >,
            typename intrinsic::clear<Sequence>::type
        >
    { };
} // end namespace erase_detail

template <typename Sequence, typename Position>
struct dispatch<detail::default_<tag::erase>, Sequence, Position>
    : intrinsic::erase<
        Sequence, Position, typename intrinsic::next<Position>::type
    >
{ };

template <typename Sequence, typename First, typename Last>
struct dispatch<detail::default_<tag::erase>, Sequence, First, Last>
    : erase_detail::erase_impl<Sequence, First, Last>
{ };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_INTRINSIC_ERASE_HPP
