#pragma once

#include <map>
#include <string>

#include "../identifiers/IdentifierHandler.cpp"
#include "Instruction.cpp"

static class InstructionHandler
{
   private:
    std::map<std::string, Instruction> instructions = {
        {"enterOrderQueue", Instruction(
                                [](AbstractGenerator* generator)
                                {
                                    Logger.Log("Entering order queue mode", Logger::DEBUG);

                                    // If is already in OrderQueue Mode, push the current order
                                    // (enterOrderQueue)
                                    if (generator->IsOrderQueueActive())
                                    {
                                        generator->EnqueueInOrderQueue(generator->GetCurrentOrder());
                                    }

                                    generator->IncrementOrderQueueDepth();
                                    generator->IncrementPhase();
                                },
                                true, false)},
        {"exitOrderQueue", Instruction(
                               [](AbstractGenerator* generator)
                               {
                                   Logger.Log("Exiting order queue mode", Logger::DEBUG);

                                   generator->DecrementOrderQueueDepth();

                                   // If is still in OrderQueue Mode, push the current orQueue //
                                   // (exitOrderStack) to the order queue
                                   if (generator->IsOrderQueueActive())
                                   {
                                       generator->EnqueueInOrderQueue(generator->GetCurrentOrder());
                                   }

                                   generator->IncrementPhase();
                               },
                               true, false)},
        {"clearOrderQueue", Instruction(
                                [](AbstractGenerator* generator)
                                {
                                    generator->DequeueWholeOrderQueue();
                                    generator->IncrementPhase();
                                },
                                false, false)},
        {"force", Instruction(
                      [](AbstractGenerator* generator)
                      {
                          generator->SetCurrentPhase(GeneratorPhases::FETCH);
                          generator->ExecuteCurrentPhase();
                          generator->SetCurrentPhase(GeneratorPhases::EXECUTE);
                          generator->ExecuteCurrentPhase();
                          generator->RestartCycle();
                      },
                      true, false)},
        {"orderEnqueue", Instruction(
                             [](AbstractGenerator* generator)
                             {
                                 generator->SetCurrentPhase(GeneratorPhases::FETCH);
                                 generator->ExecuteCurrentPhase();
                                 generator->EnqueueInOrderQueue(generator->GetCurrentOrder());
                                 generator->RestartCycle();
                             },
                             true, false)},
        {"orderFrontEnqueue", Instruction(
                                  [](AbstractGenerator* generator)
                                  {
                                      generator->SetCurrentPhase(GeneratorPhases::FETCH);
                                      generator->ExecuteCurrentPhase();
                                      generator->EnqueueInOrderQueueFront(generator->GetCurrentOrder());
                                      generator->RestartCycle();
                                  },
                                  // TODO: Make order stack proof without bugs in code
                                  false, false)},
        {"deepFetch", Instruction(
                          [](AbstractGenerator* generator)
                          {
                              generator->IncrementFetchDepth();
                              generator->SetCurrentPhase(GeneratorPhases::FETCH);
                              generator->ExecuteCurrentPhase();
                              generator->DecrementFetchDepth();
                              generator->PutInFront(generator->GetCurrentOrder());
                              generator->RestartCycle();
                          },
                          false, false)},
        {"literalToIdentifier", Instruction(
                                    [](AbstractGenerator* generator)
                                    {
                                        Order order = generator->DequeueFromOrderQueue();

                                        if (order.GetType() != Order::LiteralCode)
                                        {
                                            Logger.Log("Expected LiteralCode for literalToIdentifier, got: " +
                                                           order.ToString(),
                                                       Logger::ERROR);
                                            generator->IncrementPhase();
                                            return;
                                        }

                                        generator->PutInFront(Order(order.GetName(), Order::Identifier));
                                        generator->IncrementPhase();
                                    },
                                    false, false)},
        {"orderToLiteralCode", Instruction(
                                   [](AbstractGenerator* generator)
                                   {
                                       Order order = generator->DequeueFromOrderQueue();
                                       generator->PutInFront(Order(order.GetName(), Order::LiteralCode));
                                       generator->IncrementPhase();
                                   },
                                   false, false)},
        {"assign", Instruction(
                       [](AbstractGenerator* generator)
                       {
                           OrderQueue* queue = generator->DequeueWholeOrderQueue();

                           Order identifierOrder = queue->Dequeue();

                           if (identifierOrder.GetType() != Order::Identifier)
                           {
                               Logger.Log("Expected Identifier for assign on top of OrderQueue, got: " +
                                              identifierOrder.ToString(),
                                          Logger::ERROR);
                               return;
                           }

                           std::string identifierName = identifierOrder.GetName();
                           Identifier* identifier = new Identifier(queue);
                           IdentifierHandler.AddIdentifier(identifierName, identifier);
                           generator->IncrementPhase();
                       },
                       false, false)},
        {"assignToOne", Instruction(
                            [](AbstractGenerator* generator)
                            {
                                Order identifierOrder = generator->DequeueFromOrderQueue();

                                if (identifierOrder.GetType() != Order::Identifier)
                                {
                                    Logger.Log("Expected Identifier for assign on top of OrderQueue, got: " +
                                                   identifierOrder.ToString(),
                                               Logger::ERROR);
                                    return;
                                }

                                std::string identifierName = identifierOrder.GetName();
                                OrderQueue* queue = new OrderQueue(generator->DequeueFromOrderQueue());
                                Identifier* identifier = new Identifier(queue);
                                IdentifierHandler.AddIdentifier(identifierName, identifier);
                                generator->IncrementPhase();
                            },
                            false, false)},
        {"pushEnv", Instruction(
                        [](AbstractGenerator* generator)
                        {
                            IdentifierHandler.PushEnvironment();
                            generator->IncrementPhase();
                        },
                        false, false)},
        {"popEnv", Instruction(
                       [](AbstractGenerator* generator)
                       {
                           IdentifierHandler.PopEnvironment();
                           generator->IncrementPhase();
                       },
                       false, false)},
        {"getIntVar", Instruction(
                          [](AbstractGenerator* generator)
                          {
                              Order order = generator->DequeueFromOrderQueue();

                              if (order.GetType() != Order::LiteralCode)
                              {
                                  Logger.Log(
                                      "Tried getIntVar but order from OrderQueue is not "
                                      "direct code",
                                      Logger::ERROR);
                                  generator->IncrementPhase();
                                  return;
                              }

                              std::string generatorVarName = order.GetName();
                              int value = generator->GetIntGeneratorVar(generatorVarName);
                              generator->PutInFront(Order(std::to_string(value), Order::LiteralCode));
                              generator->IncrementPhase();
                          },
                          false, false)},
        {"setIntVar", Instruction(
                          [](AbstractGenerator* generator)
                          {
                              Order nameOrder = generator->DequeueFromOrderQueue();

                              if (nameOrder.GetType() != Order::LiteralCode)
                              {
                                  Logger.Log(
                                      "Tried setIntVar but first order (name) from OrderQueue is not "
                                      "direct code",
                                      Logger::ERROR);
                                  generator->IncrementPhase();
                                  return;
                              }

                              Order valueOrder = generator->DequeueFromOrderQueue();
                              if (valueOrder.GetType() != Order::LiteralCode)
                              {
                                  Logger.Log(
                                      "Tried setIntVar but second order (value) from OrderQueue is not "
                                      "direct code",
                                      Logger::ERROR);
                                  generator->IncrementPhase();
                                  return;
                              }

                              std::string generatorVarName = nameOrder.GetName();
                              int value = std::stoi(valueOrder.GetName());
                              generator->SetIntGeneratorVar(generatorVarName, value);
                              generator->IncrementPhase();
                          },
                          false, false)},
        {"changeIntVar", Instruction(
                             [](AbstractGenerator* generator)
                             {
                                 Order nameOrder = generator->DequeueFromOrderQueue();
                                 if (nameOrder.GetType() != Order::LiteralCode)
                                 {
                                     Logger.Log(
                                         "Tried changeIntVar but first order (name) from "
                                         "OrderQueue is not direct code",
                                         Logger::ERROR);
                                     generator->IncrementPhase();
                                     return;
                                 }

                                 Order changeOrder = generator->DequeueFromOrderQueue();
                                 if (changeOrder.GetType() != Order::LiteralCode)
                                 {
                                     Logger.Log(
                                         "Tried changeIntVar but second order (change) from "
                                         "OrderQueue is not direct code",
                                         Logger::ERROR);
                                     generator->IncrementPhase();
                                     return;
                                 }

                                 std::string generatorVarName = nameOrder.GetName();
                                 int change = std::stoi(changeOrder.GetName());

                                 int value = generator->GetIntGeneratorVar(generatorVarName);
                                 value += change;

                                 generator->SetIntGeneratorVar(generatorVarName, value);
                                 generator->IncrementPhase();
                             },
                             false, false)},
        {"getStringVar", Instruction(
                             [](AbstractGenerator* generator)
                             {
                                 Order nameOrder = generator->DequeueFromOrderQueue();
                                 if (nameOrder.GetType() != Order::LiteralCode)
                                 {
                                     Logger.Log(
                                         "Tried getStringVar but order from OrderQueue is not "
                                         "direct code",
                                         Logger::ERROR);
                                     generator->IncrementPhase();
                                     return;
                                 }

                                 std::string generatorVarName = nameOrder.GetName();
                                 std::string value = generator->GetStringGeneratorVar(generatorVarName);
                                 generator->PutInFront(Order(value, Order::LiteralCode));
                                 generator->IncrementPhase();
                             },
                             false, false)},
        {"setStringVar", Instruction(
                             [](AbstractGenerator* generator)
                             {
                                 Order nameOrder = generator->DequeueFromOrderQueue();
                                 if (nameOrder.GetType() != Order::LiteralCode)
                                 {
                                     Logger.Log(
                                         "Tried setStringGeneratorVar but first order (name) from "
                                         "OrderQueue is not direct code",
                                         Logger::ERROR);
                                     generator->IncrementPhase();
                                     return;
                                 }

                                 Order valueOrder = generator->DequeueFromOrderQueue();
                                 if (valueOrder.GetType() != Order::LiteralCode)
                                 {
                                     Logger.Log(
                                         "Tried setStringGeneratorVar but second order (value) from "
                                         "OrderQueue is not direct code",
                                         Logger::ERROR);
                                     generator->IncrementPhase();
                                     return;
                                 }

                                 std::string generatorVarName = nameOrder.GetName();
                                 std::string value = valueOrder.GetName();
                                 generator->SetStringGeneratorVar(generatorVarName, value);
                                 generator->IncrementPhase();
                             },
                             false, false)},
        {"makeOrderQueueProof",
         Instruction(

             [](AbstractGenerator* generator)
             {
                 Order order = generator->DequeueFromOrderQueue();
                 if (order.GetType() != Order::Identifier)
                 {
                     Logger.Log("Expected Identifier for makeOrderQueueProof, got: " + order.ToString(), Logger::ERROR);
                     return;
                 }

                 Identifier* identifier = IdentifierHandler.GetIdentifier(order.GetName());

                 if (identifier == nullptr)
                 {
                     Logger.Log("Identifier not found for makeOrderQueueProof: " + order.GetName(), Logger::ERROR);
                     return;
                 }

                 identifier->SetOrderQueueProof(true);
                 generator->IncrementPhase();
             },
             false, false)},
        {"makeCommentProof",
         Instruction(
             [](AbstractGenerator* generator)
             {
                 Order order = generator->DequeueFromOrderQueue();
                 if (order.GetType() != Order::Identifier)
                 {
                     Logger.Log("Expected Identifier for makeCommentProof, got: " + order.ToString(), Logger::ERROR);
                     return;
                 }

                 Identifier* identifier = IdentifierHandler.GetIdentifier(order.GetName());

                 if (identifier == nullptr)
                 {
                     Logger.Log("Identifier not found for makeCommentProof: " + order.GetName(), Logger::ERROR);
                     return;
                 }

                 identifier->SetCommentProof(true);
                 generator->IncrementPhase();
             },
             false, false)},
        {"enterComment", Instruction(
                             [](AbstractGenerator* generator)
                             {
                                 generator->EnterComment();
                                 generator->IncrementPhase();
                             },
                             true, false)},
        {"exitComment", Instruction(
                            [](AbstractGenerator* generator)
                            {
                                generator->ExitComment();
                                generator->IncrementPhase();
                            },
                            true, true)},
        {"debug", Instruction(
                      [](AbstractGenerator* generator)
                      {
                          Logger.Log("Debug Print", Logger::DEBUG);
                          generator->IncrementPhase();
                      },
                      false, false)},
        {"debugIdentifierDefinition",
         Instruction(

             [](AbstractGenerator* generator)
             {
                 Order order = generator->DequeueFromOrderQueue();

                 if (order.GetType() != Order::Identifier)
                 {
                     Logger.Log(
                         "Expected Identifier for "
                         "debugIdentifierDefinition, got: " +
                             order.ToString(),
                         Logger::ERROR);

                     generator->IncrementPhase();
                     return;
                 }

                 Identifier* identifier = IdentifierHandler.GetIdentifier(order.GetName());

                 if (identifier == nullptr)
                 {
                     Logger.Log("Identifier not found for debugIdentifierDefinition: " + order.GetName(),
                                Logger::ERROR);
                     generator->IncrementPhase();
                     return;
                 }

                 Logger.Log("Identifier: " + order.GetName() + " Definition: \n" + identifier->GetQueue()->ToString(),
                            Logger::DEBUG);

                 generator->IncrementPhase();
             },
             false, false)},
        {"debugOrderQueue", Instruction(
                                [](AbstractGenerator* generator)
                                {
                                    OrderQueue orderQueue = generator->GetOrderQueueCopy();
                                    Logger.Log("Current Order Queue: \n" + orderQueue.ToString(), Logger::DEBUG);
                                    generator->IncrementPhase();
                                },
                                false, false)},
        {"activateDebug", Instruction(
                              [](AbstractGenerator* generator)
                              {
                                  Logger.SetDebug(true);
                                  generator->IncrementPhase();
                              },
                              false, false)},
        {"deactivateDebug", Instruction(
                                [](AbstractGenerator* generator)
                                {
                                    Logger.SetDebug(false);
                                    generator->IncrementPhase();
                                },
                                false, false)}};

   public:
    Instruction* GetInstruction(std::string name)
    {
        auto instructionPair = this->instructions.find(name);

        if (instructionPair == this->instructions.end()) return nullptr;

        return &instructionPair->second;
    }
} InstructionHandler;