#pragma once
#include <iostream>
#include "Stats.h"

//角色创建在此头文件，平A、技能、终结技或天赋在角色对应的类中创建
//可随意创建角色用来测试


class S0 :public Stats
{
public:
	S0(const std::wstring& name);
	void normalAttack(Stats* op1, Stats* op2, Stats* op3) override;
	void Skill(Stats* op1, Stats* op2, Stats* op3) override;
	void Draw() override;
};

class S1 :public Stats
{
public:
	S1(const std::wstring& name);
	void normalAttack(Stats* op1, Stats* op2, Stats* op3)override;
	void Skill(Stats* op1, Stats* op2, Stats* op3) override;
	void Draw() override;
};

class S2 :public Stats
{
public:
	S2(const std::wstring& name);
	void normalAttack(Stats* op1, Stats* op2, Stats* op3)override;
	void Skill(Stats* op1, Stats* op2, Stats* op3) override;
	void Draw() override;
};

class S3 :public Stats
{
public:
	S3(const std::wstring& name);
	void normalAttack(Stats* op1, Stats* op2, Stats* op3)override;
	void Skill(Stats* op1, Stats* op2, Stats* op3) override;
	void Draw() override;
};
