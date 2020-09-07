#pragma once
#include "read_variable.h"

class Stack 
{
    std::vector<Variable> m_stack;
public:
    void addStackFrame();
    void popStackFrame();
    void checkBlock(std::string code);
    Variable& operator()();
};
