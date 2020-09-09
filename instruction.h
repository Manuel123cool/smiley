#pragma once
#include <vector>
#include <string>
#include "stack.h"
class Instruction
{
    struct Jump
    {
        int start{ -1 };
        int jumpTo{ -1 };
    };
    std::vector<Jump> m_jumps;
    std::vector<std::string> m_instructions;
    int checkIf(int whichInstr, Stack &stack);
    int checkLoop(int whichInst, Stack &stack);
    int checkJumps(int num);
    void processFunctions();
public:
    void add(std::string instruction);
    void run();
};
