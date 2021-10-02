#include "src/InputStream/InputStream.h"
#include "src/OutputStream/OutputStream.h"
#include <iostream>

int main()
{
	std::vector<uint8_t> MEMORY_OUTPUT = {};
	CMemoryOutputStream istream = CMemoryOutputStream(MEMORY_OUTPUT);

	istream.WriteByte('1');
	istream.WriteByte('2');
	istream.WriteByte('3');
	istream.WriteByte('4');


	std::cout << '1' << std::endl;
	std::cout << MEMORY_OUTPUT[1] << std::endl;

	return 0;
}
