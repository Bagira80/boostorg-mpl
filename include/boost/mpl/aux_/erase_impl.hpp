
#ifndef BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/copy_backward.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost {
namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'erase_impl' or the primary 'erase' template

template< typename Tag >
struct erase_impl
{
    template<
          typename Sequence
        , typename First
        , typename Last
        >
    struct apply
    {
        typedef typename if_na< Last,typename next<First>::type >::type last_;
        
        // 1st half: [begin, first)
        typedef iterator_range<
              typename begin<Sequence>::type
            , First
            > first_half_;

        // 2nd half: [last, end) ... that is, [last + 1, end)
        typedef iterator_range<
              last_
            , typename end<Sequence>::type
            > second_half_;

        typedef typename copy_backward<
              second_half_
            , typename clear<Sequence>::type
            , push_front<_,_>
            >::type half_sequence_;

        typedef typename copy_backward<
              first_half_
            , half_sequence_
            , push_front<_,_>
            >::type type;
    };
};

}}

#endif // BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED
