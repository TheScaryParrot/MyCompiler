#pragma once

#include <memory>

#include "../assembly/AssemblyCode.cpp"
#include "../syntaxTree/SyntaxTree.cpp"
#include "../syntaxTree/nodes/line/declaration/AbstractDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/declarationAttributes/ESyntaxTreeScopes.cpp"
#include "../syntaxTree/nodes/line/expression/AbstractValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/AssignmentNode.cpp"
#include "../syntaxTree/nodes/line/expression/OperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/UnaryExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/functionCall/CallNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/AbstractConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/IDValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/LogicalConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/NumberConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/StaticValueChainNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/StringConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/ValueChainNode.cpp"
#include "../syntaxTree/nodes/line/statement/AbstractStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/AbstractKeywordStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/BreakStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ContinueStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ForStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/IfStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ReturnStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/WhileStatementNode.cpp"
#include "generator/CodeGenerator.cpp"

static class OldSyntaxTreeTraverser
{
   public:
    std::shared_ptr<AssemblyCode> GenerateCode(SyntaxTree* syntaxTree);

   private:
    CodeGenerator codeGenerator;

    AssemblyCode* GenerateCodeBlock(CodeblockNode* codeBlock);

    AssemblyCode* GenerateLine(AbstractLineNode* line);

    AssemblyCode* GenerateDeclaration(AbstractDeclarationNode* declaration);
    AssemblyCode* GenerateVarDeclaration(VarDeclarationNode* declaration);
    AssemblyCode* GenerateFuncDeclaration(FuncDeclarationNode* declaration);
    AssemblyCode* GenerateClassDeclaration(ClassDeclarationNode* declaration);

    AssemblyCode* GenerateStatement(AbstractStatementNode* statement, bool environmentLock);
    AssemblyCode* GenerateBody(BodyNode* body);

    AssemblyCode* GenerateKeywordStatement(AbstractKeywordStatementNode* statement);
    AssemblyCode* GenerateIfStatement(IfStatementNode* statement);
    AssemblyCode* GenerateIfStatement(IfStatementNode* statement, std::string finalLabel);
    AssemblyCode* GenerateReturnStatement(ReturnStatementNode* statement);
    AssemblyCode* GenerateWhileStatement(WhileStatementNode* whileStatement);
    AssemblyCode* GenerateForStatement(ForStatementNode* forStatement);
    AssemblyCode* GenerateContinueStatement(ContinueStatementNode* statement);
    AssemblyCode* GenerateBreakStatement(BreakStatementNode* statement);

    AssemblyCode* GenerateExpression(AbstractExpressionNode* expression);

    AssemblyCode* GenerateAssignment(AssignmentNode* assignment);
    AssemblyCode* GenerateBinaryOperation(OperatorExpressionNode* binaryOperation);
    AssemblyCode* GenerateUnaryOperation(UnaryExpressionNode* unaryOperation);

    AssemblyCode* GenerateValue(AbstractValueNode* value);
    AssemblyCode* GenerateValueChain(ValueChainNode* valueChain);
    AssemblyCode* GenerateStaticValueChain(StaticValueChainNode* valueChain);
    AssemblyCode* GenerateConstValue(AbstractConstValueNode* value);
    AssemblyCode* GenerateIDValue(IDValueNode* value);
    AssemblyCode* GenerateCall(CallNode* call);

} OldSyntaxTreeTraverser;

std::shared_ptr<AssemblyCode> OldSyntaxTreeTraverser::GenerateCode(SyntaxTree* syntaxTree)
{
    codeGenerator = CodeGenerator();  // Initialize code generator

    return std::shared_ptr<AssemblyCode>(GenerateCodeBlock(syntaxTree->GetCodeBlock()));
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateCodeBlock(CodeblockNode* codeBlock)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (size_t i = 0; i < codeBlock->GetLineCount(); i++)
    {
        assemblyCode->AddLines(GenerateLine(codeBlock->GetLine(i)));
    }

    return assemblyCode;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateLine(AbstractLineNode* line)
{
    if (line == nullptr)
    {
        std::cout << "Line is null\n";
        return nullptr;
    }

    // FIXME: Solve this without dynamic_cast; visitor pattern with
    // IOldSyntaxTreeTraverser?
    if (dynamic_cast<AbstractDeclarationNode*>(line) != nullptr)
    {
        return GenerateDeclaration(dynamic_cast<AbstractDeclarationNode*>(line));
    }

    // Generate statement
    return GenerateStatement(dynamic_cast<AbstractStatementNode*>(line), false);
};

#pragma region Declarations
AssemblyCode* OldSyntaxTreeTraverser::GenerateDeclaration(AbstractDeclarationNode* declaration)
{
    if (dynamic_cast<VarDeclarationNode*>(declaration) != nullptr)
    {
        return GenerateVarDeclaration(dynamic_cast<VarDeclarationNode*>(declaration));
    }

    if (dynamic_cast<FuncDeclarationNode*>(declaration) != nullptr)
    {
        return GenerateFuncDeclaration(dynamic_cast<FuncDeclarationNode*>(declaration));
    }

    return GenerateClassDeclaration(dynamic_cast<ClassDeclarationNode*>(declaration));
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateVarDeclaration(VarDeclarationNode* declaration)
{
    DeclarationAttributes attributes = DeclarationAttributes();
    attributes.isFinal = declaration->attributes.isFinal;
    attributes.isInline = declaration->attributes.isInline;

    switch (declaration->attributes.scope)
    {
        case ESyntaxTreeScopes::PUBLIC:
            attributes.scope = EScopes::PUBLIC;
            break;
        case ESyntaxTreeScopes::PROTECTED:
            attributes.scope = EScopes::PROTECTED;
            break;
        case ESyntaxTreeScopes::PRIVATE:
            attributes.scope = EScopes::PRIVATE;
            break;
    }

    // TODO: Use static
    //  FIXME: AddVariable should also return assembly code
    Variable* variable = codeGenerator.AddVariable(declaration->name, declaration->type.GetIdentfier(), attributes);

    // TODO: Assign value
    return nullptr;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateFuncDeclaration(FuncDeclarationNode* declaration)
{
    DeclarationAttributes attributes = DeclarationAttributes();
    attributes.isFinal = declaration->attributes.isFinal;
    attributes.isInline = declaration->attributes.isInline;

    switch (declaration->attributes.scope)
    {
        case ESyntaxTreeScopes::PUBLIC:
            attributes.scope = EScopes::PUBLIC;
            break;
        case ESyntaxTreeScopes::PROTECTED:
            attributes.scope = EScopes::PROTECTED;
            break;
        case ESyntaxTreeScopes::PRIVATE:
            attributes.scope = EScopes::PRIVATE;
            break;
    }

    Function* function;

    if (declaration->returnType.IsVoid())
    {
        function = codeGenerator.AddVoidFunction(declaration->name, attributes);
    }
    else
    {
        function = codeGenerator.AddFunction(declaration->name, declaration->returnType.GetIdentfier(), attributes);
    }

    codeGenerator.PushEnvironment(std::make_shared<FunctionScopeEnvironment>());
    AssemblyCode* body = GenerateStatement(declaration->statement,
                                           true);  // Lock environment as function environment was already created
    codeGenerator.PopEnvironment();

    return codeGenerator.SetFunctionBody(function, body);
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateClassDeclaration(ClassDeclarationNode* declaration)
{
    Type* type = codeGenerator.AddType(declaration->name);
    ClassScopeEnvironment* classScopeEnvironment = codeGenerator.AddClassScopeEnvironmentToType(type);
    codeGenerator.PushEnvironment(std::shared_ptr<ScopeSpecificEnvironment>(classScopeEnvironment));
    // TODO: Generate Body
    return nullptr;
}

#pragma endregion

#pragma region Statements

AssemblyCode* OldSyntaxTreeTraverser::GenerateStatement(AbstractStatementNode* statement, bool environmentLock)
{
    if (dynamic_cast<EmptyStatementNode*>(statement) != nullptr)
    {
        return nullptr;  // No code if empty statement
    }

    if (dynamic_cast<BodyNode*>(statement) != nullptr)
    {
        if (!environmentLock)
        {
            // TODO: New environment; where does it know what type of environment
            // to create?
            codeGenerator.PushEnvironment(std::make_shared<ScopeSpecificEnvironment>());
            AssemblyCode* body = GenerateBody(dynamic_cast<BodyNode*>(statement));
            codeGenerator.PopEnvironment();
            return body;
        }

        return GenerateBody(dynamic_cast<BodyNode*>(statement));
    }

    if (dynamic_cast<AbstractKeywordStatementNode*>(statement) != nullptr)
    {
        return GenerateKeywordStatement(dynamic_cast<AbstractKeywordStatementNode*>(statement));
    }

    if (dynamic_cast<AbstractExpressionNode*>(statement) != nullptr)
    {
        return GenerateExpression(dynamic_cast<AbstractExpressionNode*>(statement));
    }

    // TODO: Check for other types of statements

    return nullptr;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateBody(BodyNode* body)
{
    // TODO: New environment; where does it know what type of environment to
    // create?
    return GenerateCodeBlock(body->GetCodeBlock());
}

#pragma region Keyword statements

AssemblyCode* OldSyntaxTreeTraverser::GenerateKeywordStatement(AbstractKeywordStatementNode* statement)
{
    if (dynamic_cast<IfStatementNode*>(statement) != nullptr)
    {
        return GenerateIfStatement(dynamic_cast<IfStatementNode*>(statement));
    }

    if (dynamic_cast<ReturnStatementNode*>(statement) != nullptr)
    {
        return GenerateReturnStatement(dynamic_cast<ReturnStatementNode*>(statement));
    }

    if (dynamic_cast<WhileStatementNode*>(statement) != nullptr)
    {
        return GenerateWhileStatement(dynamic_cast<WhileStatementNode*>(statement));
    }

    if (dynamic_cast<ForStatementNode*>(statement) != nullptr)
    {
        return GenerateForStatement(dynamic_cast<ForStatementNode*>(statement));
    }

    if (dynamic_cast<ContinueStatementNode*>(statement) != nullptr)
    {
        return GenerateContinueStatement(dynamic_cast<ContinueStatementNode*>(statement));
    }

    if (dynamic_cast<BreakStatementNode*>(statement) != nullptr)
    {
        return GenerateBreakStatement(dynamic_cast<BreakStatementNode*>(statement));
    }

    return nullptr;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateIfStatement(IfStatementNode* statement)
{
    // TODO: Get label for final
    return GenerateIfStatement(statement, "final");
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateIfStatement(IfStatementNode* statement, std::string finalLabel)
{
    // TODO: Generate if statement
    return nullptr;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateReturnStatement(ReturnStatementNode* statement)
{
    // TODO: Generate expression code
    AssemblyCode* returnCode = codeGenerator.GenerateReturnStatement(nullptr);
    return returnCode;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateWhileStatement(WhileStatementNode* whileStatement)
{
    // TODO: assembly code and variablegetter for expression
    //  Condition evaluated before InitWhile as InitWhile creates the while scope
    codeGenerator.InitLoopEnvironment();

    AssemblyCode* body = GenerateStatement(whileStatement->statement, true);
    return codeGenerator.GenerateWhile(nullptr, body);
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateForStatement(ForStatementNode* forStatement)
{
    codeGenerator.InitLoopEnvironment();

    AssemblyCode* declaration = GenerateVarDeclaration(forStatement->initialization);
    // TODO: assembly code and variablegetter for condition
    AssemblyCode* increment = GenerateStatement(forStatement->increment, true);
    AssemblyCode* body = GenerateStatement(forStatement->statement, true);

    return codeGenerator.GenerateFor(declaration, nullptr, increment, body);
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateContinueStatement(ContinueStatementNode* statement)
{
    return codeGenerator.GenerateContinueStatement();
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateBreakStatement(BreakStatementNode* statement)
{
    return codeGenerator.GenerateBreakStatement();
}

#pragma endregion

#pragma endregion

#pragma region Expressions

AssemblyCode* OldSyntaxTreeTraverser::GenerateExpression(AbstractExpressionNode* expression)
{
    if (dynamic_cast<AssignmentNode*>(expression) != nullptr)
    {
        return GenerateAssignment(dynamic_cast<AssignmentNode*>(expression));
    }

    if (dynamic_cast<OperatorExpressionNode*>(expression) != nullptr)
    {
        return GenerateBinaryOperation(dynamic_cast<OperatorExpressionNode*>(expression));
    }

    if (dynamic_cast<UnaryExpressionNode*>(expression) != nullptr)
    {
        return GenerateUnaryOperation(dynamic_cast<UnaryExpressionNode*>(expression));
    }

    // If is not assignment, binary or unary, then it is a AbstractValueNode
    return GenerateValue(dynamic_cast<AbstractValueNode*>(expression));
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateAssignment(AssignmentNode* assignmentNode)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (Assignment* assignment : assignmentNode->assignments)
    {
        EAssignOperators assignOperator = assignment->assignOperator;

        if (assignOperator == EAssignOperators::ASSIGN)
        {
            assemblyCode->AddLines(
                GenerateExpression(assignment->L_value));  // Evaluate L_value & store to Temp variables
            assemblyCode->AddLines(
                GenerateExpression(assignmentNode->value));  // Evaluate value & store to Temp variables
            assemblyCode->AddLines(
                codeGenerator.PerformBinaryOperationWithTempVariable(ECodeGeneratorBinaryOperators::ASSIGN));
            continue;
        }

        ECodeGeneratorBinaryOperators codeGeneratorOperator;

        switch (assignOperator)
        {
            case EAssignOperators::ADD_ASSIGN:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::ADD;
            case EAssignOperators::SUB_ASSIGN:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::SUB;
            case EAssignOperators::MUL_ASSIGN:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::MUL;
            case EAssignOperators::DIV_ASSIGN:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::DIV;
            case EAssignOperators::MOD_ASSIGN:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::MOD;
        }

        assemblyCode->AddLines(GenerateExpression(assignment->L_value));    // (for assign) Evaluate L_value &
                                                                            // store to Temp variables
        assemblyCode->AddLines(GenerateExpression(assignment->L_value));    // (for operation ahead of assign) Evaluate
                                                                            // L_value & store to Temp variables
        assemblyCode->AddLines(GenerateExpression(assignmentNode->value));  // Evaluate value & store to Temp variables
        assemblyCode->AddLines(codeGenerator.PerformBinaryOperationWithTempVariable(codeGeneratorOperator));
        assemblyCode->AddLines(
            codeGenerator.PerformBinaryOperationWithTempVariable(ECodeGeneratorBinaryOperators::ASSIGN));
    }

    return assemblyCode;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateBinaryOperation(OperatorExpressionNode* binaryOperationNode)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    assemblyCode->AddLines(GenerateExpression(binaryOperationNode->firstExpression));

    for (OperatorExpressionPair* operatorExpressionPair : *binaryOperationNode->operatorExpressionPairs)
    {
        codeGenerator.ActivateTempVariableEnvironment();
        assemblyCode->AddLines(GenerateExpression(operatorExpressionPair->expression));

        ECodeGeneratorBinaryOperators codeGeneratorOperator;

        switch (operatorExpressionPair->op)
        {
            case EOperators::ADD_OPERATOR:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::ADD;
            case EOperators::SUB_OPERATOR:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::SUB;
            case EOperators::MUL_OPERATOR:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::MUL;
            case EOperators::DIV_OPERATOR:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::DIV;
            case EOperators::MOD_OPERATOR:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::MOD;
        }

        assemblyCode->AddLines(codeGenerator.PerformBinaryOperationWithTempVariable(codeGeneratorOperator));
    }

    return assemblyCode;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateUnaryOperation(UnaryExpressionNode* unaryOperation) { return nullptr; }

AssemblyCode* OldSyntaxTreeTraverser::GenerateValue(AbstractValueNode* value)
{
    if (dynamic_cast<ValueChainNode*>(value) != nullptr)
    {
        return GenerateValueChain(dynamic_cast<ValueChainNode*>(value));
    }

    if (dynamic_cast<StaticValueChainNode*>(value) != nullptr)
    {
        return GenerateStaticValueChain(dynamic_cast<StaticValueChainNode*>(value));
    }

    if (dynamic_cast<AbstractConstValueNode*>(value) != nullptr)
    {
        return GenerateConstValue(dynamic_cast<AbstractConstValueNode*>(value));
    }

    if (dynamic_cast<IDValueNode*>(value) != nullptr)
    {
        return GenerateIDValue(dynamic_cast<IDValueNode*>(value));
    }

    if (dynamic_cast<CallNode*>(value) != nullptr)
    {
        return GenerateCall(dynamic_cast<CallNode*>(value));
    }

    return nullptr;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateValueChain(ValueChainNode* valueChain)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (AbstractExpressionNode* value : valueChain->propertyAccesses)
    {
        assemblyCode->AddLines(GenerateExpression(value));
        codeGenerator.ActivateTempVariableEnvironment();  // Activate environment of temp variable
                                                          // (which is the result of generateExpression)
    }

    codeGenerator.ClearTempVariableEnvironment();  // Clear the temp variable environment as the value chain is done

    return assemblyCode;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateStaticValueChain(StaticValueChainNode* valueChain)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (AbstractExpressionNode* value : valueChain->propertyAccesses)
    {
        assemblyCode->AddLines(GenerateExpression(value));
        // TODO: Activate static environment of type
        codeGenerator.ActivateTempVariableEnvironment();  // Activate environment of temp variable
                                                          // (which is the result of generateExpression)
    }

    // TODO: Temp variable environment should be cleared but only the static part. Probably will need a different
    // TempVariableEnvironment for static and normal ValueChains
    return assemblyCode;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateConstValue(AbstractConstValueNode* value)
{
    if (dynamic_cast<LogicalConstValueNode*>(value) != nullptr)
    {
        codeGenerator.PushLogicalConstToTempVariable(dynamic_cast<LogicalConstValueNode*>(value)->GetValue());
        return nullptr;
    }

    if (dynamic_cast<NumberConstValueNode*>(value) != nullptr)
    {
        codeGenerator.PushNumberConstToTempVariable(dynamic_cast<NumberConstValueNode*>(value)->GetValue());
        return nullptr;
    }

    if (dynamic_cast<StringConstValueNode*>(value) != nullptr)
    {
        codeGenerator.PushStringConstToTempVariable(dynamic_cast<StringConstValueNode*>(value)->GetValue());
        return nullptr;
    }

    return nullptr;
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateIDValue(IDValueNode* value)
{
    codeGenerator.PushVariableToTempVariable(value->GetValue());
    return nullptr;  // No code generated by this
}

AssemblyCode* OldSyntaxTreeTraverser::GenerateCall(CallNode* call)
{
    for (AbstractExpressionNode* argument : call->arguments)
    {
        GenerateExpression(argument);
    }

    return codeGenerator.CallFunction(call->functionName, call->arguments.size());
}

#pragma endregion