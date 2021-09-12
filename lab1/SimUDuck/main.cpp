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
	duck.Fly();
	duck.Dance();
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
