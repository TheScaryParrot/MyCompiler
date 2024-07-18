#pragma once

#include <map>

template <typename Key, typename Value>
class Map
{
   private:
    std::map<Key, Value> map;

   public:
    void Insert(Key key, Value value) { map[key] = value; }
    Value Get(Key key) { return map[key]; }
    bool Contains(Key key) { return map.find(key) != map.end(); }

    typename std::map<Key, Value>::iterator begin() { return map.begin(); }
    typename std::map<Key, Value>::iterator end() { return map.end(); }
};