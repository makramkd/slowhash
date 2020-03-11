#ifndef SLOWHASH_TABLE_HPP
#define SLOWHASH_TABLE_HPP

#include <cstdlib>
#include <exception>
#include <iostream>

#include "src/lib/item.hpp"
#include "src/lib/hash.hpp"

namespace slowhash
{
  namespace exceptions {
    class key_not_found : public std::runtime_error {
      std::string message;
    public:
      key_not_found(const char *message) noexcept
      : std::runtime_error(message),
        message(message)
      {
      }

      const char* what() const throw() {
        return this->message.c_str();
      }
    };
  } // namespace exceptions

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
      // Iterate through indexes until we find an empty bucket.
      // Insert the item into that bucket and increment the count member variable.
      auto item = new table_item(key, value);
      slowhash::table_item *curr_item;
      std::size_t index;
      auto i = 0;
      do {
        index = this->hasher(item->key, i);
        curr_item = this->items[index];
        ++i;
      } while (curr_item != nullptr);
      this->items[index] = item;
      this->count++;
    }

    const std::string& search(const std::string& key) {
      auto i = 0;
      slowhash::table_item *item;
      std::size_t index;
      do {
        index = this->hasher(key, i);
        item = this->items[index];
        if (item->key == key) {
          return item->value;
        }
        ++i;
      } while (item != nullptr);

      // TODO: need to make a decision, either use exceptions or std::optional
      throw exceptions::key_not_found(("Could not find key: " + key + " in the hash table").c_str());
    }

    void remove(const std::string& key) {

    }

    // utility

    // TODO: implement for ease of printing and debugging
    friend std::ostream& operator<<(std::ostream& stream, const hash_table& table) {
      return stream;
    }
  };
} // namespace slowhash

#endif
