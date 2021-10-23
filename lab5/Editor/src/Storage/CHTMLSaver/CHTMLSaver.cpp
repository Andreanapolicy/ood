#include "CHTMLSaver.h"

void CHTMLSaver::Save(const std::string& path, IDocument& document)
{
	std::ofstream htmlFile(path);

	std::string directory = std::filesystem::path(path).parent_path() / IMAGES_DIRECTORY;

	if (!std::filesystem::is_directory(directory))
	{
		std::filesystem::create_directory(directory);
	}

	htmlFile << "<html>\n"
			 << "<head>\n"
			 << "<title>" << EscapeString(document.GetTitle()) << "</title>\n"
			 << "</head>\n"
			 << "<body>\n";

	for (auto index = 0; index < document.GetItemsCount(); index++)
	{
		if (document.GetItem(index).GetImage())
		{
			auto image = document.GetItem(index).GetImage();
			auto src = image->GetPath();
			int width = image->GetWidth();
			int height = image->GetHeight();

			htmlFile << "<img src=\"" + src + "\" width=\"" + std::to_string(width) + "\" height=\"" + std::to_string(height) + "\" />" << std::endl;

			if (!std::filesystem::exists(directory / std::filesystem::path(path).filename()))
			{
				std::filesystem::copy_file(src, directory / std::filesystem::path(path).filename());
			}
		}
		else
		{
			auto paragraph = document.GetItem(index).GetParagraph();

			htmlFile << "<p>" + EscapeString(paragraph->GetText()) + "</p>" << std::endl;
		}
	}

	htmlFile << "</body>\n"
			 << "</html>" << std::endl;
}

std::string CHTMLSaver::EscapeString(const std::string& str) const
{
	std::string result;

	for (auto ch : str)
	{
		auto it = std::find_if(ESCAPE_CHARS.begin(), ESCAPE_CHARS.end(), [&](std::pair<char, std::string> pair) {
			return pair.first == ch;
		});

		if (it == ESCAPE_CHARS.end())
		{
			result += ch;
		}
		else
		{
			result += it->second;
		}
	}

	return result;
}
