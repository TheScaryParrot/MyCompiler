#pragma once

#include "../utils/Logger.cpp"
#include "Environment.cpp"
#include "Identifier.cpp"

class InstructionEnvironment : private Environment
{
   public:
    InstructionEnvironment() {
        /*
        this->AddCallable("enterComment", new ICallable([](ICodeGenerator* generator)
                                                        { generator->PushMode(ICodeGenerator::EModes::COMMENT); }));

        this->AddCallable("exitComment", new ICallable(
                                             [](ICodeGenerator* generator)
                                             {
                                                 if (!generator->IsInMode(ICodeGenerator::EModes::COMMENT))
                                                 {
                                                     Logger.Log("Trying to exit comment mode while not in comment mode",
                                                                Logger::ERROR);
                                                     return;
                                                 }
                                                 generator->PopMode();
                                             }));

        this->AddCallable("enterOrderQueue", new Callable(
                                                 [](ICodeGenerator* generator)
                                                 {
                                                     Logger.Log("Entering order queue mode", Logger::DEBUG);

                                                     // If is already in OrderQueue Mode, push the current order
                                                     // (enterOrderQueue)
                                                     if (generator->IsInMode(ICodeGenerator::EModes::ORDER_QUEUE))
                                                     {
                                                         generator->EnqueueInOrderQueue(generator->GetCurrentOrder());
                                                     }

                                                     generator->IncrementOrderQueueDepth();
                                                 }));

        this->AddCallable("exitOrderQueue", new Callable(
                                                [](ICodeGenerator* generator)
                                                {
                                                    Logger.Log("Exiting order queue mode", Logger::DEBUG);

                                                    generator->DecrementOrderQueueDepth();

                                                    // If is still in OrderQueue Mode, push the current orQueue //
                                                    // (exitOrderStack) to the order queue
                                                    if (generator->IsInMode(ICodeGenerator::EModes::ORDER_QUEUE))
                                                    {
                                                        generator->EnqueueInOrderQueue(generator->GetCurrentOrder());
                                                    }
                                                }));

        this->AddCallable("pushNewOrderQueue",
                          new Callable([](ICodeGenerator* generator) { generator->PushNewOrderQueue(); }));

        this->AddCallable(
            "pushNextOrderToOrderQueue",
            new Callable([](ICodeGenerator* generator) { generator->EnqueueInOrderQueue(generator->GetNextOrder()); }));

        this->AddCallable("clearOrderQueue",
                          new Callable([](ICodeGenerator* generator) { generator->ClearOrderQueue(); }));

        this->AddCallable("putInFrontFromOrderQueue", new Callable(
                                                          [](ICodeGenerator* generator)
                                                          {
                                                              Logger.Log("Executing from order queue", Logger::DEBUG);
                                                              generator->PutInFrontFromOrderQueue();
                                                          }));

        this->AddCallable("enterTypeStack", new Callable(
                                                [](ICodeGenerator* generator)
                                                {
                                                    Logger.Log(
                                                        "Type stack is depricated: #enterTypeStack should not be used",
                                                        Logger::WARNING);
                                                    // generator->NewTypeStack();
                                                    // generator->PushMode(ICodeGenerator::EModes::TYPE_STACK);
                                                }));

        this->AddCallable("exitTypeStack", new Callable(
                                               [](ICodeGenerator* generator)
                                               {
                                                   /*if (!generator->IsInMode(ICodeGenerator::EModes::TYPE_STACK))
                                                   {
                                                       Logger.Log(
                                                           "Trying to exit type stack mode while not in type stack
                                                   mode", Logger::ERROR); return;
                                                   }*/

        /*Logger.Log(
                                                       "Type stack is depricated: #exitTypeStack should not be used",
                                                       Logger::DEBUG);

                                                   // generator->PopMode();
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

                    OrderQueue* code = generator->PopOrderQueue();

                    Identifier* callable = new Identifier(*code);

                    generator->AddIdentifier(nextOrder.GetName(), callable);
                }));

        this->AddCallable(
            "assignNextIdentifierToOneOrder",
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

                    OrderQueue code = OrderQueue();
                    code.Enqueue(generator->DequeueFromOrderQueue());

                    Identifier* callable = new Identifier(code);

                    generator->AddIdentifier(nextOrder.GetName(), callable);
                }));

        this->AddCallable("makeNextOrderOrderQueueProof",
                          new Callable(
                              [](ICodeGenerator* generator)
                              {
                                  Order nextOrder = generator->GetNextOrder();

                                  Logger.Log("Making next identifier order queue proof '" + nextOrder.ToString() + "'",
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

        this->AddCallable(
            "debugStatus",
            new Callable(
                [](ICodeGenerator* generator)
                {
                    Logger.Log("---DEBUG STATUS", Logger::DEBUG);
                    Logger.Log("---Current order: " + generator->GetCurrentOrder().ToString(), Logger::DEBUG);
                    Logger.Log("---Next order: " + generator->GetNextOrder().ToString(), Logger::DEBUG);
                    Logger.Log("---Current mode: " + std::to_string(generator->GetCurrentMode()), Logger::DEBUG);
                }));

        this->AddCallable("activateDebugMode", new Callable([](ICodeGenerator* generator) { Logger.SetDebug(true); }));
        this->AddCallable("deactivateDebugMode",
                          new Callable([](ICodeGenerator* generator) { Logger.SetDebug(false); }));

                          */
    };

    ICallable* GetInstruction(std::string name) { return this->GetCallable(name); }
};