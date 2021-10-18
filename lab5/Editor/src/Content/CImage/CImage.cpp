#include "CImage.h"
#include <random>

CImage::CImage(const std::string& path, const int width, const int height)
{
	if (CheckExtention(path) || !std::filesystem::exists(path))
	{
		throw ImageDoesNotExistException("Error, wrong image path. Image does not exist");
	}

	if (width < 1 || width > 10000 || height < 1 || height > 10000)
	{
		throw WrongImageSizeException("Error, wrong image size(should be [1, 10000])");
	}

	m_width = width;
	m_height = height;

	if (!std::filesystem::is_directory(IMAGE_DIRECTORY))
	{
		std::filesystem::create_directory(IMAGE_DIRECTORY);
	}

	std::string newImagePath = IMAGE_DIRECTORY + '/' + GenerateFileName(8) + std::filesystem::path(path).extension().string();
	std::filesystem::copy(path, newImagePath);

	m_path = newImagePath;
}

std::string CImage::GetPath() const
{
	return m_path;
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	if (width < 1 || width > 10000 || height < 1 || height > 10000)
	{
		throw WrongImageSizeException("Error, wrong image size(should be [1, 10000])");
	}

	m_width = width;
	m_height = height;
}

void CImage::Remove()
{

}

std::string CImage::GenerateFileName(size_t length)
{
	const std::string availableChars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<size_t> distribution(0, availableChars.size() - 1);

	std::string fileName;

	for (size_t i = 0; i < length; ++i)
	{
		fileName += availableChars[distribution(generator)];
	}

	return fileName;
}

bool CImage::CheckExtention(const std::string& path) const
{
	std::string extention = std::filesystem::path(path).string();

	return std::find(AVAILABLE_EXTENSIONS.begin(), AVAILABLE_EXTENSIONS.end(), extention) != AVAILABLE_EXTENSIONS.end();
}
