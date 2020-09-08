#pragma once
#include <string>
#include <iostream>
#include "read_variable.h"
#include <bits/stdc++.h> 
#include "stack.h"

namespace MyRegex
{
    bool testString(std::string string, std::string test);
    void testComandPrint(std::string code, Stack &stack);
    void testUserInput(std::string code, Stack &stack);
    void testCalculater(std::string, Stack &stack);
    
    std::string processComments(std::string code);
    std::string deleteInessentialSpaces(std::string code); 
}
