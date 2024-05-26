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

}AssemblyInstructions;

const AssemblyInstruction AssemblyInstructions::MOV = AssemblyInstruction("MOV");
const AssemblyInstruction AssemblyInstructions::ADD = AssemblyInstruction("ADD");
const AssemblyInstruction AssemblyInstructions::SUB = AssemblyInstruction("SUB");
const AssemblyInstruction AssemblyInstructions::MUL = AssemblyInstruction("MUL");
const AssemblyInstruction AssemblyInstructions::DIV = AssemblyInstruction("DIV");