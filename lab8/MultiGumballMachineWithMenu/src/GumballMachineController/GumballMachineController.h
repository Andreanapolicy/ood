#pragma once
#include "../Menu/CMenu/CMenu.h"
#include "../GumballMachine/IGumballMachine/IGumballMachine.h"
#include "../GumballMachine/CGumballMachine/CGumballMachine.h"

class GumballMachineController
{
public:
    GumballMachineController(std::istream& input, std::ostream& output);

    void Run();
private:
    void EjectQuarter();

    void InsertQuarter();

    void InsertBalls(std::istream& input);

    void TurnCrank();

    void GetState() const;

    CGumballMachine m_gumballMachine;
    CMenu m_menu;
    std::ostream& m_outStream;
};
