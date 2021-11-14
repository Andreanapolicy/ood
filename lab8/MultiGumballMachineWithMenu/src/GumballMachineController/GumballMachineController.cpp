#include "GumballMachineController.h"

GumballMachineController::GumballMachineController(std::istream& input, std::ostream& output)
	: m_outStream(output)
	, m_menu(input, output)
	, m_gumballMachine(CGumballMachine(0))
{
	m_menu.AddCommand("add_gumballs", "Adding to machine gumballs", [this](std::istream& input){ InsertBalls(input); });
	m_menu.AddCommand("insert_quarter", "Inserting quarter", [this](std::istream& input){ InsertQuarter(); });
	m_menu.AddCommand("eject_quarter", "Ejecting quarter(s)", [this](std::istream& input){ EjectQuarter(); });
	m_menu.AddCommand("turn_crank", "Turning the crank of machine gumballs", [this](std::istream& input){ TurnCrank(); });
	m_menu.AddCommand("state", "Getting state of machine gumballs", [this](std::istream& input){ GetState(); });
	m_menu.AddCommand("help", "Show all commands", [this](std::istream& inStream) { m_menu.ShowCommands(); });
	m_menu.AddCommand("exit", "Exit from program", [this](std::istream& inStream) { m_menu.Exit(); });
}

void GumballMachineController::Run()
{
	m_menu.Run();
}

void GumballMachineController::EjectQuarter()
{
	m_gumballMachine.EjectQuarter();
}

void GumballMachineController::InsertQuarter()
{
	m_gumballMachine.InsertQuarter();
}

void GumballMachineController::InsertBalls(std::istream& input)
{
	unsigned int count;
	input >> count;

	m_gumballMachine.InsertBalls(count);
}

void GumballMachineController::TurnCrank()
{
	m_gumballMachine.TurnCrank();
}

void GumballMachineController::GetState() const
{
	m_outStream << m_gumballMachine.ToString() << std::endl;
}
