#include "CMenu.h"

CMenu::CMenu(std::istream& inStream, std::ostream& outStream)
	: m_outStream(outStream)
	, m_inStream(inStream)
{
}

void CMenu::Exit()
{
	m_isEnd = true;
}

void CMenu::Run()
{
	std::string command;

	while (m_outStream << ">" && std::getline(m_inStream, command) && ExecuteInstruction(command))
	{
	}
}

void CMenu::AddCommand(const std::string& sketch, const std::string& description, CMenu::Instruction const& instruction)
{
	auto it = std::find_if(m_commands.begin(), m_commands.end(), [&](Command& command) {
		return command.GetSketch() == sketch;
	});

	if (it != m_commands.end())
	{
		return;
	}

	m_commands.emplace_back(Command(sketch, description, instruction));
}

void CMenu::ShowCommands() const
{
	for (auto index = 0; index < m_commands.size(); index++)
	{
		m_outStream << std::to_string(index + 1) << ". <" << m_commands[index].GetSketch() + ">: " << m_commands[index].GetDescription() << std::endl;
	}
}

bool CMenu::ExecuteInstruction(const std::string& instruction)
{
	std::stringstream ss(instruction);
	std::string sketch;
	ss >> sketch;

	auto it = std::find_if(m_commands.begin(), m_commands.end(), [&](Command& command) {
		return command.GetSketch() == sketch;
	});

	if (it == m_commands.end())
	{
		m_outStream << "Error, wrong command\n";
	}
	else
	{
		it->GetInstruction()(ss);
	}

	return !m_isEnd;
}
