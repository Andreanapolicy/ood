#pragma once
#include "../../Command/CResizeImageCommand/CResizeImageCommand.h"
#include "../../History/CHistory/CHistory.h"
#include "../Exception/ImageDoesNotExistException.h"
#include "../Exception/WrongImageSizeException.h"
#include "../IImage/IImage.h"
#include <filesystem>
#include <vector>

class CImage : public IImage
{
public:
	CImage(const std::string& path, const int width, const int height, CHistory& history);

	std::string GetPath() const override;

	int GetWidth() const override;

	int GetHeight() const override;

	void Resize(int width, int height) override;

	void Remove() override;

private:
	bool CheckExtention(const std::string& path) const;

	std::string const IMAGE_DIRECTORY = "images";
	std::vector<std::string> AVAILABLE_EXTENSIONS = { "jpg", "png", "svg" };

	std::string static GenerateFileName(size_t length);

	std::string m_path;
	int m_width;
	int m_height;
	CHistory& m_history;
};