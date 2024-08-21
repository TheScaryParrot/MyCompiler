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
                                [](AbstractGenerator* generator) -> bool
                                {
                                    Logger.Log("Entering order queue mode", Logger::DEBUG);

                                    // If is already in OrderQueue Mode, push the current order
                                    // (enterOrderQueue)
                                    if (generator->IsOrderQueueActive())
                                    {
                                        generator->EnqueueInOrderQueue(generator->GetCurrentOrder());
                                    }

                                    generator->IncrementOrderQueueDepth();
                                    return true;
                                },
                                true, false)},
        {"exitOrderQueue", Instruction(
                               [](AbstractGenerator* generator) -> bool
                               {
                                   Logger.Log("Exiting order queue mode", Logger::DEBUG);

                                   generator->DecrementOrderQueueDepth();

                                   // If is still in OrderQueue Mode, push the current orQueue //
                                   // (exitOrderStack) to the order queue
                                   if (generator->IsOrderQueueActive())
                                   {
                                       generator->EnqueueInOrderQueue(generator->GetCurrentOrder());
                                   }

                                   return true;
                               },
                               true, false)},
        {"clearOrderQueue", Instruction(
                                [](AbstractGenerator* generator) -> bool
                                {
                                    generator->DequeueWholeOrderQueue();
                                    return true;
                                },
                                false, false)},
        {"force", Instruction(
                      [](AbstractGenerator* generator) -> bool
                      {
                          generator->SetCurrentPhase(GeneratorPhases::FETCH);
                          generator->ExecuteCurrentPhase();
                          generator->SetCurrentPhase(GeneratorPhases::EXECUTE);
                          generator->ExecuteCurrentPhase();
                          generator->RestartCycle();
                          return false;
                      },
                      true, false)},
        {"orderEnqueue", Instruction(
                             [](AbstractGenerator* generator) -> bool
                             {
                                 generator->SetCurrentPhase(GeneratorPhases::FETCH);
                                 generator->ExecuteCurrentPhase();
                                 generator->EnqueueInOrderQueue(generator->GetCurrentOrder());
                                 generator->RestartCycle();
                                 return false;
                             },
                             true, false)},
        {"orderFrontEnqueue", Instruction(
                                  [](AbstractGenerator* generator) -> bool
                                  {
                                      generator->SetCurrentPhase(GeneratorPhases::FETCH);
                                      generator->ExecuteCurrentPhase();
                                      generator->EnqueueInOrderQueueFront(generator->GetCurrentOrder());
                                      generator->RestartCycle();
                                      return false;
                                  },
                                  // TODO: Make order stack proof without bugs in code
                                  false, false)},
        {"deepFetch", Instruction(
                          [](AbstractGenerator* generator) -> bool
                          {
                              generator->IncrementFetchDepth();
                              generator->SetCurrentPhase(GeneratorPhases::FETCH);
                              generator->ExecuteCurrentPhase();
                              generator->DecrementFetchDepth();
                              generator->PutInFront(generator->GetCurrentOrder());
                              generator->RestartCycle();
                              return false;
                          },
                          false, false)},
        {"literalToIdentifier", Instruction(
                                    [](AbstractGenerator* generator) -> bool
                                    {
                                        Order order = generator->DequeueFromOrderQueue();

                                        if (order.GetType() != Order::LiteralCode)
                                        {
                                            Logger.Log("Expected LiteralCode for literalToIdentifier, got: " +
                                                           order.ToString(),
                                                       Logger::ERROR);
                                            return true;
                                        }

                                        generator->PutInFront(Order(order.GetName(), Order::Identifier));
                                        return true;
                                    },
                                    false, false)},
        {"orderToLiteralCode", Instruction(
                                   [](AbstractGenerator* generator) -> bool
                                   {
                                       Order order = generator->DequeueFromOrderQueue();
                                       generator->PutInFront(Order(order.GetName(), Order::LiteralCode));
                                       return true;
                                   },
                                   false, false)},
        {"assign", Instruction(
                       [](AbstractGenerator* generator) -> bool
                       {
                           OrderQueue* queue = generator->DequeueWholeOrderQueue();

                           Order identifierOrder = queue->Dequeue();

                           if (identifierOrder.GetType() != Order::Identifier)
                           {
                               Logger.Log("Expected Identifier for assign on top of OrderQueue, got: " +
                                              identifierOrder.ToString(),
                                          Logger::ERROR);
                               return true;
                           }

                           std::string identifierName = identifierOrder.GetName();
                           Identifier* identifier = new Identifier(queue);
                           IdentifierHandler.AddIdentifier(identifierName, identifier);
                           return true;
                       },
                       false, false)},
        {"assignToOne", Instruction(
                            [](AbstractGenerator* generator) -> bool
                            {
                                Order identifierOrder = generator->DequeueFromOrderQueue();

                                if (identifierOrder.GetType() != Order::Identifier)
                                {
                                    Logger.Log("Expected Identifier for assign on top of OrderQueue, got: " +
                                                   identifierOrder.ToString(),
                                               Logger::ERROR);
                                    return true;
                                }

                                std::string identifierName = identifierOrder.GetName();
                                OrderQueue* queue = new OrderQueue(generator->DequeueFromOrderQueue());
                                Identifier* identifier = new Identifier(queue);
                                IdentifierHandler.AddIdentifier(identifierName, identifier);
                                return true;
                            },
                            false, false)},
        {"pushEnv", Instruction(
                        [](AbstractGenerator* generator) -> bool
                        {
                            IdentifierHandler.PushEnvironment();
                            return true;
                        },
                        false, false)},
        {"popEnv", Instruction(
                       [](AbstractGenerator* generator) -> bool
                       {
                           IdentifierHandler.PopEnvironment();
                           return true;
                       },
                       false, false)},
        {"getIntVar", Instruction(
                          [](AbstractGenerator* generator) -> bool
                          {
                              Order order = generator->DequeueFromOrderQueue();

                              if (order.GetType() != Order::LiteralCode)
                              {
                                  Logger.Log(
                                      "Tried getIntVar but order from OrderQueue is not "
                                      "direct code",
                                      Logger::ERROR);
                                  return true;
                              }

                              std::string generatorVarName = order.GetName();
                              int value = generator->GetIntGeneratorVar(generatorVarName);
                              generator->PutInFront(Order(std::to_string(value), Order::LiteralCode));
                              return true;
                          },
                          false, false)},
        {"setIntVar", Instruction(
                          [](AbstractGenerator* generator) -> bool
                          {
                              Order nameOrder = generator->DequeueFromOrderQueue();

                              if (nameOrder.GetType() != Order::LiteralCode)
                              {
                                  Logger.Log(
                                      "Tried setIntVar but first order (name) from OrderQueue is not "
                                      "direct code",
                                      Logger::ERROR);
                                  return true;
                              }

                              Order valueOrder = generator->DequeueFromOrderQueue();
                              if (valueOrder.GetType() != Order::LiteralCode)
                              {
                                  Logger.Log(
                                      "Tried setIntVar but second order (value) from OrderQueue is not "
                                      "direct code",
                                      Logger::ERROR);
                                  return true;
                              }

                              std::string generatorVarName = nameOrder.GetName();
                              int value = std::stoi(valueOrder.GetName());
                              generator->SetIntGeneratorVar(generatorVarName, value);
                              return true;
                          },
                          false, false)},
        {"changeIntVar", Instruction(
                             [](AbstractGenerator* generator) -> bool
                             {
                                 Order nameOrder = generator->DequeueFromOrderQueue();
                                 if (nameOrder.GetType() != Order::LiteralCode)
                                 {
                                     Logger.Log(
                                         "Tried changeIntVar but first order (name) from "
                                         "OrderQueue is not direct code",
                                         Logger::ERROR);
                                     return true;
                                 }

                                 Order changeOrder = generator->DequeueFromOrderQueue();
                                 if (changeOrder.GetType() != Order::LiteralCode)
                                 {
                                     Logger.Log(
                                         "Tried changeIntVar but second order (change) from "
                                         "OrderQueue is not direct code",
                                         Logger::ERROR);
                                     return true;
                                 }

                                 std::string generatorVarName = nameOrder.GetName();
                                 int change = std::stoi(changeOrder.GetName());

                                 int value = generator->GetIntGeneratorVar(generatorVarName);
                                 value += change;

                                 generator->SetIntGeneratorVar(generatorVarName, value);
                                 return true;
                             },
                             false, false)},
        {"getStringVar", Instruction(
                             [](AbstractGenerator* generator) -> bool
                             {
                                 Order nameOrder = generator->DequeueFromOrderQueue();
                                 if (nameOrder.GetType() != Order::LiteralCode)
                                 {
                                     Logger.Log(
                                         "Tried getStringVar but order from OrderQueue is not "
                                         "direct code",
                                         Logger::ERROR);
                                     return true;
                                 }

                                 std::string generatorVarName = nameOrder.GetName();
                                 std::string value = generator->GetStringGeneratorVar(generatorVarName);
                                 generator->PutInFront(Order(value, Order::LiteralCode));
                                 return true;
                             },
                             false, false)},
        {"setStringVar", Instruction(
                             [](AbstractGenerator* generator) -> bool
                             {
                                 Order nameOrder = generator->DequeueFromOrderQueue();
                                 if (nameOrder.GetType() != Order::LiteralCode)
                                 {
                                     Logger.Log(
                                         "Tried setStringGeneratorVar but first order (name) from "
                                         "OrderQueue is not direct code",
                                         Logger::ERROR);
                                     return true;
                                 }

                                 Order valueOrder = generator->DequeueFromOrderQueue();
                                 if (valueOrder.GetType() != Order::LiteralCode)
                                 {
                                     Logger.Log(
                                         "Tried setStringGeneratorVar but second order (value) from "
                                         "OrderQueue is not direct code",
                                         Logger::ERROR);
                                     return true;
                                 }

                                 std::string generatorVarName = nameOrder.GetName();
                                 std::string value = valueOrder.GetName();
                                 generator->SetStringGeneratorVar(generatorVarName, value);
                                 return true;
                             },
                             false, false)},
        {"makeOrderQueueProof",
         Instruction(

             [](AbstractGenerator* generator) -> bool
             {
                 Order order = generator->DequeueFromOrderQueue();
                 if (order.GetType() != Order::Identifier)
                 {
                     Logger.Log("Expected Identifier for makeOrderQueueProof, got: " + order.ToString(), Logger::ERROR);
                     return true;
                 }

                 Identifier* identifier = IdentifierHandler.GetIdentifier(order.GetName());

                 if (identifier == nullptr)
                 {
                     Logger.Log("Identifier not found for makeOrderQueueProof: " + order.GetName(), Logger::ERROR);
                     return true;
                 }

                 identifier->SetOrderQueueProof(true);
                 return true;
             },
             false, false)},
        {"makeCommentProof",
         Instruction(
             [](AbstractGenerator* generator) -> bool
             {
                 Order order = generator->DequeueFromOrderQueue();
                 if (order.GetType() != Order::Identifier)
                 {
                     Logger.Log("Expected Identifier for makeCommentProof, got: " + order.ToString(), Logger::ERROR);
                     return true;
                 }

                 Identifier* identifier = IdentifierHandler.GetIdentifier(order.GetName());

                 if (identifier == nullptr)
                 {
                     Logger.Log("Identifier not found for makeCommentProof: " + order.GetName(), Logger::ERROR);
                     return true;
                 }

                 identifier->SetCommentProof(true);
                 return true;
             },
             false, false)},
        {"enterComment", Instruction(
                             [](AbstractGenerator* generator) -> bool
                             {
                                 generator->EnterComment();
                                 return true;
                             },
                             true, false)},
        {"exitComment", Instruction(
                            [](AbstractGenerator* generator) -> bool
                            {
                                generator->ExitComment();
                                return true;
                            },
                            true, true)},
        {"debug", Instruction(
                      [](AbstractGenerator* generator) -> bool
                      {
                          Logger.Log("Debug Print", Logger::DEBUG);
                          return true;
                      },
                      false, false)},
        {"debugIdentifierDefinition",
         Instruction(

             [](AbstractGenerator* generator) -> bool
             {
                 Order order = generator->DequeueFromOrderQueue();

                 if (order.GetType() != Order::Identifier)
                 {
                     Logger.Log(
                         "Expected Identifier for "
                         "debugIdentifierDefinition, got: " +
                             order.ToString(),
                         Logger::ERROR);

                     return true;
                 }

                 Identifier* identifier = IdentifierHandler.GetIdentifier(order.GetName());

                 if (identifier == nullptr)
                 {
                     Logger.Log("Identifier not found for debugIdentifierDefinition: " + order.GetName(),
                                Logger::ERROR);
                     return true;
                 }

                 Logger.Log("Identifier: " + order.GetName() + " Definition: \n" + identifier->GetQueue()->ToString(),
                            Logger::DEBUG);

                 return true;
             },
             false, false)},
        {"debugOrderQueue", Instruction(
                                [](AbstractGenerator* generator) -> bool
                                {
                                    OrderQueue orderQueue = generator->GetOrderQueueCopy();
                                    Logger.Log("Current Order Queue: \n" + orderQueue.ToString(), Logger::DEBUG);
                                    return true;
                                },
                                false, false)},
        {"activateDebug", Instruction(
                              [](AbstractGenerator* generator) -> bool
                              {
                                  Logger.SetDebug(true);
                                  return true;
                              },
                              false, false)},
        {"deactivateDebug", Instruction(
                                [](AbstractGenerator* generator) -> bool
                                {
                                    Logger.SetDebug(false);
                                    return true;
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