#include "regex.h"
#include "read_variable.h"

bool Variable::testIfVariable(std::string code)
{
    if (code.length() <= 0)
        return false;

    bool isInString{ MyRegex::testString(code, ":) ") };
    if (!isInString)
        return false;
    
    TypeValue typeValue;

    typeValue.identifier = getIdentifier(code); 
    //std::cout << typeValue.identifier << std::endl;
   
      
    typeValue.value = getValue(code); 
    //std::cout << typeValue.value << std::endl;

    typeValue.type = getType(code); 
    //std::cout << typeValue.type << std::endl;

    m_variables.push_back(typeValue); 
    return true;
} 

std::string Variable::getIdentifier(std::string code)
{
    std::string identifier;
    bool start{ false };
    for(const auto &c : code) 
    {
        if (c == ' ' && start)
            return identifier;

        if (start)
            identifier += c;

        if (c == ' ' && !start)
            start = true;
    } 
    return "something went wrong";
}
  
std::string Variable::getValue(std::string code)
{
    std::string value;
    bool start{ false };
    int whiteSpaceCount{ 0 };
    for(const auto &c : code) 
    {    
         if (start)
            value += c;    

        if (c == ' ')
             ++whiteSpaceCount;

        if (whiteSpaceCount == 2)
            start = true;
        
    } 
    std::string stringValue;
    if (value.at(0) == '"')
    {
        for (int i{ 1 }; i < value.length() - 1; ++i)
        {
           stringValue += value.at(i); 
        } 
        value = stringValue;
    }
    return value; 
}

Variable::Types Variable::getType(std::string code)
{
    std::string value;
    bool start{ false };
    int whiteSpaceCount{ 0 };
    for(const auto &c : code) 
    {    
        if (start)
        {
            value += c;    
        }

        if (c == ' ')
             ++whiteSpaceCount;

        if (whiteSpaceCount == 2)
            start = true;
        
    } 
    if (value.at(0) == '"')
    {
        return STRING;
    }
     
    return INT;
}

void Variable::printValue(std::string identifier)
{
    for (int i{ 0 }; i < m_variables.size(); ++i)
    {
        if (m_variables.at(i).identifier == identifier)
            std::cout << m_variables.at(i).value << std::endl;
    } 
}

void Variable::setVariable(std::string identifier, std::string value)
{
    for (int i{ 0 }; i < m_variables.size(); ++i)
    {
        if (m_variables.at(i).identifier == identifier)
        {
            m_variables.at(i).value = value; 
            return;
        }
    } 
    
    TypeValue typeValue; 
    typeValue.identifier = identifier;
    typeValue.value = value;
    typeValue.type = STRING; 
    
    m_variables.push_back(typeValue);
}

std::string Variable::getValueVar(std::string identifier)
{
    for (int i{ 0 }; i < m_variables.size(); ++i)
    {
        if (m_variables.at(i).identifier == identifier)
            return m_variables.at(i).value;
    } 
    return "smt went wrong";
}
