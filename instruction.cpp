#include "instruction.h"
#include "read_variable.h"
#include "regex.h"
#include "stack.h"

void Instruction::add(std::string instruction)
{
    if (instruction.length() > 0)
         m_instructions.push_back(instruction);
}

void Instruction::run()
{
    Stack stack;
    stack.addStackFrame();
    for (int i{ 0 }; i < m_instructions.size(); ++i)  
    {
        std::string code{ m_instructions.at(i) };
        if (checkIf(i, stack) != -1)
            i = checkIf(i, stack); 

        stack.checkBlock(code);
        if (stack().testIfVariable(code))        
            continue;
        stack().testIfBoolVar(code);

        MyRegex::testComandPrint(code, stack); 
        MyRegex::testUserInput(code, stack);
        MyRegex::testCalculater(code, stack);
    }
}

int Instruction::checkIf(int whichInstr, Stack &stack)
{
    std::string code{ m_instructions.at(whichInstr) };
    if (code.length() <= 0)
        return -1;

    if (!MyRegex::testString(code, ":/ "))
        return -1;
    
    std::string identifier;
    bool start{ false };
    for(const auto &c : code) 
    {
        if (c == ' ' && start)
            break; 

        if (start)
            identifier += c;

        if (c == ' ' && !start)
            start = true;
    }     
    std::string value{ stack().getValueVar(identifier) };
    
    if (value == "true")
    {
        return whichInstr;
    }
    else 
    {
        for (int i{ whichInstr }; i < m_instructions.size(); ++i)  
        {
            std::string code{ m_instructions.at(i) };
            if (MyRegex::testString(code, "<>"))
                return i;
        }
    }
}
