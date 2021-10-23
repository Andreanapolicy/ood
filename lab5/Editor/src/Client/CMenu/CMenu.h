#pragma once
#include <functional>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class CMenu
{
	typedef std::function<void(std::istream& inStream)> Instruction;
public:
	CMenu(std::istream& inStream, std::ostream& outStream);

	void Run();

	void AddCommand(const std::string& sketch, const std::string& description, Instruction const& instruction);

	void ShowCommands() const;

	void Exit();
private:

	class Command
	{
	public:
		Command(const std::string& sketch, const std::string& description, Instruction const& instruction)
			: m_sketch(sketch)
			, m_description(description)
			, m_instruction(instruction)
		{
		}

		std::string GetSketch() const
		{
			return m_sketch;
		}

		std::string GetDescription() const
		{
			return m_description;
		}

		Instruction GetInstruction() const
		{
			return m_instruction;
		}

	private:
		std::string m_sketch;
		std::string m_description;
		Instruction m_instruction;
	};

	bool ExecuteInstruction(const std::string& instruction);

	bool m_isEnd = false;
	std::istream& m_inStream;
	std::ostream& m_outStream;
	std::vector<Command> m_commands = {};
};
