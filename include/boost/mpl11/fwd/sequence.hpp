/*!
 * @file
 * Forward declares `boost::mpl11::Sequence`.
 */

#ifndef BOOST_MPL11_FWD_SEQUENCE_HPP
#define BOOST_MPL11_FWD_SEQUENCE_HPP

#include <boost/mpl11/detail/doxygen.hpp>
#include <boost/mpl11/detail/methods.hpp>
#include <boost/mpl11/detail/std_size_t.hpp>
#include <boost/mpl11/fwd/comparable.hpp>
#include <boost/mpl11/fwd/orderable.hpp>


namespace boost { namespace mpl11 {
    /*!
     * @ingroup typeclasses
     * @defgroup Sequence Sequence
     *
     * Collection of objects.
     *
     * @todo Write more information about this.
     *
     *
     * ### Refines
     * - `Comparable` when the elements in the sequence are `Comparable`.
     * - `Orderable` when the elements in the sequence are `Orderable`.
     *
     * ### Methods
     * `head`, `tail`, `is_empty`, `last`, `init`, `at_c`, `at`,
     * `length` and `unpack`.
     *
     * `at` is only a wrapper over `at_c`. It is provided for convenience but
     * it is not implemented inside the typeclass.
     *
     * ### Minimal complete definition
     * `head`, `tail` and `is_empty`.
     *
     *
     * @note
     * `Sequence`s are not required to be finite. If a `Sequence` is infinite,
     * some methods such as `length` and `unpack` are not well-defined. The
     * well-definedness of some other methods such as `init` and `last`
     * depends on the particular sequence.
     *
     * @{
     */
    template <typename Tag>
    struct Sequence;

#ifndef BOOST_MPL11_DOXYGEN_INVOKED
    namespace unchecked {
#endif

    //! Returns the first element of a non-empty `Sequence`.
    template <typename S>                           struct head;

    /*!
     * Extract the elements after the head of a non-empty `Sequence`.
     *
     * Specifically, returns a sequence containing all the elements of the
     * original sequence except the first one.
     */
    template <typename S>                           struct tail;

    //! Boolean `Integral` representing whether the given `Sequence` is empty.
    template <typename S>                           struct is_empty;

    //! Returns the last element of a non-empty `Sequence`.
    template <typename S>                           struct last;

    /*!
     * Extract the elements before the last of a non-empty `Sequence`.
     *
     * Specifically, returns a sequence containing all the elements of the
     * original sequence except the last one.
     */
    template <typename S>                           struct init;

    //! Returns the element of a `Sequence` at the given index.
    template <typename S, detail::std_size_t Index> struct at_c;

    //! Equivalent to `at_c<S, Index::value>`;
    //! requires a non-negative `Index`.
    template <typename S, typename Index>           struct at;

    //! `Integral` of unsigned type representing the number of elements in
    //! a finite `Sequence`.
    template <typename S>                           struct length;

    /*!
     * Invokes a metafunction class with the contents of a finite `Sequence`.
     *
     * Specifically, `unpack<S, F>` is a nullary metafunction equivalent
     * to `apply<F, a0, ..., an>`, where `a0`, ...,`an` are the elements
     * in the sequence.
     */
    template <typename S, typename F>               struct unpack;

#ifndef BOOST_MPL11_DOXYGEN_INVOKED
    } // end namespace unchecked

    namespace checked {
        template <typename S>                           struct head;
        template <typename S>                           struct tail;
        template <typename S>                           struct last;
        template <typename S>                           struct init;
        template <typename S, detail::std_size_t Index> struct at_c;
        template <typename S, typename Index>           struct at;
        using unchecked::is_empty;
        using unchecked::length;
        using unchecked::unpack;
    }

    using methods::head;
    using methods::tail;
    using methods::last;
    using methods::init;
    using methods::is_empty;
    using methods::at_c;
    using methods::at;
    using methods::length;
    using methods::unpack;
#endif // !BOOST_MPL11_DOXYGEN_INVOKED

    template <typename S>
    using head_t = typename head<S>::type;

    template <typename S>
    using tail_t = typename tail<S>::type;

    template <typename S>
    using is_empty_t = typename is_empty<S>::type;

    template <typename S>
    using last_t = typename last<S>::type;

    template <typename S>
    using init_t = typename init<S>::type;

    template <typename S, detail::std_size_t Index>
    using at_c_t = typename at_c<S, Index>::type;

    template <typename S, typename Index>
    using at_t = typename at<S, Index>::type;

    template <typename S>
    using length_t = typename length<S>::type;

    template <typename S, typename F>
    using unpack_t = typename unpack<S, F>::type;

    //! @}

    /*!
     * @ingroup tags
     *
     * Tag representing the `Sequence` typeclass.
     */
    struct sequence_tag BOOST_MPL11_DOXYGEN_ONLY({ });

    /*!
     * Default instantiation of the `Sequence` typeclass for `Sequence`s.
     */
    template <>
    struct Sequence<sequence_tag>;

    /*!
     * Default instantiation of the `Comparable` typeclass for `Sequence`s.
     *
     * Two `Sequence`s are equal if their elements are equal when compared
     * side-by-side, and if both sequences run out of elements at the same
     * time, i.e. if they have the same length. The inequality of two
     * `Sequence`s is defined in terms of their equality.
     */
    template <>
    struct Comparable<sequence_tag, sequence_tag>;

    /*!
     * Default instantiation of the `Orderable` typeclass for `Sequence`s.
     *
     * Less-than comparison for `Sequence`s is defined as the lexicographical
     * comparison of their elements. Other comparison operators are defined
     * in terms of the less-than comparison.
     */
    template <>
    struct Orderable<sequence_tag, sequence_tag>;
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_FWD_SEQUENCE_HPP
