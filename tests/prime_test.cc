#include "gtest/gtest.h"

#include "src/lib/prime.hpp"

TEST(IsPrimeShould, ReturnTrueOnPrime) {
  auto prime = 131;
  auto ret = slowhash::is_prime(prime);
  EXPECT_EQ(1, ret);
}

TEST(IsPrimeShould, ReturnFalseOnComposite) {
  auto composite = 132;
  auto ret = slowhash::is_prime(composite);
  EXPECT_EQ(0, ret);
}

TEST(NextPrimeShould, ReturnNextPrime) {
  auto composite = 132;
  auto ret = slowhash::next_prime(composite);
  EXPECT_EQ(137, ret);
}
