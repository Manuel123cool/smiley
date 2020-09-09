#include "stack.h"
#include "regex.h"

void Stack::addStackFrame()
{
    Variable var;
    if (m_stack.size() > 0)
    {
        var = m_stack.at(m_stack.size() - 1);
    }
    m_stack.push_back(var);
}

void Stack::popStackFrame()
{
    m_stack.at(m_stack.size() - 2).
        compareVariable(m_stack.at(m_stack.size() - 1)); 
    m_stack.pop_back();
}

Variable& Stack::operator()()
{
    return m_stack.at(m_stack.size() - 1);
} 

void Stack::checkBlock(std::string code)
{
    if (code.length() <= 0)
        return;

    bool blockStart{ MyRegex::testString(code, "><") };
    bool blockEnd{ MyRegex::testString(code, "<>") };
    
    if (blockStart)
        addStackFrame();          
    
    if (blockEnd)
       popStackFrame(); 
}

