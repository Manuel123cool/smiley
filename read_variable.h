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
        FLOAT,
        BOOL
    };
private:
    struct TypeValue
    {
        Types type;
        std::string value;    
        std::string identifier;
    };
    struct ArrayValue
    {
        Types type;
        std::string value;    
        std::string identifier;
        int id;
    };
 
    std::vector<TypeValue> m_variables;  
    std::vector<ArrayValue> m_arrays;
    std::string getIdentifier(std::string code);
    std::string getValue(std::string code);
    Types getType(std::string code);
    bool checkIfValueIsIdentifier(std::string code);
public:
    Types getTypeByIdent(std::string ident);
    bool testIfVariable(std::string code);
    void testIfBoolVar(std::string code);
    std::string getValueVar(std::string identifer);
    void printValue(std::string identifier);
    void setVariable(std::string identifier, std::string value, Types type);
    void compareVariable(const Variable &variable);   
};
