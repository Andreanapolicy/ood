#include "src/InputStream/InputStream.h"
#include "src/InputStream/InputStreamDecorator.h"
#include "src/OutputStream/OutputStream.h"
#include "src/OutputStream/OutputStreamDecorator.h"
#include <iostream>

int main()
{
	std::string FILE_NAME = "file.txt";

	auto stream = std::make_unique<CFileOutputStream>(FILE_NAME);
	auto compressedStream = CCompressedOutputStream(std::move(stream));

	compressedStream.WriteByte('1');
	compressedStream.WriteByte('C');
	compressedStream.WriteByte('C');
	compressedStream.WriteByte('A');
	compressedStream.WriteByte('A');
	compressedStream.WriteByte('A');
	compressedStream.WriteByte('\n');
	compressedStream.WriteByte('A');

	auto inStream = std::make_unique<CFileInputStream>(FILE_NAME);
	auto decompressedStream = CDecompressedInputStream(std::move(inStream));

	std::cout << decompressedStream.ReadByte() << std::endl;
	std::cout << decompressedStream.ReadByte() << std::endl;
	std::cout << decompressedStream.ReadByte() << std::endl;
	std::cout << decompressedStream.ReadByte() << std::endl;
	std::cout << decompressedStream.ReadByte() << std::endl;
	std::cout << decompressedStream.ReadByte() << std::endl;
	std::cout << decompressedStream.ReadByte() << std::endl;
//	std::cout << decompressedStream.ReadByte() << std::endl;
	return 0;
}
