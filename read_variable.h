#pragma once 
#include <vector>
#include <string>
#include <iostream>

class Variable
{
public:
    enum Types
    {
        INT,
        STRING,
        FLOAT
    };
private:
    struct TypeValue
    {
        Types type;
        std::string value;    
        std::string identifier;
    };
    std::vector<TypeValue> m_variables;  
    std::string getIdentifier(std::string code);
    std::string getValue(std::string code);
    Types getType(std::string code);
public:
    bool testIfVariable(std::string code);
    std::string getValueVar(std::string identifer);
    void printValue(std::string identifier);
    void setVariable(std::string identifier, std::string value);
};
