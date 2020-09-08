#pragma once
#include <vector>
#include <string>
#include "stack.h"
class Instruction
{
    std::vector<std::string> m_instructions;
    int checkIf(int whichInstr, Stack &stack);
public:
    void add(std::string instruction);
    void run();
};
