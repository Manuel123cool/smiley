#include "regex.h"
#include <string>
#include <iostream>
#include "read_variable.h"

bool MyRegex::testString(std::string string, std::string test)
{
    bool isInString{ true };
    for (int i{ 0 }; i < test.length(); ++i)
    {
        if (string.at(i) != test.at(i))
            isInString = false;
    }
    return isInString;
} 

void MyRegex::testComandPrint(std::string code, Variable &variable)
{
    if (code.length() <= 0)
        return;  

    if (!MyRegex::testString(code, "B) "))
        return;
    std::string identifier;
    bool start{ false };
    for(const auto &c : code)
    {
        if (start)
            identifier += c;
   
        if (c == ' ' && !start)
            start = true;
    }
    variable.printValue(identifier);
}

std::string MyRegex::processComments(std::string code)
{
    bool firstEmojiStart{ false };
    bool secondEmojiStart{ false };
    int numOfDelStart{ -1 };
    int numOfDelEnd{ 0 };
    int count{ 0 };
    for(const auto &c : code)
    {
        if (firstEmojiStart && c == '(' && numOfDelStart == -1)
        {
            numOfDelStart = count - 1; 
        }
        else
        {
            firstEmojiStart = false;
        }
        
        
        if (secondEmojiStart && c == '(')
        {
            numOfDelEnd = count;
            break;
        }
        else 
        {
            secondEmojiStart = false;
        }
            
        if (!secondEmojiStart && c == ':' && numOfDelStart != -1)
            secondEmojiStart = true;
    
        if (c == ':' && !firstEmojiStart)
            firstEmojiStart = true; 
        ++count;
    }
    
    std::string codeWithoutCom;
    
    if (numOfDelEnd == 0)
        return code;

    for (int i{ 0 }; i < code.length(); ++i)
    {
        if (i < numOfDelStart)
            codeWithoutCom += code.at(i); 
        if (i > numOfDelEnd)
            codeWithoutCom += code.at(i); 
    }
    return codeWithoutCom;
}

std::string MyRegex::deleteInessentialSpaces(std::string code) 
{
    if (code.length() == 0)
        return code;

    std::vector<int> delNum;
    bool startDel{ false };
    int count{ 0 };
    for(const auto &c : code)
    {
        if (c == '"')
            break;
        if (startDel && c == ' ')
            delNum.push_back(count);
        if (c == ' ')
            startDel = true;
        if (startDel && c != ' ')
            startDel = false;
        ++count;    
    }
    
    bool delAtEnd{ false };
    if (code.at(code.length() - 1) == ' ')
        delAtEnd = true;

    int count1{ 1 };
    while (delAtEnd)
    {
        if (code.at(code.length() - count1) == ' ') 
            delNum.push_back(code.length() - count1);
        else
            delAtEnd = false;
        ++count1; 
    }

    std::string codeWithoutSpaces;
    for (int i{ 0 }; i < code.length(); ++i)
    {
        bool elemDel{ false };
        for (const auto &elem : delNum)
        {
            if (elem == i)
                elemDel = true; 
        }
        if (!elemDel)
            codeWithoutSpaces += code.at(i);
    }
    return codeWithoutSpaces; 
}


void MyRegex::testUserInput(std::string code, Variable &variable)
{
    if (code.length() <= 0)
        return;  

    if (!MyRegex::testString(code, "B-) "))
        return;

    std::string identifier;
    bool start{ false };
    for(const auto &c : code)
    {
        if (start)
            identifier += c;
   
        if (c == ' ' && !start)
            start = true;
    }

    std::string inputValue;
    std::getline(std::cin, inputValue);
    variable.setVariable(identifier, inputValue);
}

void MyRegex::testCalculater(std::string code, Variable &variable)
{
    if (code.length() == 0)
        return;

    if (!MyRegex::testString(code, ":") && code.at(2) != 'S')
        return;

    std::string firstValue;
    std::string secondValue;
    bool identifier1{ false };
    bool identifier2{ false };
    
    bool firstStart{ false };
    bool secondStart{ false };
    for(const auto &c : code) 
    {    
        if (secondStart)
            secondValue += c;

        if (c == ' ' && firstStart)
            secondStart = true;

        if (firstStart && !secondStart)
            firstValue += c;

        if (c == ' ' && !firstStart)
            firstStart = true; 
    } 
    
    char firstChar[firstValue.length() + 1]; 
    char secondChar[secondValue.length() + 1]; 
        
    std::strcpy(firstChar, firstValue.c_str());    
    std::strcpy(secondChar, secondValue.c_str());    
    
    if (static_cast<int>(firstChar[0]) > 57)
        identifier1 = true;
                
    if (static_cast<int>(secondChar[0]) > 57)
        identifier2 = true;
    
    int firstNum{ 0 };
    int secondNum{ 0 }; 
     
    if (identifier1)
        firstNum = std::stoi(variable.getValueVar(firstValue));
    else 
        firstNum = std::stoi(firstValue);

    if (identifier2)
    {
        secondNum = std::stoi(variable.getValueVar(secondValue));
    }
    else 
    {
        std::cerr << "Error calculating: second value should be a identifier";
        return;
    } 
    int result{ 0 }; 
    switch (code.at(1))
    {
        case '+':
            result = firstNum + secondNum;
            break;
        case '*':
            result = firstNum * secondNum;
            break;
         case '-':
            result = firstNum - secondNum;
            break;
         case '/':
            result = firstNum / secondNum;
            break;
         default:
            std::cerr << "calculation syntax error";
    }
    variable.setVariable(secondValue, std::to_string(result)); 
}
