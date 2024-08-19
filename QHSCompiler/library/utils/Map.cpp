#pragma once

#include <map>

template <typename Key, typename Value>
class Map
{
   private:
    std::map<Key, Value> map;

   public:
    Map(std::map<Key, Value> map) { this->map = map; }

    void Set(Key key, Value value) { map[key] = value; }

    Value Get(Key key) { return map[key]; }

    bool Contains(Key key) { return map.count(key) > 0; }

    size_t Size() { return map.size(); }
};