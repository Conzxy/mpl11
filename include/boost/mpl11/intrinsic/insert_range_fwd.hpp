/*!
 * @file
 * Defines `boost::mpl11::insert_range`.
 */

#ifndef BOOST_MPL11_INTRINSIC_INSERT_RANGE_HPP
#define BOOST_MPL11_INTRINSIC_INSERT_RANGE_HPP

#include <boost/mpl11/detail/doxygen_only.hpp>
#include <boost/mpl11/detail/optional.hpp>
#include <boost/mpl11/dispatch.hpp>


namespace boost { namespace mpl11 {
    namespace tag { struct insert_range : dispatch<insert_range> { }; }

    /*!
     * @ingroup intrinsics
     *
     * Overloaded intrinsic for inserting a range of elements in a sequence.
     */
    template <typename, typename, typename = detail::optional>
    struct insert_range;

    /*!
     * @ingroup intrinsics
     *
     * Inserts a range of elements at an arbitrary position in a
     * @ref RandomExtensibleSequence.
     *
     *
     * ### Semantics and default implementation
     *
     * Equivalent to copying the elements from the ranges
     * [`begin<Sequence>::type`, `Position`), `Range` and
     * [`Position`, `end<Sequence>::type`) into `clear<Sequence>::type`
     */
    template <typename Sequence, typename Position, typename Range>
    struct insert_range BOOST_MPL11_DOXYGEN_ONLY(<Sequence, Position, Range>)
        : dispatch<tag::insert_range, Sequence, Position, Range>
    { };

    /*!
     * @ingroup intrinsics
     *
     * Inserts a range of elements in an @ref AssociativeSequence.
     *
     *
     * ### Semantics and default implementation
     *
     * Equivalent to `foldl<Range, Sequence, insert<_1, _2>>`.
     *
     *
     * @warning
     * Differences from the original MPL:
     * - It is possible to use `insert_range` on
     *   @ref AssociativeSequence "Associative Sequences".
     */
    template <typename Sequence, typename Range>
    struct insert_range<Sequence, Range>
        : dispatch<tag::insert_range, Sequence, Range>
    { };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_INTRINSIC_INSERT_RANGE_HPP