#pragma once

#include <vector>

template <typename Key, typename Value>
class Map
{
   private:
    std::vector<std::pair<Key, Value>> list;

   public:
    void Insert(Key key, Value value)
    {
        for (std::pair<Key, Value>& item : list)
        {
            if (item.first == key)
            {
                item.second = value;
            }
        }

        list.push_back(std::make_pair(key, value));
    }

    Value Get(Key key)
    {
        for (auto item : list)
        {
            if (item.first == key)
            {
                return item.second;
            }
        }

        throw std::invalid_argument("Key not found");
    }

    bool Contains(Key key)
    {
        for (auto item : list)
        {
            if (item.first == key)
            {
                return true;
            }
        }

        return false;
    }

    std::pair<Key, Value> At(size_t index) { return list[index]; }
    size_t Size() { return list.size(); }

    typename std::vector<std::pair<Key, Value>>::iterator begin() { return list.begin(); }
    typename std::vector<std::pair<Key, Value>>::iterator end() { return list.end(); }
};