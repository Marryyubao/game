#pragma once
#include <iostream>
using namespace std;
#include"../Defines.h"
#include"../game/GameObject.h"
#include "../utils/ImageShow.h"

//Multiplier作用于基础数值的调整，各部分的作用参考明日方舟wiki

class Multiplier
{
public:

	Multiplier();
	~Multiplier();

	typedef struct
	{
		string sign;	//加成来源名字，同名加成取最高值，剩余回合取较大值
		double value;	//加成数值
		int round;		//剩余回合：0仍生效，减到-1时过期并释放槽位
	}Mul;

	Mul* preadd = new Mul[20];//前置加算部分：一般为场地效果，不同加成效果之间加算，会使得属性面板改变，默认为0
	Mul* premul = new Mul[20];//前置乘算部分：一般为场地效果，不同加成效果之间加算，会使得属性面板改变，默认为1
	Mul* diradd = new Mul[20];//直接加算部分：一般为技能效果，不同加成效果之间加算，会使得属性面板改变，默认为0
	Mul* dirmul = new Mul[20];//直接乘算部分：一般为技能效果，不同加成效果之间加算，会使得属性面板改变，默认为0
	Mul* finadd = new Mul[20];//最终加算部分：结算伤害时作用，不同加成效果之间加算，不改变面板属性，默认为0
	Mul* finmul = new Mul[20];//最终乘算部分：结算伤害时作用，不同加成效果之间乘算，不改变面板属性，默认为0	

	//初始化每个加成列表
	void initMultiplier(Mul& m);

	//获得加成时更新加成列表
	void renewMultiplier(Mul* m, string s, double v, int r);

	//更新单个列表，给下面的函数用，一般不直接调用此函数
	void checkSingleMultiplier(Mul* m);

	//回合结束时更新加成列表
	void checkMultiplier();

	//对加成列表求和得到单项总加成
	double getSum(Mul* m);

	//对加成列表求累乘得到单项总加成，只适用于finmul项！
	double getMul(Mul* m);
};

//BaseStats是所有创建的角色共用的基础属性、面板属性等父类

class Stats:public GameObject
{
public:

	Stats();
	Stats(const std::wstring& name);
	~Stats();

	bool isAlive = true;

	const std::wstring _wname;	//名字
	char _name[20];				//char类型的名字也要，方便显示名字
	string _actiontext;
	Rect _range;//矩形
	bool _haveSkill= false;

	//op1统一为队友，op2为主要目标，op3为次要目标
	virtual void normalAttack(Stats* op1, Stats* op2, Stats* op3);
	virtual void Skill(Stats* op1, Stats* op2, Stats* op3);
	void showActionText();
	void changeRound();

	//基础属性
	double bs_hp;	//生命值
	double bs_hpl;	//生命上限
	double bs_atk;	//攻击力
	double bs_def;	//防御力
	double bs_roa;	//法术抗性
	double bs_spd;	//速度

	//伤害类型
	int k;			//1为物理，2为法术，3为真实，4为治疗

	//属性增减
	Multiplier mp_hp;
	Multiplier mp_hpl;
	Multiplier mp_atk;
	Multiplier mp_def;
	Multiplier mp_roa;
	Multiplier mp_spd;

	//面板属性
	double fi_hp;
	double fi_hpl;
	double fi_atk;
	double fi_def;
	double fi_roa;
	double fi_spd;

	//位置，暂时还用不到
	//int posi;

	//回合数
	int round = 1;

	//角色位置
	int x, y;

	//设置目标名字
	void setTargetName(string s);

	//设置伤害类型
	void setDamageKind(int k0);

	//对基础属性进行修正显示
	double getFinalStats(double bs,Multiplier& mp);

	//设置目标基础属性
	void setTargetBaseStats(double hpl0, double atk0, double def0, double roa0, double spd0);

	//打印目标基础属性
	void showTargetBaseStats();												

	////打印目标面板属性
	void showTargetFinalStats();

	virtual void Draw();

	void SetRange(Rect range);
};
