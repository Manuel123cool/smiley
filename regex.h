#pragma once
#include <string>
#include <iostream>
#include "read_variable.h"
#include <bits/stdc++.h> 

namespace MyRegex
{
    bool testString(std::string string, std::string test);
    void testComandPrint(std::string code, Variable &variable);
    void testUserInput(std::string code, Variable &variable);
    void testCalculater(std::string, Variable &variable);

    std::string processComments(std::string code);
    std::string deleteInessentialSpaces(std::string code); 
}
