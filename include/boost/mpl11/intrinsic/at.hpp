/*!
 * @file
 * Defines `boost::mpl11::intrinsic::at` and `boost::mpl::intrinsic::at_c`.
 */

#ifndef BOOST_MPL11_INTRINSIC_AT_HPP
#define BOOST_MPL11_INTRINSIC_AT_HPP

#include <boost/mpl11/algorithm/advance.hpp>
#include <boost/mpl11/algorithm/find_if.hpp>
#include <boost/mpl11/arg.hpp>
#include <boost/mpl11/categories.hpp>
#include <boost/mpl11/detail/best_category_for.hpp>
#include <boost/mpl11/detail/doxygen_only.hpp>
#include <boost/mpl11/detail/is_same.hpp>
#include <boost/mpl11/detail/optional.hpp>
#include <boost/mpl11/detail/tag_dispatched.hpp>
#include <boost/mpl11/dispatch.hpp>
#include <boost/mpl11/identity.hpp>
#include <boost/mpl11/if.hpp>
#include <boost/mpl11/integral_c.hpp>
#include <boost/mpl11/intrinsic/begin.hpp>
#include <boost/mpl11/intrinsic/category_of.hpp>
#include <boost/mpl11/intrinsic/deref.hpp>
#include <boost/mpl11/intrinsic/end.hpp>
#include <boost/mpl11/intrinsic/equal_to.hpp>
#include <boost/mpl11/intrinsic/key_of.hpp>
#include <boost/mpl11/intrinsic/not_equal_to.hpp>
#include <boost/mpl11/intrinsic/value_of.hpp>
#include <boost/mpl11/tags.hpp>


namespace boost { namespace mpl11 {
namespace intrinsic {
    /*!
     * @ingroup intrinsic
     *
     * Overloaded intrinsic for accessing elements in a sequence.
     */
    template <typename SequenceOrAssociativeSequence,
              typename IndexOrKey,
              typename DefaultOrNothing = detail::optional>
    struct at;

    /*!
     * @ingroup intrinsic
     *
     * Returns the element associated to a key in an `AssociativeSequence`,
     * or a default value if no such element exists and a default is provided.
     *
     *
     * ### Semantics and default implementation
     *
     * When no `Default` is provided, equivalent to `at<Sequence, Key, X>`,
     * where `X` is a type such that a compile-time assertion is triggered
     * if `X` is returned.
     *
     * When a `Default` is provided, let `Iter` be the same as
       @code
            find_if<
                Sequence,
                equal_to<key_of<Sequence, _1>, Key>
            >::type
       @endcode
     * Then, `at` is equivalent to `value_of<Sequence, deref<Iter>::type>` if
       @code
            equal_to<
                Iter, end<Sequence>::type
            >::type::value
       @endcode
     * is `false`, and `identity<Default>` otherwise.
     *
     *
     * @warning
     * Differences from the original MPL:
     * - A compile-time assertion is triggered when no `Default` is provided
     *   and `Key` can't be found.
     * - A default implementation is provided for `AssociativeSequence`s.
     */
    template <typename Sequence, typename Key, typename Default>
    struct at BOOST_MPL11_DOXYGEN_ONLY(<Sequence, Key, Default>)
        : detail::tag_dispatched<tag::at, Sequence, Key, Default>
    { };

    /*!
     * @ingroup intrinsic
     *
     * Returns the `N`th element of a sequence if `N` is in the bounds of
     * the sequence, and triggers a compile-time assertion otherwise.
     *
     *
     * ### Semantics and default implementation
     *
     * Let `Iter` be the same as `advance<begin<Sequence>::type, N>::type`.
     * Then, `at` is equivalent to `deref<Iter>` if
       @code
            equal_to<
                Iter, end<Sequence>::type
            >::type::value
       @endcode
     * and `N::value < 0` are `false`, and a compile-time assertion
     * is triggered otherwise.
     *
     *
     * @warning
     * Differences from the original MPL:
     * - A compile-time assertion is triggered if `N` is out of the bounds of
     *   `Sequence`.
     */
    template <typename Sequence, typename N>
    struct at<Sequence, N>
        : detail::tag_dispatched<tag::at, Sequence, N>
    { };

    //! Convenience alias to `at<Sequence, ulong<N>>`.
    template <typename Sequence, unsigned long N>
    using at_c = at<Sequence, ulong<N>>;
} // end namespace intrinsic

namespace at_detail {
    template <typename Sequence, typename Iterator>
    struct value_deref
        : intrinsic::value_of<
            Sequence,
            typename intrinsic::deref<Iterator>::type
        >
    { };

    template <typename Category, typename ...>
    struct at_impl;

    template <typename Sequence, typename Key, typename Default>
    struct at_impl<category::associative_sequence, Sequence, Key, Default> {
    private:
        using Iter = typename algorithm::find_if<
            Sequence,
            intrinsic::equal_to<intrinsic::key_of<Sequence, _1>, Key>
        >::type;

        using WasNotFound = typename intrinsic::equal_to<
            Iter, typename intrinsic::end<Sequence>::type
        >::type;

    public:
        using type = typename if_<WasNotFound,
            identity<Default>,
            value_deref<Sequence, Iter>
        >::type::type;
    };

    struct not_found;

    template <typename Sequence, typename Key>
    struct at_impl<category::associative_sequence, Sequence, Key>
        : intrinsic::at<Sequence, Key, not_found>
    {
        static_assert(
            !detail::is_same<typename at_dispatched::type, not_found>::value,
        "Could not find the value associated to a given key in an associated "
        "sequence and no default return value was specified.");
    };

    template <typename Sequence, typename N>
    struct at_impl<category::forward_sequence, Sequence, N> {
    private:
        using Iter = typename algorithm::advance<
            typename intrinsic::begin<Sequence>::type, N
        >::type;

        static_assert(
            N::value >= 0 &&
            intrinsic::not_equal_to<
                Iter, typename intrinsic::end<Sequence>::type
            >::type::value,
        "Trying to access a sequence at an index that is out of bounds.");

    public:
        using type = typename deref<Iter>::type;
    };
} // end namespace at_detail

template <typename Sequence, typename Key, typename ...Default>
struct dispatch<detail::default_<tag::at>, Sequence, Key, Default...>
    : at_detail::at_impl<
        typename detail::best_category_for<Sequence,
            category::associative_sequence,
            category::forward_sequence
        >::type,
        Sequence, Key, Default...
    >
{ };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_INTRINSIC_AT_HPP
