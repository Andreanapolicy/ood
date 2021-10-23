#pragma once
#include "../../Command/CChangeTitleCommand/CChangeTitleCommand.h"
#include "../../Command/CDeleteItemCommand/CDeleteItemCommand.h"
#include "../../Command/CInsertDocumentItemCommand/CInsertDocumentItemCommand.h"
#include "../../Content/CImage/CImage.h"
#include "../../Content/CParagraph/CParagraph.h"
#include "../CConstDocumentItem/CConstDocumentItem.h"
#include "../Exception/CWrongItemException/CWrongItemException.h"
#include "../IDocument/IDocument.h"

class CDocument : public IDocument
{
public:
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, size_t position) override;

	std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height, size_t position) override;

	CConstDocumentItem GetItem(size_t index) const override;

	CDocumentItem GetItem(size_t index) override;

	void SetTitle(const std::string& title) override;

	std::string GetTitle() const override;

	size_t GetItemsCount() const override;

	void ResizeImage(size_t index, int width, int height) override;

	void ReplaceParagraphText(size_t index, const std::string& text) override;

	void RemoveItem(size_t index) override;

	void Save(const std::string& path) const override;

	bool CanUndo() const override;

	void Undo() override;

	bool CanRedo() const override;

	void Redo() override;

private:
	CHistory m_history;
	std::vector<CDocumentItem> m_items = {};
	std::string m_title = "";
};
