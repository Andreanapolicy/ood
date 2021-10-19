#include "CHistory.h"

bool CHistory::CanUndo() const
{
	return m_next > 0;
}

bool CHistory::CanRedo() const
{
	return m_next < m_items.size();
}

void CHistory::Undo()
{
	if (CanUndo())
	{
		m_items[--m_next]->Unexecute();
	}
}

void CHistory::Redo()
{
	if (CanRedo())
	{
		m_items[m_next]->Execute();
		m_next++;
	}
}

void CHistory::AddAndExecuteCommand(CHistory::ICommandPtr&& commandPtr)
{
	commandPtr->Execute();

	m_items.erase(m_items.begin() + m_next, m_items.end());
	m_items.push_back(std::move(commandPtr));
	m_next++;

	if (m_next == HISTORY_LIMITATION + 1)
	{
		m_items.erase(m_items.begin());
		m_next--;
	}
}
