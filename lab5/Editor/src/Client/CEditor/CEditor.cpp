#include "CEditor.h"

CEditor::CEditor(std::istream& inStream, std::ostream& outStream)
	: m_outStream(outStream)
	, m_inStream(inStream)
	, m_document(std::make_unique<CDocument>())
	, m_menu(inStream, outStream)
{
	m_menu.AddCommand("insertParagraph", "Insert in document paragraph", [this](std::istream& inStream) { InsertParagraph(inStream); });
	m_menu.AddCommand("insertImage", "Insert in document image", [this](std::istream& inStream) { InsertImage(inStream); });
	m_menu.AddCommand("setTitle", "Set title of document", [this](std::istream& inStream) { SetTitle(inStream); });
	m_menu.AddCommand("list", "Show result document", [this](std::istream& inStream) { ShowDocument(inStream); });
	m_menu.AddCommand("replaceText", "Replace text in paragraph", [this](std::istream& inStream) { ReplaceText(inStream); });
	m_menu.AddCommand("resizeImage", "Resize image", [this](std::istream& inStream) { ResizeImage(inStream); });
	m_menu.AddCommand("deleteItem", "Delete item", [this](std::istream& inStream) { DeleteItem(inStream); });
	m_menu.AddCommand("undo", "Undo last change", [this](std::istream& inStream) { Undo(inStream); });
	m_menu.AddCommand("redo", "Redo last undo", [this](std::istream& inStream) { Redo(inStream); });
	m_menu.AddCommand("save", "Save in html format and exit", [this](std::istream& inStream) { Save(inStream); });
	m_menu.AddCommand("help", "Show all commands", [this](std::istream& inStream) { m_menu.ShowCommands(); });
	m_menu.AddCommand("exit", "Exit from program", [this](std::istream& inStream) { m_menu.Exit(); });
}

void CEditor::Run()
{
	m_menu.Run();
}

void CEditor::InsertParagraph(std::istream& inStream)
{
	std::string stringIndex;
	std::string text;

	try
	{
		if (!(inStream >> stringIndex) || !(getline(inStream, text)))
		{
			throw CInvalidParamsException("Error, invalid params for inserting paragraph");
		}

		m_document->InsertParagraph(text, stringIndex == "end" ? m_document->GetItemsCount() : std::stoi(stringIndex));
	}
	catch (std::exception& exception)
	{
		m_outStream << exception.what() << std::endl;
	}
}

void CEditor::InsertImage(std::istream& inStream)
{
	std::string stringIndex;
	int width;
	int height;
	std::string path;

	try
	{
		if (!(inStream >> stringIndex) || !(inStream >> width) || !(inStream >> height) || !(inStream >> path))
		{
			throw CInvalidParamsException("Error, invalid params for inserting image");
		}

		m_document->InsertImage(path, width, height, stringIndex == "end" ? m_document->GetItemsCount() : std::stoi(stringIndex));
	}
	catch (std::exception& exception)
	{
		m_outStream << exception.what() << std::endl;
	}
}

void CEditor::SetTitle(std::istream& inStream)
{
	std::string title;

	try
	{
		if (!(getline(inStream, title)))
		{
			throw CInvalidParamsException("Error, invalid params for changing title");
		}

		m_document->SetTitle(title);
	}
	catch (std::exception& exception)
	{
		m_outStream << exception.what() << std::endl;
	}
}

void CEditor::ShowDocument(std::istream& inStream)
{
	m_outStream << "Title: " << m_document->GetTitle() << std::endl;

	for (auto index = 0; index < m_document->GetItemsCount(); index++)
	{
		m_outStream << std::to_string(index + 1) << ". ";

		if (m_document->GetItem(index).GetParagraph())
		{
			m_outStream << "paragraph: " << m_document->GetItem(index).GetParagraph()->GetText();
		}
		else
		{
			auto image = m_document->GetItem(index).GetImage();
			m_outStream << "image: " << std::to_string(image->GetWidth()) << "x" << std::to_string(image->GetHeight()) << ", src: " << image->GetPath();
		}

		m_outStream << std::endl;
	}
}

void CEditor::ReplaceText(std::istream& inStream)
{
	size_t index;
	std::string text;

	try
	{
		if (!(inStream >> index) || !(getline(inStream, text)))
		{
			throw CInvalidParamsException("Error, invalid params for replacing text");
		}

		m_document->ReplaceParagraphText(index, text);
	}
	catch (std::exception& exception)
	{
		m_outStream << exception.what() << std::endl;
	}
}

void CEditor::ResizeImage(std::istream& inStream)
{
	size_t index;
	int width;
	int height;

	try
	{
		if (!(inStream >> index) || !(inStream >> width) || !(inStream >> height))
		{
			throw CInvalidParamsException("Error, invalid params for resizing image");
		}

		m_document->ResizeImage(index, width, height);
	}
	catch (std::exception& exception)
	{
		m_outStream << exception.what() << std::endl;
	}
}

void CEditor::DeleteItem(std::istream& inStream)
{
	size_t index;

	try
	{
		if (!(inStream >> index))
		{
			throw CInvalidParamsException("Error, invalid params for deleting image");
		}

		m_document->RemoveItem(index);
	}
	catch (std::exception& exception)
	{
		m_outStream << exception.what() << std::endl;
	}
}

void CEditor::Undo(std::istream& inStream)
{
	if (!m_document->CanUndo())
	{
		m_outStream << "Error, there are no operation to undo" << std::endl;
		return;
	}

	m_document->Undo();
}

void CEditor::Redo(std::istream& inStream)
{
	if (!m_document->CanRedo())
	{
		m_outStream << "Error, there are no operation to redo" << std::endl;
		return;
	}

	m_document->Redo();
}

void CEditor::Save(std::istream& inStream)
{
}
