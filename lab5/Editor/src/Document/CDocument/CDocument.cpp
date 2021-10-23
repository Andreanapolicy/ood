#include "CDocument.h"

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string& text, size_t position)
{
	auto newParagraph = std::make_shared<CParagraph>(text, m_history);
	auto newDocumentItem = CDocumentItem(newParagraph);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertDocumentItemCommand>(m_items, newDocumentItem, position));

	return newParagraph;
}

std::shared_ptr<IImage> CDocument::InsertImage(const std::string& path, int width, int height, size_t position)
{
	auto newImage = std::make_shared<CImage>(path, width, height, m_history);
	auto newDocumentItem = CDocumentItem(newImage);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertDocumentItemCommand>(m_items, newDocumentItem, position));

	return newImage;
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	return m_items.at(index);
}

CDocumentItem CDocument::GetItem(size_t index)
{
	return m_items.at(index);
}

void CDocument::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(std::make_unique<CChangeTitleCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

void CDocument::ResizeImage(size_t index, int width, int height)
{
	if (index > GetItemsCount())
	{
		throw CWrongIndexOfItemInDocumentException("Error, index greater then document size");
	}

	auto item = GetItem(index);
	if (!item.GetImage())
	{
		throw CWrongItemException("Error, calling wrong item by index");
	}

	item.GetImage()->Resize(width, height);
}

void CDocument::ReplaceParagraphText(size_t index, const std::string& text)
{
	if (index > GetItemsCount())
	{
		throw CWrongIndexOfItemInDocumentException("Error, index greater then document size");
	}

	auto item = GetItem(index);
	if (!item.GetParagraph())
	{
		throw CWrongItemException("Error, calling wrong item by index");
	}

	item.GetParagraph()->SetText(text);
}

void CDocument::RemoveItem(size_t index)
{
	m_history.AddAndExecuteCommand(std::make_unique<CDeleteItemCommand>(m_items, index));
}

void CDocument::Save(const std::string& path) const
{
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	return m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	return m_history.Redo();
}
