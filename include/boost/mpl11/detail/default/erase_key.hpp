/*!
 * @file
 * Defines the default implementation of `boost::mpl11::intrinsic::erase_key`.
 */

#ifndef BOOST_MPL11_DETAIL_DEFAULT_ERASE_KEY_HPP
#define BOOST_MPL11_DETAIL_DEFAULT_ERASE_KEY_HPP

#include <boost/mpl11/algorithm/copy.hpp>
#include <boost/mpl11/arg.hpp>
#include <boost/mpl11/dispatch.hpp>
#include <boost/mpl11/intrinsic/clear.hpp>
#include <boost/mpl11/intrinsic/key_of.hpp>
#include <boost/mpl11/intrinsic/not_equal_to.hpp>
#include <boost/mpl11/tags.hpp>
#include <boost/mpl11/view/filtered.hpp>


namespace boost { namespace mpl11 {
template <typename Sequence, typename Key>
struct dispatch<detail::default_<tag::erase_key>, Sequence, Key>
    : algorithm::copy<
        view::filtered<
            Sequence,
            intrinsic::not_equal_to<Key, intrinsic::key_of<Sequence, _1>>
        >,
        typename intrinsic::clear<Sequence>::type
    >
{ };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_DETAIL_DEFAULT_ERASE_KEY_HPP