#include "include/Duck/CDecoyDuck/CDecoyDuck.h"
#include "include/Duck/CMallardDuck/CMallardDuck.h"
#include "include/Duck/CModelDuck/CModelDuck.h"
#include "include/Duck/CRedheadDuck/CRedheadDuck.h"
#include "include/Duck/CRubberDuck/CRubberDuck.h"
#include <iostream>

void DrawDuck(CDuck const& duck)
{
	duck.Display();
}

void PlayWithDuck(CDuck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Swim();
	duck.Fly();
	duck.Fly();
	duck.Dance();
	std::cout << "Count of fly is: ";
	duck.ShowCountOfFly();
	duck.SetFlyBehavior(std::make_unique<CFlyWithWings>());
	std::cout << "After changing fly behavior count of fly is: ";
	duck.ShowCountOfFly();

	std::cout << std::endl;
}

int main()
{
	CMallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	CRedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	CRubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	CDecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	CModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(std::make_unique<CFlyWithWings>());
	PlayWithDuck(modelDuck);
}
