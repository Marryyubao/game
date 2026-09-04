#include "../../inc/game/Figure.h"
#include "../../inc/Globals.h"

//由面板数值修正得到最终数值
/*例如：角色面板攻击力2600，技能：造成相当于攻击力150% 的伤害，
则在忽略敌方的防御力和法抗后的技能伤害为：（2600+0）*150%=3900*/
static double dataFix(double fi_data,Multiplier& mp)
{
	double fa = mp.getSum(mp.finadd);
	double fm = mp.getMul(mp.finmul);
	return (fi_data + fa) * fm;
}

//物理伤害结算
static double getPhysicDmg(double atk, double def)
{
	if (atk - def > atk * 0.05)
		return atk - def;	//一般情况下：物理伤害=物理攻击力-对方防御力
	else
		return atk * 0.05;	//当对方防御力过高时，结算保底伤害（5%）
}

//法术伤害结算
static double getArtDmg(double atk, double roa)
{
	if (atk * (100 - roa) / 100 > atk * 0.05)
		return atk * (100 - roa) / 100;	//一般情况下：法术伤害=法术攻击力*（100-对方法抗）/100
	else
		return atk * 0.05;	//当对方法抗过高时，结算保底伤害（5%）
}

//防止一些属性出现负数的修正函数
static double lowerLimitFix(double x)
{
	if (x < 0)
		return 0;
	else
		return x;
}

//防止一些属性超过上限的修正函数
static double upperLimitFix(double x, double y)
{
	if (x < y)
		return x;
	else
		return y;
}

//通用平A模板
static void normalAttackModule(Stats& c1, Stats& c2)
{
	double dmg=0;
	double atk1 = dataFix(c1.fi_atk, c1.mp_atk);
	double def2 = dataFix(c2.fi_def, c2.mp_def);
	double roa2 = dataFix(c2.fi_roa, c2.mp_roa);
	if (c1.k == 1)	//物理攻击
	{
		dmg = getPhysicDmg(atk1, def2);
		c2.fi_hp -= getPhysicDmg(atk1, def2);
		c2.fi_hp = lowerLimitFix(c2.fi_hp);
	}
	else if (c1.k == 2)	//法术攻击
	{
		dmg = getArtDmg(atk1, roa2);
		c2.fi_hp -= getArtDmg(atk1, roa2);
		c2.fi_hp = lowerLimitFix(c2.fi_hp);
	}
	else if (c1.k == 3)	//真实攻击
	{
		dmg = c1.fi_atk;
		c2.fi_hp -= c1.fi_atk;
		c2.fi_hp = lowerLimitFix(c2.fi_hp);
	}
	else if (c1.k == 4)	//治疗
	{
		if (!c2.isAlive)
			return;
		dmg = c1.fi_atk;
		c2.fi_hp += c1.fi_atk;
		c2.fi_hp = upperLimitFix(c2.fi_hp,c2.fi_hpl);
	}
}

S0::S0(const std::wstring& name):Stats(name)
{
	string str = "S0";
	str.copy(_name, 2, 0);
	*(_name + 2) = '\0';
	_haveSkill = true;
	setTargetBaseStats(2565, 535, 410, 0, 90);
	double boost = 0.2 * bs_atk;
	//天赋：初始获得20%基础攻击力提升，持续2回合
	mp_atk.renewMultiplier(mp_atk.diradd, "talentS0", boost, 2);
	fi_atk = getFinalStats(bs_atk, mp_atk);
}

void S0::normalAttack(Stats* op1, Stats* op2, Stats* op3)
{
	if (1)
	{
		normalAttackModule(*this, *op2);
		_actiontext = "S0 attacked!";
	}
}

void S0::Skill(Stats* op1, Stats* op2, Stats* op3)	//攻击时攻击力提高100%，持续2回合
{
	if (1)
	{
		mp_atk.renewMultiplier(mp_atk.finmul, "skillS0", 2.0, 2);
		fi_atk = getFinalStats(bs_atk, mp_atk);
		_actiontext = "S0 used skill!";
	}
}

void S0::Draw()
{
	putimage(x, y, &I0);
}

S1::S1(const std::wstring& name) :Stats(name)
{
	string str = "S1";
	str.copy(_name, 2, 0);
	*(_name + 2) = '\0';
	_haveSkill = true;
	setTargetBaseStats(3205, 430, 890, 10, 100);
}

void S1::normalAttack(Stats* op1, Stats* op2, Stats* op3)	//攻击时攻击力提高自身防御力的5%
{
	if (1)
	{
		op2->fi_hp -= getPhysicDmg(this->fi_atk * (1 + this->fi_def * 0.0015), op2->fi_def);
		op2->fi_hp = lowerLimitFix(op2->fi_hp);
		_actiontext = "S1 attacked!";
	}
}

void S1::Skill(Stats* op1, Stats* op2, Stats* op3)	//自身防御力提高100%，队友防御力提高200，持续1回合
{
	if (1)
	{
		mp_def.renewMultiplier(mp_def.dirmul, "skillS1", 1.0, 1);
		fi_def = getFinalStats(bs_def, mp_def);
		op1->mp_def.renewMultiplier(op1->mp_def.diradd, "skillfromS1", 200, 1);
		op1->fi_atk = getFinalStats(op1->bs_def, op1->mp_def);
		_actiontext = "S1 used skill!";
	}
}

void S1::Draw()
{
	putimage(x, y, &I1);
}

S2::S2(const std::wstring& name) :Stats(name)
{
	string str = "S2";
	str.copy(_name, 2, 0);
	*(_name + 2) = '\0';
	//_haveSkill = true;
	setTargetBaseStats(1755, 535, 195, 20, 100);
	k = 2;	//攻击造成法术伤害
}

void S2::normalAttack(Stats* op1, Stats* op2, Stats* op3)
{
	if (1)
	{
		normalAttackModule(*this, *op2);
		normalAttackModule(*this, *op3);
		_actiontext = "S2 attacked!";
	}
}

void S2::Skill(Stats* op1, Stats* op2, Stats* op3)
{
	op2->_haveSkill = false;
	op2->mp_atk.renewMultiplier(op2->mp_atk.finmul, "Weak", -0.5, 2);
	op2->fi_atk = getFinalStats(op2->bs_atk, op2->mp_atk);
	op2->fi_hp -= getArtDmg(this->fi_atk * 0.5, op2->fi_def);
	op2->fi_hp = lowerLimitFix(op2->fi_hp);
	_actiontext = "S2 used skill!";
}

void S2::Draw()
{
	putimage(x, y, &I2);
}

S3::S3(const std::wstring& name) :Stats(name)
{
	string str = "S3";
	str.copy(_name, 2, 0);
	*(_name + 2) = '\0';
	setTargetBaseStats(1925, 997, 125, 25, 100);
	k = 2;	//攻击造成法术伤害
}

void S3::normalAttack(Stats* op1, Stats* op2, Stats* op3)
{
	if (1)
	{
		k = 2;
		double temp = op2->fi_hp;
		normalAttackModule(*this, *op2);
		double dmg = temp - op2->fi_hp;
		k = 4;
		fi_hp += dmg * 0.75;
		fi_hp = upperLimitFix(fi_hp, fi_hpl);
		if(op1->isAlive)
		{
			op1->fi_hp += dmg * 0.5;
			op1->fi_hp = upperLimitFix(op1->fi_hp, op1->fi_hpl);
		}
		_actiontext = "S3 attacked!";
	}
}

void S3::Skill(Stats* op1, Stats* op2, Stats* op3)
{
	fi_hpl = upperLimitFix(fi_hpl * 1.3, bs_hpl * 1.5);
	op1->fi_hpl = upperLimitFix(op1->fi_hpl * 1.3, op1->bs_hpl * 1.5);
	_actiontext = "S3 used skill!";
}

void S3::Draw()
{
	putimage(x, y, &I3);
}
