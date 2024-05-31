#pragma once

#include <string>

#include "AssemblyInstruction.cpp"

static class AssemblyInstructions
{
public:
    static const AssemblyInstruction MOV;
    static const AssemblyInstruction ADD;
    static const AssemblyInstruction SUB;
    static const AssemblyInstruction MUL;
    static const AssemblyInstruction DIV;

    static const AssemblyInstruction CALL;
    static const AssemblyInstruction RET;

    static const AssemblyInstruction JMP;

}AssemblyInstructions;

const AssemblyInstruction AssemblyInstructions::MOV = AssemblyInstruction("MOV");
const AssemblyInstruction AssemblyInstructions::ADD = AssemblyInstruction("ADD");
const AssemblyInstruction AssemblyInstructions::SUB = AssemblyInstruction("SUB");
const AssemblyInstruction AssemblyInstructions::MUL = AssemblyInstruction("MUL");
const AssemblyInstruction AssemblyInstructions::DIV = AssemblyInstruction("DIV");

const AssemblyInstruction AssemblyInstructions::CALL = AssemblyInstruction("CALL");
const AssemblyInstruction AssemblyInstructions::RET = AssemblyInstruction("RET");

const AssemblyInstruction AssemblyInstructions::JMP = AssemblyInstruction("JMP");