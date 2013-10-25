/*!
 * @file
 * Forward declares `boost::mpl11::erase`.
 */

#ifndef BOOST_MPL11_FWD_ERASE_HPP
#define BOOST_MPL11_FWD_ERASE_HPP

#include <boost/mpl11/detail/doxygen_only.hpp>
#include <boost/mpl11/detail/optional.hpp>


namespace boost { namespace mpl11 {
    /*!
     * @ingroup intrinsics
     *
     * Removes several adjacent elements in a sequence,
     * starting from an arbitrary position.
     *
     *
     * ### Semantics and default implementation
     *
     * Equivalent to returning a sequence containing the whole original
     * sequence except for the content of the range delimited by
     * [`First`, `Last`).
     */
    template <typename Sequence, typename First, typename Last>
    struct erase BOOST_MPL11_DOXYGEN_ONLY(<Sequence, First, Last>);

    /*!
     * @ingroup intrinsics
     *
     * Removes an element at a position in a sequence.
     *
     *
     * ## Semantics and default implementation
     *
     * Equivalent to `erase<Sequence, Position, next<Position>::type>`.
     */
    template <typename Sequence, typename Position>
    struct erase<Sequence, Position>;
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_FWD_ERASE_HPP
