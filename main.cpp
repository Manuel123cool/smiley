#include <iostream>
#include <fstream>
#include <string>
#include "read_variable.h"
#include "regex.h"
#include "stack.h"
#include "instruction.h"
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
    Instruction instruction;

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

        instruction.add(clearedStr);
    } 
    instruction.run();
    return 0;
}

