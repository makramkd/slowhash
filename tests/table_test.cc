#include <vector>
#include <string>

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

TEST(TableShould, InsertCorrectly2) {
  slowhash::hash_table table;
  std::vector<std::pair<std::string, std::string>> key_values = {
    {"hello", "world"},
    {"today", "yes"},
    {"its", "okay"},
    {"bruh", "dont worry be happy like duh"},
    {"sexy", "and i know it"},
  };
  for (const auto& pair: key_values) {
    table.insert(pair.first, pair.second);
  }
  EXPECT_EQ(5, table.get_count());

  EXPECT_EQ(std::string("world"), table.search("hello").value());
  EXPECT_EQ(std::string("yes"), table.search("today").value());
  EXPECT_EQ(std::string("okay"), table.search("its").value());
  EXPECT_EQ(std::string("dont worry be happy like duh"), table.search("bruh").value());
  EXPECT_EQ(std::string("and i know it"), table.search("sexy").value());
}

TEST(TableShould, InsertCorrectly3) {
  // TODO: test insertion after a re-size
}

TEST(TableShould, RemoveCorrectly) {

}
