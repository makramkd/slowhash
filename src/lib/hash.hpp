#ifndef SLOWHASH_HASH_HPP
#define SLOWHASH_HASH_HPP

#include <cstddef>
#include <string>
#include <cmath>
#include <type_traits>

namespace slowhash
{
  /// A string hasher that uses open addressing with double hashing to avoid collisions.
  /// The two main parameters this hasher requires is a prime number that is larger
  /// than the character set size (e.g, if ASCII, using 131 is sufficient) and the number
  /// of buckets in the hash table that this is being used in.
  struct string_hasher {
    /// A prime number that is larger than the alphabet size.
    /// This is used in the hash computation.
    std::size_t prime_a;

    /// A prime number that is larger than the alphabet size.
    /// This is used in the hash computation. It is vital that
    /// this is not equal to prime_a to ensure a correct hash computation.
    std::size_t prime_b;

    /// The number of buckets in the target hash table
    std::size_t num_buckets;

    /// Construct a string hasher from the given prime_a, prime_b prime factors
    /// and the given num_buckets parameter.
    /// It is vital that prime_a is not equal to prime_b for valid hashes to be computed.
    /// In the interest of performance no invalid_argument exception is thrown if this is the case.
    string_hasher(std::size_t prime_a, std::size_t prime_b, std::size_t num_buckets)
    : prime_a(prime_a),
      prime_b(prime_b),
      num_buckets(num_buckets)
    {}

    /// Default constructor so that this can be embedded in classes
    string_hasher()
    : prime_a(0),
      prime_b(1),
      num_buckets(1)
    {}

    ~string_hasher() {}

    std::size_t operator()(const std::string& s, const std::size_t& attempt) const noexcept {
      const auto hash_a = this->__hash(s, prime_a);
      const auto hash_b = this->__hash(s, prime_b);
      return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
    }

  private:
    std::size_t __hash(const std::string s, std::size_t prime_factor) const noexcept {
      std::size_t hash = 0;
      auto strlen = s.size();
      for (auto i = 0; i < strlen; ++i) {
        hash += ((std::size_t) std::pow(prime_factor, strlen - (i + 1))) * s[i];
        hash %= num_buckets;
      }
      return hash;
    }
  };

  // Forward declaration: in order to use enable_if is_integral in the actual
  // class definition.
  template<typename T, typename = void> struct integral_hasher;

  /// Simple integral hasher that is essentially an identity function.
  /// Integral types are trivial to hash since they already exist in the domain
  /// that we care about - the integers. The caller provides a num_buckets parameter
  /// that it is up to them to make sure it is good enough (i.e, large enough and prime).
  /// The returned hashed value will be at most num_buckets in terms of integral value.
  template<typename T>
  struct integral_hasher<T, typename std::enable_if<std::is_integral<T>::value>::type> {
    std::size_t num_buckets;

    explicit integral_hasher(std::size_t num_buckets)
    : num_buckets(num_buckets)
    {}

    std::size_t operator()(const T& val) const noexcept {
      return val % num_buckets;
    }
  };
} // namespace slowhash

#endif
