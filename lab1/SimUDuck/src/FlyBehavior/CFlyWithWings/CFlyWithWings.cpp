#include "../../../include/FlyBehavior/CFlyWithWings/CFlyWithWings.h"

void CFlyWithWings::Fly()
{
	m_countOfFly++;
	std::cout << "I'm flying with wings!!" << std::endl;
}

void CFlyWithWings::ShowCountOfFly()
{
	std::cout << m_countOfFly << std::endl;
}
