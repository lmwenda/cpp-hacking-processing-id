#include <iostream>
#include "exeOpener.h"

class ClassInitiliazers
{
    public:
        string exeName;
        exePrompt = NULL;

};

void prompt()
{
    ClassInitiliazers classDefiner;
    std::cout<<"Enter the path of the .exe file you want to open: "<<std::endl;
    getline(std::cin, classDefiner.exeName);
    std::cout<<"Opening file from "<<classDefiner.exeName<<std::endl;

    // Opening .exe file here
}

int main()
{
    // Render all of the Components of the File Opener here
}
