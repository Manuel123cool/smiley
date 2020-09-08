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

void Variable::testIfBoolVar(std::string code)
{    
    if (code.length() <= 0)
        return;

    bool isInString{ MyRegex::testString(code, ":b) ") };
    if (!isInString) 
        return;

    std::string identifier{ getIdentifier(code) };

    std::string value1;
    bool start{ false };
    int whiteSpaceCount{ 0 };
    for(const auto &c : code) 
    {    
        if (c == ' ')
             ++whiteSpaceCount;

        if (whiteSpaceCount == 3)
            break;

        if (start)
            value1 += c;    

        if (whiteSpaceCount == 2)
            start = true;
    } 

    if (value1 == "true" || value1 == "false")
    {
        TypeValue typeValue;
        typeValue.identifier = identifier; 
        typeValue.type = BOOL; 
        typeValue.value = value1;
        m_variables.push_back(typeValue);
        return;
    }

    std::string stringValue;
    bool firstValueIsString{ false };
    if (value1.at(0) == '"')
    {
        firstValueIsString = true;
        for (int i{ 1 }; i < value1.length() - 1; ++i)
        {
           stringValue += value1.at(i); 
        } 
        value1 = stringValue;
    }

    std::string operatorStr;
    bool start1{ false };
    int whiteSpaceCount1{ 0 };
    for(const auto &c : code) 
    {    
        if (c == ' ')
             ++whiteSpaceCount1;

        if (whiteSpaceCount1 == 4)
            break;

        if (start1)
            operatorStr += c;    

        if (whiteSpaceCount1 == 3)
            start1 = true;
    } 

    std::string value2;
    bool start2{ false };
    int whiteSpaceCount2{ 0 };
    for(const auto &c : code) 
    {    
        if (c == ' ')
             ++whiteSpaceCount2;

        if (start2)
            value2 += c;    

        if (whiteSpaceCount2 == 4)
            start2 = true;
    } 
    std::string stringValue2;
    bool secondValueIsString{ false };
    if (value2.at(0) == '"')
    {
        secondValueIsString = true;
        for (int i{ 1 }; i < value2.length() - 1; ++i)
        {
           stringValue += value2.at(i); 
        } 
        value2 = stringValue;
    }

    char firstChar[value1.length() + 1];
    char secondChar[value2.length() + 1];

    std::strcpy(firstChar, value1.c_str());    
    std::strcpy(secondChar, value2.c_str());    
    
    bool firstIsNum{ false };
    bool secondIsNum{ false };

    if (static_cast<int>(firstChar[0]) <= 57)
        firstIsNum = true;
         
    if (static_cast<int>(secondChar[0]) <= 57)
        secondIsNum = true;
 
    std::cout << identifier << " " << value1 << " " << operatorStr << " "  << value2 << std::endl;
    TypeValue typeValue;
    typeValue.identifier = identifier; 
    typeValue.type = BOOL; 

    float number1{ 0 };
    float number2{ 0 };

    if (firstIsNum)
        number1 = std::stof(value1);
    
    if (secondIsNum)
        number2 = std::stof(value2);
    
    if (getTypeByIdent(value1) == FLOAT) 
    {
        number1 = std::stof(getValueVar(value1));
        firstIsNum = true;
    }

    if (getTypeByIdent(value2) == FLOAT) 
    {
        number2 = std::stof(getValueVar(value2));
        secondIsNum = true;
    }

    if (operatorStr == "==")
    {
        if (firstIsNum && secondIsNum)
        {
            if (number1 == number2)
            {
                typeValue.value = "true"; 
                m_variables.push_back(typeValue); 
                return;
            }                      
            else
            {
                typeValue.value = "false";
                m_variables.push_back(typeValue); 
                return;
            }            
        }
        if (getTypeByIdent(value1) == INT || getTypeByIdent(value2) == INT) 
        {
            int numberInt1;
            int numberInt2;
            if (getTypeByIdent(value1) == INT && getTypeByIdent(value2) == INT) 
            {
                numberInt1 = std::stoi(getValueVar(value1));
                numberInt2 = std::stoi(getValueVar(value2));
            }
            else if (getTypeByIdent(value1) == INT)
            {
                numberInt1 = std::stoi(getValueVar(value1));
                numberInt2 = static_cast<int>(number2);
            }
            else if (getTypeByIdent(value2) == INT)
            {
                numberInt2 = static_cast<int>(number1);
                numberInt2 = std::stoi(getValueVar(value2));
            }
            if (numberInt1 == numberInt2)
            {
                typeValue.value = "true"; 
                m_variables.push_back(typeValue); 
                return;
            }                      
            else
            {
                typeValue.value = "false";
                m_variables.push_back(typeValue); 
                return;
            }            
        } 
        if (getTypeByIdent(value1) == STRING && getTypeByIdent(value2) == STRING)
        {
            if (getValueVar(value1) == getValueVar(value2))
            {
                typeValue.value = "true"; 
                m_variables.push_back(typeValue); 
                return;
            }                      
            else
            {
                typeValue.value = "false";
                m_variables.push_back(typeValue); 
                return;
            }            
        } 
    }

    if (operatorStr == "!=")
    {
        if (firstIsNum && secondIsNum)
        {
            if (number1 != number2)
            {
                typeValue.value = "true"; 
                m_variables.push_back(typeValue); 
                return;
            }                      
            else
            {
                typeValue.value = "false";
                m_variables.push_back(typeValue); 
                return;
            }            
        }
        if (getTypeByIdent(value1) == INT || getTypeByIdent(value2) == INT) 
        {
            int numberInt1;
            int numberInt2;
            if (getTypeByIdent(value1) == INT && getTypeByIdent(value2) == INT) 
            {
                numberInt1 = std::stoi(getValueVar(value1));
                numberInt2 = std::stoi(getValueVar(value2));
            }
            else if (getTypeByIdent(value1) == INT)
            {
                numberInt1 = std::stoi(getValueVar(value1));
                numberInt2 = static_cast<int>(number2);
            }
            else if (getTypeByIdent(value2) == INT)
            {
                numberInt2 = static_cast<int>(number1);
                numberInt2 = std::stoi(getValueVar(value2));
            }
            if (numberInt1 != numberInt2)
            {
                typeValue.value = "true"; 
                m_variables.push_back(typeValue); 
                return;
            }                      
            else
            {
                typeValue.value = "false";
                m_variables.push_back(typeValue); 
                return;
            }            
        } 
        if (getTypeByIdent(value1) == STRING && getTypeByIdent(value2) == STRING)
        {
            if (getValueVar(value1) != getValueVar(value2))
            {
                typeValue.value = "true"; 
                m_variables.push_back(typeValue); 
                return;
            }                      
            else
            {
                typeValue.value = "false";
                m_variables.push_back(typeValue); 
                return;
            }            
        } 
    }

    if (operatorStr == "<")
    {
        if (firstIsNum && secondIsNum)
        {
            if (number1 < number2)
            {
                typeValue.value = "true"; 
                m_variables.push_back(typeValue); 
                return;
            }                      
            else
            {
                typeValue.value = "false";
                m_variables.push_back(typeValue); 
                return;
            }            
        }
        if (getTypeByIdent(value1) == INT || getTypeByIdent(value2) == INT) 
        {
            int numberInt1;
            int numberInt2;
            if (getTypeByIdent(value1) == INT && getTypeByIdent(value2) == INT) 
            {
                numberInt1 = std::stoi(getValueVar(value1));
                numberInt2 = std::stoi(getValueVar(value2));
            }
            else if (getTypeByIdent(value1) == INT)
            {
                numberInt1 = std::stoi(getValueVar(value1));
                numberInt2 = static_cast<int>(number2);
            }
            else if (getTypeByIdent(value2) == INT)
            {
                numberInt2 = static_cast<int>(number1);
                numberInt2 = std::stoi(getValueVar(value2));
            }
            if (numberInt1 < numberInt2)
            {
                typeValue.value = "true"; 
                m_variables.push_back(typeValue); 
                return;
            }                      
            else
            {
                typeValue.value = "false";
                m_variables.push_back(typeValue); 
                return;
            }            
        } 
    }

    if (operatorStr == ">")
    {
        if (firstIsNum && secondIsNum)
        {
            if (number1 > number2)
            {
                typeValue.value = "true"; 
                m_variables.push_back(typeValue); 
                return;
            }                      
            else
            {
                typeValue.value = "false";
                m_variables.push_back(typeValue); 
                return;
            }            
        }
        if (getTypeByIdent(value1) == INT || getTypeByIdent(value2) == INT) 
        {
            int numberInt1;
            int numberInt2;
            if (getTypeByIdent(value1) == INT && getTypeByIdent(value2) == INT) 
            {
                numberInt1 = std::stoi(getValueVar(value1));
                numberInt2 = std::stoi(getValueVar(value2));
            }
            else if (getTypeByIdent(value1) == INT)
            {
                numberInt1 = std::stoi(getValueVar(value1));
                numberInt2 = static_cast<int>(number2);
            }
            else if (getTypeByIdent(value2) == INT)
            {
                numberInt2 = static_cast<int>(number1);
                numberInt2 = std::stoi(getValueVar(value2));
            }
            if (numberInt1 > numberInt2)
            {
                typeValue.value = "true"; 
                m_variables.push_back(typeValue); 
                return;
            }                      
            else
            {
                typeValue.value = "false";
                m_variables.push_back(typeValue); 
                return;
            }            
        } 
    }
    std::cerr << "Bool: syntax or whatever mistake" << std::endl;
}
