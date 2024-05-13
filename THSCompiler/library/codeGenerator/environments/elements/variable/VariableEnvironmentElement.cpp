#include "../EnvironmentElement.cpp"

class VariableEnvironmentElement : public EnvironmentElement
{
public:
    VariableEnvironmentElement(std::string identifier, std::string type)
        : EnvironmentElement(identifier)
    {
        this->type = type;
    }

    std::string GetType()
    {
        return this->type;
    }
};