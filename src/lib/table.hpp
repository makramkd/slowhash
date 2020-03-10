#ifndef SLOWHASH_TABLE_HPP
#define SLOWHASH_TABLE_HPP

#include <cstdlib>

#include "src/lib/item.hpp"
#include "src/lib/hash.hpp"

namespace slowhash
{
  struct hash_table {
    /// The capacity of the hash table - how many buckets
    size_t size;

    /// How many items are currently stored in the table
    size_t count;

    /// The table itself
    // TODO: use std::vector instead
    table_item **items;

    /// Hasher function object
    string_hasher hasher;

    // Constructors/Destructors

    hash_table()
    : size(53),
      count(0)
    {
      // Allocate an array of points to table_item objects
      // TODO: simplify
      items = static_cast<table_item**>(std::calloc(this->size, sizeof(table_item*)));

      // ASCII character set size is 128 - 131 is the next largest prime after that
      hasher.prime_a = 131;
      // 137 is the next largest prime after 131.
      hasher.prime_b = 137;

      // num_buckets is the size of the current table
      hasher.num_buckets = size;
    }

    // Destructor: free items array
    ~hash_table()
    {
      for (int i = 0; i < this->size; ++i) {
        auto item = this->items[i];
        if (item != nullptr) {
          std::free(item);
        }
      }
      std::free(this->items);
    }

    // Modifiers

    void insert(const std::string& key, const std::string& value) {
      auto item = new table_item(key, value);
      auto index = this->hasher(item->key, 0);
      auto curr_item = this->items[index];
      auto i = 1;
      while (curr_item != nullptr) {
        index = this->hasher(item->key, i);
        curr_item = this->items[index];
        ++i;
      }
      this->items[index] = item;
      this->count++;
    }

    const std::string& search(const std::string& key) {
      return "";
    }

    void remove(const std::string& key) {

    }
  };
} // namespace slowhash

#endif
