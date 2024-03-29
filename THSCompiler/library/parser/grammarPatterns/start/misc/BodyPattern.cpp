#pragma once

#include "../../IGrammarPattern.cpp"

#include "../../../../tokens/ConstTokens.cpp"
#include"../CodeBlock.cpp"

class BodyPattern : public IGrammarPattern
{
public:
    BodyPattern();
    ~BodyPattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static BodyPattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    CodeBlock* codeBlock;
};

BodyPattern::BodyPattern()
{
}

BodyPattern::~BodyPattern()
{
    delete codeBlock;
}

ELookAheadCertainties BodyPattern::LookAhead(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.BODY_OPEN_TOKEN))
    {
        return ELookAheadCertainties::CertainlyPresent;
    }

    return ELookAheadCertainties::CertainlyNotPresent;
}

BodyPattern* BodyPattern::Parse(TokenList* tokens)
{
    tokens->Next(); // Consume BODY_OPEN_TOKEN

    BodyPattern* bodyPattern = new BodyPattern();

    bodyPattern->codeBlock = CodeBlock::Parse(tokens);

    tokens->Next(); // Consume BODY_CLOSE_TOKEN

    return bodyPattern;
}

std::string BodyPattern::ToString()
{
    return "{\n" + codeBlock->ToString() + "\n}";
}