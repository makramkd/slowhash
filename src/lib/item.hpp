#ifndef SLOWHASH_ITEM_HPP
#define SLOWHASH_ITEM_HPP

#include <string>

namespace slowhash
{
  struct table_item {
    std::string key;
    std::string value;

    table_item(std::string key, std::string value)
    : key(key),
      value(value)
    {
    }

    ~table_item(){}
  };
} // namespace slowhash


#endif
