#include "regex.h"
#include "read_variable.h"

bool Variable::testIfVariable(std::string code)
{
    if (code.length() <= 0)
        return false;

    bool isInString{ MyRegex::testString(code, ":) ") };
    if (!isInString)
        return false;

    if (checkIfValueIsIdentifier(code))
    {
        std::string value{ getValue(code) };
        int count{ 0 };
        for (const auto &elem : m_variables)
        {
            if (value == elem.identifier)
            {
                TypeValue typeValue;

                typeValue.identifier = getIdentifier(code); 
                typeValue.value = m_variables.at(count).value; 
                typeValue.type = m_variables.at(count).type; 
                m_variables.push_back(typeValue); 
                return true;
            } 
            ++count;
        } 
    }

    std::string identifier{ getIdentifier(code) };
    std::string value{ getValue(code) };
    Types type{ getType(code) };

    for (int i{ 0 }; i < m_variables.size(); ++i)
    {
        if (m_variables.at(i).identifier == identifier)
        {
            m_variables.at(i).value = value; 
            m_variables.at(i).type = type;
            return true;
        }
    } 
    
    TypeValue typeValue;

    typeValue.identifier = identifier; 
    typeValue.value = value; 
    typeValue.type = type; 
    m_variables.push_back(typeValue);
    return true;
} 

bool Variable::checkIfValueIsIdentifier(std::string code)
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
    if (value.at(0) == '"')
        return false;
    
    char valueChar[value.length() + 1]; 
    std::strcpy(valueChar, value.c_str());    
    
    if (static_cast<int>(valueChar[0]) > 57)
        return true;
    
    return false;
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

    for (const auto &elem : value)
    {
        if (elem == '.')
            return FLOAT;
    }

    
    return INT;
}

void Variable::printValue(std::string identifier)
{
    for (int i{ 0 }; i < m_variables.size(); ++i)
    {
        if (m_variables.at(i).identifier == identifier)
        {
            std::cout << m_variables.at(i).value << std::endl;
            return; 
        }
    } 
    std::cerr << "Print: identifier not found" << std::endl;
}

void Variable::setVariable(std::string identifier, std::string value, Types type)
{
    for (int i{ 0 }; i < m_variables.size(); ++i)
    {
        if (m_variables.at(i).identifier == identifier)
        {
            m_variables.at(i).value = value; 
            m_variables.at(i).type = type; 
            return;
        }
    } 
    
    TypeValue typeValue; 
    typeValue.identifier = identifier;
    typeValue.value = value;
    typeValue.type = type; 
    
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

void Variable::compareVariable(const Variable &variable)
{
    for (int i{ 0 }; i < variable.m_variables.size(); ++i)
    {
        for (int j{ 0 }; j < m_variables.size(); ++j)
        {
            if (m_variables.at(j).identifier == variable.m_variables.at(i).identifier)
            {
                m_variables.at(j).type = variable.m_variables.at(i).type;
                m_variables.at(j).value = variable.m_variables.at(i).value;
            } 
        } 

    } 
   
}

Variable::Types Variable::getTypeByIdent(std::string identifier)
{
    for (int i{ 0 }; i < m_variables.size(); ++i)
    {
        if (m_variables.at(i).identifier == identifier)
            return m_variables.at(i).type;
    } 
    return STRING;
}
