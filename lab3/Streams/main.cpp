#include "src/InputStream/InputStream.h"
#include "src/InputStream/InputStreamDecorator.h"
#include "src/OutputStream/OutputStream.h"
#include "src/OutputStream/OutputStreamDecorator.h"
#include <iostream>
#include <map>

std::map<std::string, int> mapOfOption = {
	{ "--encrypt", 1 },
	{ "--decrypt", 2 },
	{ "--compress", 3 },
	{ "--decompress", 4 }
};

std::string ERROR_MESSAGE = "Error. Calling this program should be like:\n ./Streams <options> <input file> <output file>";

bool ChooseOptions(IInputStreamPtr& inputStream, IOutputStreamPtr& outputStream, int argc, char* argv[])
{
	int indexOfOptions = 1;
	while (argc - 2 > indexOfOptions)
	{
		std::string option = argv[indexOfOptions];
		if (mapOfOption.find(option) == mapOfOption.end())
		{
			std::cout << ERROR_MESSAGE << std::endl;

			return false;
		}

		std::cout << mapOfOption[option] << std::endl;

		switch (mapOfOption[option])
		{
		case 1: {
			indexOfOptions++;
			auto key = atoi(argv[indexOfOptions]);
			outputStream = std::make_unique<CEncryptedOutputStream>(std::move(outputStream), key);
			break;
		}
		case 2: {
			indexOfOptions++;
			auto key = atoi(argv[indexOfOptions]);
			inputStream = std::make_unique<CDecryptedInputStream>(std::move(inputStream), key);
			break;
		}
		case 3: {
			outputStream = std::make_unique<CCompressedOutputStream>(std::move(outputStream));
			break;
		}
		case 4: {
			inputStream = std::make_unique<CDecompressedInputStream>(std::move(inputStream));
			break;
		}
		default: {
			std::cout << ERROR_MESSAGE << std::endl;

			return false;
		}
		}

		indexOfOptions++;
	}

	return true;
}

void CopyFile(IInputStreamPtr& inputStream, IOutputStreamPtr& outputStream)
{
	std::cout << "CopyFile" << std::endl;
	while (!inputStream->IsEOF())
	{
		try
		{
			outputStream->WriteByte(inputStream->ReadByte());
		}
		catch (const std::exception& exception)
		{
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << ERROR_MESSAGE << std::endl;

		return 1;
	}

	IInputStreamPtr inputStream = std::make_unique<CFileInputStream>(argv[argc - 2]);
	IOutputStreamPtr outputStream = std::make_unique<CFileOutputStream>(argv[argc - 1]);

	if (!ChooseOptions(inputStream, outputStream, argc, argv))
	{
		return 1;
	}

	CopyFile(inputStream, outputStream);

	return 0;
}
