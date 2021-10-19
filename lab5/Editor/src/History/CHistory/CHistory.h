#pragma once
#include "../../Command/ICommand/ICommand.h"
#include <memory>
#include <vector>

class CHistory
{
	using ICommandPtr = std::unique_ptr<ICommand>;

public:
	bool CanUndo() const;
	bool CanRedo() const;

	void Undo();
	void Redo();

	void AddAndExecuteCommand(ICommandPtr&& commandPtr);

private:
	const size_t HISTORY_LIMITATION = 10;

	std::vector<ICommandPtr> m_items{};
	size_t m_next = 0;
};
