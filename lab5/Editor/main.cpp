#include <iostream>
#include "./src/Client/CEditor/CEditor.h"

int main()
{
	CEditor editor(std::cin, std::cout);

	editor.Run();

	return 0;
}
