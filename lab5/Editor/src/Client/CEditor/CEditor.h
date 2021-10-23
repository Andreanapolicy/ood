#pragma once
#include "../CMenu/CMenu.h"
#include "../../Document/CDocument/CDocument.h"
#include "../Exception/CInvalidParamsException/CInvalidParamsException.h"

class CEditor
{
public:
	CEditor(std::istream& inStream, std::ostream& outStream);

	void Run();

private:
	void InsertParagraph(std::istream& inStream);

	void InsertImage(std::istream& inStream);

	void SetTitle(std::istream& inStream);

	void ShowDocument(std::istream& inStream);

	void ReplaceText(std::istream& inStream);

	void ResizeImage(std::istream& inStream);

	void DeleteItem(std::istream& inStream);

	void Undo(std::istream& inStream);

	void Redo(std::istream& inStream);

	void Save(std::istream& inStream);

	std::unique_ptr<IDocument> m_document;
	CMenu m_menu;

	std::istream& m_inStream;
	std::ostream& m_outStream;
};
