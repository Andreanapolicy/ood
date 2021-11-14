#include <iostream>
#include "src/GumballMachineController/GumballMachineController.h"

int main()
{
    GumballMachineController gumballMachineController(std::cin, std::cout);

	gumballMachineController.Run();

    return 0;
}
