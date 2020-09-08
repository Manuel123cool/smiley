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
    int count{ 0 };
    for (const auto &code : m_instructions)
    {
        stack.checkBlock(code);
        if (stack().testIfVariable(code))        
            continue;
        stack().testIfBoolVar(code);

        MyRegex::testComandPrint(code, stack); 
        MyRegex::testUserInput(code, stack);
        MyRegex::testCalculater(code, stack);
        ++count;
    }
}
