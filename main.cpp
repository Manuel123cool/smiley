#include <iostream>
#include <fstream>
#include <string>
#include "read_variable.h"
#include "regex.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "No command line argument" << std::endl;
        return 1;
    }

    std::ifstream inf{ argv[1] };
 
    if (!inf)
    {
        std::cerr << "Uh oh, Sample.dat could not be opened for reading!\n";
        return 1;
    }
    
    Variable variable;
    
    while (inf)
    {
        std::string strInput;
        std::getline(inf, strInput);
        
        std::string clearedStr{ strInput };
        while (clearedStr != MyRegex::processComments(clearedStr))
        {
            clearedStr = MyRegex::processComments(clearedStr);
        }
        clearedStr = MyRegex::deleteInessentialSpaces(clearedStr);

        if (variable.testIfVariable(clearedStr))        
            continue;
        
        MyRegex::testComandPrint(clearedStr, variable); 
        MyRegex::testUserInput(clearedStr, variable);
        MyRegex::testCalculater(clearedStr, variable);
        
    } 
    return 0;

}

