#include "gtest/gtest.h"

#include "src/lib/table.hpp"

TEST(TableShould, ConstructCorrectly) {
  slowhash::hash_table table;
  EXPECT_EQ(53, table.size);
  EXPECT_EQ(0, table.count);
}
