#pragma once

#include "../utils/Logger.cpp"
#include "Environment.cpp"

class InstructionEnvironment : private Environment
{
   public:
    InstructionEnvironment();

    void ExecuteInstruction(std::string name, ICodeGenerator* codeGenerator);
    Callable* GetInstruction(std::string name);
};

InstructionEnvironment::InstructionEnvironment()
{
    this->AddCallable("enterComment", new Callable([](ICodeGenerator* generator)
                                                   { generator->PushMode(ICodeGenerator::EModes::Comment); }));

    this->AddCallable("exitComment", new Callable(
                                         [](ICodeGenerator* generator)
                                         {
                                             if (!generator->IsInMode(ICodeGenerator::EModes::Comment))
                                             {
                                                 Logger.Log("Trying to exit comment mode while not in comment mode",
                                                            Logger::ERROR);
                                                 return;
                                             }
                                             generator->PopMode();
                                         }));

    this->AddCallable("enterCodeStack", new Callable(
                                            [](ICodeGenerator* generator)
                                            {
                                                Logger.Log("Entering code stack mode", Logger::DEBUG);

                                                // If is already in CodeStack Mode, push the current order
                                                // (enterCodeStack)
                                                if (generator->IsInMode(ICodeGenerator::EModes::CodeStack))
                                                {
                                                    generator->PushToOrderStack(generator->GetCurrentOrder());
                                                }

                                                generator->IncrementCodeStackDepth();
                                            }));

    this->AddCallable("exitCodeStack", new Callable(
                                           [](ICodeGenerator* generator)
                                           {
                                               Logger.Log("Exiting code stack mode", Logger::DEBUG);

                                               generator->DecrementCodeStackDepth();

                                               // If is still in CodeStack Mode, push the current order (exitCodeStack)
                                               // to the code stack
                                               if (generator->IsInMode(ICodeGenerator::EModes::CodeStack))
                                               {
                                                   generator->PushToOrderStack(generator->GetCurrentOrder());
                                               }
                                           }));

    this->AddCallable(
        "pushNextOrderToCodeStack",
        new Callable([](ICodeGenerator* generator) { generator->PushToOrderStack(generator->GetNextOrder()); }));

    this->AddCallable("enterTypeStack", new Callable(
                                            [](ICodeGenerator* generator)
                                            {
                                                Logger.Log("Entering type stack mode", Logger::DEBUG);
                                                generator->NewTypeStack();
                                                generator->PushMode(ICodeGenerator::EModes::TypeStack);
                                            }));

    this->AddCallable("exitTypeStack", new Callable(
                                           [](ICodeGenerator* generator)
                                           {
                                               if (!generator->IsInMode(ICodeGenerator::EModes::TypeStack))
                                               {
                                                   Logger.Log(
                                                       "Trying to exit type stack mode while not in type stack mode",
                                                       Logger::ERROR);
                                                   return;
                                               }

                                               Logger.Log("Exiting type stack mode", Logger::DEBUG);

                                               generator->PopMode();
                                           }));

    this->AddCallable(
        "assignNextIdentifier",
        new Callable(
            [](ICodeGenerator* generator)
            {
                Order nextOrder = generator->GetNextOrder();

                if (nextOrder.GetType() != Order::EOrderTypes::Identifier)
                {
                    Logger.Log("Tried assigning next identifier but next order is not identifier . Skipping assign",
                               Logger::ERROR);

                    return;
                }

                Logger.Log("Assigning next order '" + nextOrder.ToString() + "'", Logger::DEBUG);

                std::vector<Type*> popTypes = generator->PopTypeStack();
                std::vector<Type*> pushTypes = generator->PopTypeStack();
                OrderQueue code = generator->PopFromCodeStack();

                Identifier* callable = new Identifier(pushTypes, popTypes, code);

                generator->AddIdentifier(nextOrder.GetName(), callable);
            }));

    this->AddCallable("makeNextOrderCodeStackProof",
                      new Callable(
                          [](ICodeGenerator* generator)
                          {
                              Order nextOrder = generator->GetNextOrder();

                              Logger.Log("Making next identifier code stack proof '" + nextOrder.ToString() + "'",
                                         Logger::DEBUG);

                              Callable* callable = generator->GetCallable(nextOrder);

                              callable->SetCodeStackProof(true);
                          }));

    this->AddCallable("makeNextOrderCommentProof",
                      new Callable(
                          [](ICodeGenerator* generator)
                          {
                              Order nextOrder = generator->GetNextOrder();

                              Logger.Log("Making next identifier comment proof '" + nextOrder.ToString() + "'",
                                         Logger::DEBUG);

                              Callable* callable = generator->GetCallable(nextOrder);

                              callable->SetCommentProof(true);
                          }));

    this->AddCallable("debug",
                      new Callable([](ICodeGenerator* generator) { Logger.Log("DEBUG PRINT", Logger::INFO); }));

    this->AddCallable("debugStatus",
                      new Callable(
                          [](ICodeGenerator* generator)
                          {
                              Logger.Log("---DEBUG STATUS", Logger::DEBUG);
                              Logger.Log("---Current order: " + generator->GetCurrentOrder().ToString(), Logger::DEBUG);
                              Logger.Log("---Next order: " + generator->GetNextOrder().ToString(), Logger::DEBUG);
                              Logger.Log("---Current mode: " + std::to_string(generator->GetCurrentMode()),
                                         Logger::DEBUG);
                          }));

    this->AddCallable("activateDebugMode", new Callable([](ICodeGenerator* generator) { Logger.SetDebug(true); }));
    this->AddCallable("deactivateDebugMode", new Callable([](ICodeGenerator* generator) { Logger.SetDebug(false); }));
};

void InstructionEnvironment::ExecuteInstruction(std::string name, ICodeGenerator* codeGenerator)
{
    this->ExecuteCallable(name, codeGenerator);
}

Callable* InstructionEnvironment::GetInstruction(std::string name) { return this->GetCallable(name); }