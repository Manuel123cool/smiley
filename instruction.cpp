#include "instruction.h"
#include "read_variable.h"
#include "regex.h"
#include "stack.h"
#include <stdexcept>

void Instruction::add(std::string instruction)
{
    if (instruction.length() > 0)
         m_instructions.push_back(instruction);
}

void Instruction::run()
{
    processFunctions();
    Stack stack;
    stack.addStackFrame();
    for (int i{ 0 }; i < m_instructions.size(); ++i)  
    {
        std::string code{ m_instructions.at(i) };
        int jumpNum{ checkJumps(i) };
        if (jumpNum != -1)
            i = jumpNum; 

        if (checkIf(i, stack) != -1)
            i = checkIf(i, stack); 
        if (checkLoop(i, stack) != -1)
            i = checkLoop(i, stack); 

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
        int countBlockStarts{ 0 };
        for (int i{ whichInstr }; i < m_instructions.size(); ++i)  
        {
            std::string code{ m_instructions.at(i) };

            if (MyRegex::testString(code, "><"))
                ++countBlockStarts;

            if (MyRegex::testString(code, "<>"))
                --countBlockStarts;

            if (MyRegex::testString(code, "<>") && countBlockStarts == 0)
                return i;
            
        }
    }
    return -1;
}


int Instruction::checkLoop(int whichInstr, Stack &stack)
{
    std::string code{ m_instructions.at(whichInstr) };
    if (code.length() <= 0)
        return -1;

    if (!MyRegex::testString(code, "<* "))
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
        int countBlockStarts{ 0 };
        for (int i{ whichInstr }; i < m_instructions.size(); ++i)  
        {
            std::string code{ m_instructions.at(i) };

            if (MyRegex::testString(code, "><"))
                ++countBlockStarts;

            if (MyRegex::testString(code, "<>"))
                --countBlockStarts;

            if (MyRegex::testString(code, "<>") && countBlockStarts == 0)
            {
                Jump jump;
                jump.start = i;
                jump.jumpTo = whichInstr;
                m_jumps.push_back(jump); 
            }
        }       
    }
    else 
    {
        int countBlockStarts{ 0 };
        for (int i{ whichInstr }; i < m_instructions.size(); ++i)  
        {
            std::string code{ m_instructions.at(i) };

            if (MyRegex::testString(code, "><"))
                ++countBlockStarts;

            if (MyRegex::testString(code, "<>"))
                --countBlockStarts;

            if (MyRegex::testString(code, "<>") && countBlockStarts == 0)
                return i;
        } 
    }
    return -1;
}


int Instruction::checkJumps(int num)
{
    for (int i{ 0 }; i < m_jumps.size(); ++i)
    {
        int startNum = m_jumps.at(i).start;
        if (startNum == num)
        {
            int jumpTo{ m_jumps.at(i).jumpTo };
            for (int j{ 0 }; j < m_jumps.size(); ++j)
            {
                if (m_jumps.at(j).start == startNum && m_jumps.at(j).jumpTo == jumpTo)
                    m_jumps.erase(m_jumps.begin() + j);
            }
            return jumpTo;
        }
    }
    return -1;
}

void Instruction::processFunctions()
{
    struct Funct
    {
        std::string identifier;
        int start;
        int end; 
    };
    std::vector<Funct> functIdent;

    for (int i{ 0 }; i < m_instructions.size(); ++i)  
    {
        std::string code{ m_instructions.at(i) };

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
 
        bool isInString{ MyRegex::testString(code, ":D ") };    
        if (isInString)
        {
            int jmpTo{ -1 };
            int countBlockStarts{ 0 };
            for (int j{ i }; j < m_instructions.size(); ++j)  
            {
                std::string code{ m_instructions.at(j) };

                if (MyRegex::testString(code, "><"))
                    ++countBlockStarts;

                if (MyRegex::testString(code, "<>"))
                    --countBlockStarts;

                if (MyRegex::testString(code, "<>") && countBlockStarts == 0)
                    jmpTo = j;
            } 
            if (jmpTo == -1)
                std::cerr << "Smt went in functions wrong" << std::endl;

            Jump jump;
            jump.start = i;
            jump.jumpTo = jmpTo;
            m_jumps.push_back(jump); 
            
            Funct func;
            func.start = i;
            func.end = jmpTo;
            func.identifier = identifier;
            functIdent.push_back(func); 
        }     

        bool isInString1{ MyRegex::testString(code, ";) ") };    
        if (isInString1)
        {
            for (const auto &elem : functIdent)
            {
                if (elem.identifier == identifier)
                {
                    Jump jump;
                    jump.start = i;
                    jump.jumpTo = elem.start;
                    m_jumps.push_back(jump); 
                    
                    Jump jump1;
                    jump1.start = elem.end;
                    jump1.jumpTo = i;
                    m_jumps.push_back(jump1); 
 
                }
            }
        } 
    }
}
