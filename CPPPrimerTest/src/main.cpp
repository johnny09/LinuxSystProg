#include <iostream>
#include "Sales_data.h"
#include "Screen.h"

int main()
{
    Screen myScreen(5,5,'X');
    myScreen.move(4,0).set('#').display(std::cout);
    std::cout<<"/n";
    myScreen.display(std::cout);
    std::cout<<"/n";
}