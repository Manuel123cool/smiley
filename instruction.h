#pragma once
#include <vector>
#include <string>
class Instruction
{
    std::vector<std::string> m_instructions;
public:
    void add(std::string instruction);
    void run();
};
