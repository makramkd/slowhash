#include "gtest/gtest.h"

#include "src/lib/table.hpp"

TEST(TableShould, ConstructCorrectly) {
  slowhash::hash_table table;
  EXPECT_EQ(53, table.get_size());
  EXPECT_EQ(0, table.get_count());
}

TEST(TableShould, InsertCorrectly) {
  slowhash::hash_table table;
  EXPECT_EQ(0, table.get_count());

  table.insert("hello", "world");
  EXPECT_EQ(1, table.get_count());

  auto val = table.search("hello");
  EXPECT_EQ(std::string("world"), val.value());
}
