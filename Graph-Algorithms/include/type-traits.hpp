/**
 * @file type-traits.hpp
 * @breif Some template metaprogramming constructs
 */

#ifndef _TYPE_TRAITS_HPP_INCLUDED
#define _TYPE_TRAITS_HPP_INCLUDED

template <bool, class if_true, class if_false>
struct if_{};

template <class if_true, class if_false>
struct if_<true, if_true, if_false> {
  typedef if_true value;
};

template <class if_true, class if_false>
struct if_<false, if_true, if_false> {
  typedef if_false value;
};

class Empty {};

#endif // _TYPE_TRAITS_HPP_INCLUDED