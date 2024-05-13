#include <string>

class EnvironmentElement
{
public:
    EnvironmentElement(std::string identifier)
    {
        this->identifier = identifier;
    }

    bool IsThisElement(std::string identifier)
    {
        return this->identifier == identifier;
    }

private:
    std::string identifier;
};