#pragma once

#include <vector>
#include <functional>

#include "EnvironmentElement.cpp"

/// @brief Basic Environment that holds EnvironmentElements and provides methods to add and get elements, based on their identifier
/// @tparam T 
template <class T>
class AbstractEnvironment
{
public:
    void AddElement(std::string identifier, std::shared_ptr<T> element)
    {
        elements.push_back(std::make_shared<EnvironmentElement<T>>(identifier, element));
    }

    std::shared_ptr<T> GetElement(std::string identifier)
    {
        return FindElement([identifier](std::shared_ptr<EnvironmentElement<T>> element) -> bool{return element->IsThisElement(identifier);});

        /*for (std::shared_ptr<T> element : elements)
        {
            if (element->IsThisElement(identifier))
            {
                return element->GetElement();
            }
        }

        return nullptr;*/
    }

    std::shared_ptr<T> FindElement(std::function<bool(std::shared_ptr<EnvironmentElement<T>>)> predicate)
    {
        for (std::shared_ptr<EnvironmentElement<T>> element : elements)
        {
            if (predicate(element))
            {
                return element;
            }
        }

        return nullptr;
    }

private:
    std::vector<std::shared_ptr<EnvironmentElement<T>>> elements;
};