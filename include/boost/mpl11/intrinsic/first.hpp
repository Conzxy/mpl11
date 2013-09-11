/*!
 * @file
 * Defines `boost::mpl11::first`.
 */

#ifndef BOOST_MPL11_INTRINSIC_FIRST_HPP
#define BOOST_MPL11_INTRINSIC_FIRST_HPP

#include <boost/mpl11/dispatch.hpp>
#include <boost/mpl11/tags.hpp>


namespace boost { namespace mpl11 {
    /*!
     * @ingroup intrinsics
     *
     * Returns the first element of a pair.
     *
     *
     * @warning
     * Differences from the original MPL:
     * - No default implementation is provided.
     * - The operation uses standard tag dispatching.
     */
    template <typename Pair>
    struct first
        : dispatch<tag::first, Pair>
    { };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_INTRINSIC_FIRST_HPP
