#include "../../inc/game/States.h"

//正面效果
PositiveStates::PositiveStates()
{
	for (int i = 0; i < top-1; i++)
	{
		round[i] = 0;
	}
}

PositiveStates::~PositiveStates()
{
	//state = 0;
}

void PositiveStates::setPositiveStates(int k, int r)
{
	if (r > 0)
	{
		if (round[k] < r)
			round[k] = r;
	}
	else
		round[k] = 0;
}

bool PositiveStates::isPositiveStates(int k)
{
	if (round[k] == 0)
		return false;
	else
		return true;
}

NegitiveStates::NegitiveStates()
{
	for (int i = 0; i < top-1; i++)
	{
		round[i] = 0;
	}
	burn_dmg = 0; poison_dmg = 0;
}

NegitiveStates::~NegitiveStates()
{
	//state = 0;
}

void NegitiveStates::setNegitiveStates(int k, int r)
{
	if (r > 0)
	{
		if (round[k] < r)
			round[k] = r;
	}
	else
		round[k] = 0;
}

bool NegitiveStates::isNegitiveStates(int k)
{
	if (round[k] == 0)
		return false;
	else
		return true;
}

void NegitiveStates::getBurnDmg(double atk, double percent)
{
	burn_dmg = atk * percent;
}

void NegitiveStates::getPoisonDmg(double atk, double percent)
{
	poison_dmg = atk * percent;
}
