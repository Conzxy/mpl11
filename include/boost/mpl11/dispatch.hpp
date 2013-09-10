/*!
 * @file
 * Defines `boost::mpl11::dispatch`.
 */

#ifndef BOOST_MPL11_DISPATCH_HPP
#define BOOST_MPL11_DISPATCH_HPP

#include <boost/mpl11/detail/always_false.hpp>


namespace boost { namespace mpl11 {
    namespace detail {
        template <typename OperationTag>
        struct default_;
    }

    template <typename OperationTag, typename ...Args>
    struct dispatch
        : dispatch<detail::default_<OperationTag>, Args...>
    { };

    template <typename OperationTag, typename ...Args>
    struct dispatch<detail::default_<OperationTag>, Args...> {
        static_assert(detail::always_false<OperationTag, Args...>::value,
        "No default implementation is provided for the requested "
        "operation with the arguments provided.");
    };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_DISPATCH_HPP