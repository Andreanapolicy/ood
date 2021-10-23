#pragma once
#include "../IStorage/IStorage.h"
#include <filesystem>
#include <fstream>

class CHTMLSaver : public IStorage
{
public:
	void Save(const std::string& path, IDocument& document) override;

private:
	std::string EscapeString(const std::string& str) const;

	const std::string IMAGES_DIRECTORY = "images";
	const std::vector<std::pair<char, std::string>> ESCAPE_CHARS = {
		{ '<', "&lt;" },
		{ '>', "&gt;" },
		{ '\"', "&quot;" },
		{ '\'', "&apos;" },
		{ '&', "&amp;" },
	};
};