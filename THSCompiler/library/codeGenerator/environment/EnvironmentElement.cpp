#pragma once

#include <memory>
#include <string>

/// @brief Combines an identifier with an element of type T; used in AbstractEnvironment
template <class T>
class EnvironmentElement
{
   public:
    EnvironmentElement(std::string identifier, std::shared_ptr<T> element)
    {
        this->identifier = identifier;
        this->element = element;
    }

    bool IsThisElement(std::string identifier) { return this->identifier == identifier; }

    std::shared_ptr<T> GetElement() { return element; }

   private:
    std::string identifier;
    std::shared_ptr<T> element;
};