/*!
 * @file
 * Forward declares `boost::mpl11::shift_right`.
 */

#ifndef BOOST_MPL11_FWD_SHIFT_RIGHT_HPP
#define BOOST_MPL11_FWD_SHIFT_RIGHT_HPP

namespace boost { namespace mpl11 {
    /*!
     * @ingroup bitwise_operators
     *
     * Returns the result of bitwise _shift right_ operation on an
     * @ref IntegralConstant.
     *
     *
     * ### Semantics and default implementation
     *
     * Equivalent to
     * `identity<integral_c<decltype(T::value >> Shift::value),
     *                      T::value >> Shift::value>>`.
     */
    template <typename T, typename Shift>
    struct shift_right;
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_FWD_SHIFT_RIGHT_HPP
