#pragma once

#include <vector>

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
        for (std::shared_ptr<T> element : elements)
        {
            if (element->IsThisElement(identifier))
            {
                return element->GetElement();
            }
        }

        return nullptr;
    }

private:
    std::vector<std::shared_ptr<EnvironmentElement<T>>> elements;
};