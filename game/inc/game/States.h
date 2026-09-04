#pragma once

//正面效果，同名效果取持续回合数最高
class PositiveStates
{
public:
	PositiveStates();
	~PositiveStates();

	enum
	{
		Immune,			//免疫：无视所有负面效果，第0位
		ControlImmune,	//控制免疫：无视所有控制类负面效果，第1位
		NegitiveImmune,	//负面状态免疫：无视所有状态类负面效果，第2位
		top
	};

	//round为状态对应的剩余回合数，0表示对应状态未激活，大于0表示剩余回合数，数组序号和枚举一一对应
	int round[top-1];

	//对应状态改变
	void setPositiveStates(int k, int r);
	bool isPositiveStates(int k);
};

//状态类负面效果：不影响行动且不造成控制类负面效果，同名效果取持续回合数最高
class NegitiveStates
{
public:
	NegitiveStates();
	~NegitiveStates();

	enum
	{
		Burned,		//燃烧：自身回合开始时受到来源目单位攻击力一定比例的法伤，第0位
		Poisoning,	//中毒：自身回合开始时受到来源目单位攻击力一定比例的法伤，第1位
		top
	};

	//round为状态对应的剩余回合数，0表示对应状态未激活，大于0表示剩余回合数，数组序号和枚举一一对应
	int round[top-1];

	//对应状态改变
	void setNegitiveStates(int k, int r);
	bool isNegitiveStates(int k);

	//燃烧伤害
	double burn_dmg;
	void getBurnDmg(double atk,double percent);

	//中毒伤害
	double poison_dmg;
	void getPoisonDmg(double atk, double percent);
};

class States
{
public:
	PositiveStates PS;
	NegitiveStates NS;
};