#ifndef SLOWHASH_PRIME_HPP
#define SLOWHASH_PRIME_HPP

#include <type_traits>
#include <cmath>

namespace slowhash
{
  /// Return whether the given integral argument is prime or not.
  /// 1 - prime
  /// 0 - not prime
  /// -1 - undefined (i.e x < 2) TODO: is this necessary?
  // TODO: figure out how to SFINAE if T is not integral
  template<typename T>
  int is_prime(const T& x) {
    if (x < 2) {
      return -1;
    }
    if (x < 4) {
      return 1;
    }
    if ((x % 2) == 0) {
      return 0;
    }
    for (T i = 3; i <= std::floor(std::sqrt(static_cast<double>(x))); i += 2) {
      if ((x % i) == 0) {
        return 0;
      }
    }
    return 1;
  }

  /// Return the next prime after x, or x if it is prime itself.
  // TODO: figure out how to SFINAE if T is not integral
  template<typename T>
  T next_prime(T x) {
    while (is_prime(x) != 1) {
      x++;
    }
    return x;
  }
} // namespace slowhash


#endif
