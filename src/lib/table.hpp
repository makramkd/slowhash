#ifndef SLOWHASH_TABLE_HPP
#define SLOWHASH_TABLE_HPP

#include <cstdlib>
#include <exception>
#include <iostream>
#include <optional>

#include "src/lib/item.hpp"
#include "src/lib/hash.hpp"

namespace slowhash
{
  // TODO:
  // Template on key type and value type
  // Template on given hasher
  // Provide typedefs like key_type, value_type, etc. that are provided in std::map
  struct hash_table {
  private:
    /// The capacity of the hash table - how many buckets
    // TODO: rename this to capacity
    std::size_t size;

    /// How many items are currently stored in the table
    // TODO: rename this to size
    std::size_t count;

    /// The table itself
    // TODO: use std::vector<std::unique_ptr> instead
    table_item **items;

    /// Hasher function object
    string_hasher hasher;

    // sentinel node to use to refer to deleted key/value pairs in the table
    table_item *deleted_sentinel;

    // Constructors/Destructors
  public:
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

      // initialize deleted_sentinel
      deleted_sentinel = new table_item("", "");
    }

    // Destructor: free items array
    ~hash_table()
    {
      for (int i = 0; i < this->size; ++i) {
        auto item = this->items[i];
        // NOTE: should not delete the sentinel using std::free()
        // since it was allocated using new()
        if (item != nullptr && item != this->deleted_sentinel) {
          std::free(item);
        }
      }
      std::free(this->items);
      delete deleted_sentinel;
    }

    // Accessors
    std::size_t get_size() const {
      return this->size;
    }

    std::size_t get_count() const {
      return this->count;
    }

    // Modifiers

    void insert(const std::string& key, const std::string& value) {
      // Iterate through indexes until we find an empty bucket.
      // Insert the item into that bucket and increment the count member variable.
      auto item = new table_item(key, value);
      auto index = this->hasher(key, 0);
      auto curr_item = this->items[index];
      auto i = 1;
      while (curr_item != nullptr) {
        // Overwriting existing keys with new values
        if (curr_item != deleted_sentinel && curr_item->key == key) {
          delete curr_item;
          this->items[index] = item;
          return;
        }
        index = this->hasher(key, i);
        curr_item = this->items[index];
        ++i;
      }
      this->items[index] = item;
      this->count++;
    }

    std::optional<std::string> search(const std::string& key) {
      auto index = this->hasher(key, 0);
      auto curr_item = this->items[index];
      auto i = 1;
      while (curr_item != nullptr) {
        if (curr_item != deleted_sentinel && curr_item->key == key) {
          return curr_item->value;
        }
        index = this->hasher(key, i);
        curr_item = this->items[index];
        ++i;
      }

      return {};
    }

    void remove(const std::string& key) {
      // Item that we want to delete may be part of a collision chain.
      // Removing it from the table will break that chain, and will make
      // finding items in the tail of the chain impossible. Instead we simply
      // mark those items as deleted.
      auto index = this->hasher(key, 0);
      auto curr_item = this->items[index];
      auto i = 1;
      while (curr_item != nullptr) {
        if (curr_item != deleted_sentinel && curr_item->key == key) {
          delete curr_item;
          this->items[index] = deleted_sentinel;
          // TODO: add return here?
        }
        index = this->hasher(key, i);
        curr_item = this->items[index];
        ++i;
      }
      this->count--;
    }

    // utility

    // TODO: implement for ease of printing and debugging
    friend std::ostream& operator<<(std::ostream& stream, const hash_table& table) {
      return stream;
    }
  };
} // namespace slowhash

#endif
