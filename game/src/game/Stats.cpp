#include "../../inc/game/Stats.h"

Multiplier::Multiplier()
{
	//cout << "Multiplier构造" << endl;
	for (int i = 0; i < 20; i++)
	{
		initMultiplier(preadd[i]);
		initMultiplier(premul[i]);
		initMultiplier(diradd[i]);
		initMultiplier(dirmul[i]);
		initMultiplier(finadd[i]);
		initMultiplier(finmul[i]);
	}
}

Multiplier::~Multiplier()
{
	delete[] preadd;
	delete[] premul;
	delete[] diradd;
	delete[] dirmul;
	delete[] finadd;
	delete[]  finmul;
	//cout << "Multiplier析构" << endl;
}

void Multiplier::initMultiplier(Mul& m)
{
	m.round = -1; m.sign = "default"; m.value = 0;
}

void Multiplier::renewMultiplier(Mul* m, string s, double v, int r)
{
	printf("=== renewMultiplier called: s=%s, v=%.1f, r=%d ===\n", s.c_str(), v, r);

	// 1. 查找同名
	for (int i = 0; i < 20; i++)
	{
		if (m[i].sign == s)
		{
			// 同名加成不叠加：数值取最高值，剩余回合取较大值。
			if (m[i].value < v)
				m[i].value = v;
			if (m[i].round < r)
				m[i].round = r;
			return;
		}
	}

	// 2. 找空位
	for (int i = 0; i < 20; i++)
	{
		if (m[i].sign == "default" && m[i].round == -1)
		{
			printf("=== Writing to diradd[%d]: s=%s, v=%.1f, r=%d ===\n", i, s.c_str(), v, r);
			m[i].sign = s;
			m[i].value = v;
			m[i].round = r;
			return;
		}
	}

	printf("=== ERROR: No available slot in diradd! ===\n");
}

void Multiplier::checkSingleMultiplier(Mul* m)
{
	for (int i = 0; i < 20; i++)
	{
		if (m[i].round >= 0)
		{
			m[i].round--;
			if (m[i].round == -1)
			{
				m[i].sign = "default";
				m[i].value = 0;
			}
		}
	}
}

void Multiplier::checkMultiplier()
{
	checkSingleMultiplier(preadd);
	checkSingleMultiplier(premul);
	checkSingleMultiplier(diradd);
	checkSingleMultiplier(dirmul);
	checkSingleMultiplier(finadd);
	checkSingleMultiplier(finmul);
}

double Multiplier::getSum(Mul* m)
{
	double sum = 0;
	for (int i = 0; i < 20; i++)
	{
		if (m[i].round >= 0)
			sum += m[i].value;
	}
	return sum;
}

double Multiplier::getMul(Mul* m)
{
	double mul = 1;
	for (int i = 0; i < 20; i++)
	{
		if (m[i].round >= 0)
			mul *= m[i].value;
	}
	return mul;
}

Stats::Stats()
{
	//cout << "BaseStats构造" << endl;
	bs_hp = 0; bs_hpl = 0; bs_atk = 0; bs_def = 0; bs_roa = 0; bs_spd = 0;
	fi_hp = 0; fi_hpl = 0; fi_atk = 0; fi_def = 0; fi_roa = 0; fi_spd = 0;
	k = 1;	//伤害类型默认为物理
	//round = 0;
}

Stats::Stats( const std::wstring& name):_wname(name)
{
	//cout << "BaseStats构造" << endl;
	bs_hp = 0; bs_hpl = 0; bs_atk = 0; bs_def = 0; bs_roa = 0; bs_spd = 0;
	fi_hp = 0; fi_hpl = 0; fi_atk = 0; fi_def = 0; fi_roa = 0; fi_spd = 0;
	k = 1;	//伤害类型默认为物理
	//round = 0;
}

Stats::~Stats()
{
	//cout << "BaseStats析构" << endl;
}

//计算公式：面板数值=（（基础数值+前置加算提升）*前置乘算提升+直接加算提升）*（1+直接乘算提升）
/*例如：角色攻击力1000，场地效果：提升20%攻击力，队友效果：提供100攻击力加成，角色自身技能：攻击力+100%
则角色面板攻击力为（（1000+0）*（1+20%）+100）*（1+100%）=2600*/
double Stats::getFinalStats(double bs, Multiplier& mp)
{
	double pa = mp.getSum(mp.preadd);
	double pm = mp.getSum(mp.premul) + 1;
	double da = mp.getSum(mp.diradd);
	double dm = mp.getSum(mp.dirmul);
	return ((bs + pa) * pm + da) * (1 + dm);
}

//基础属性数值设置完毕后面板属性会一同设置
void Stats::setTargetBaseStats(double hpl0=100, double atk0=100, double def0=100, double roa0=10,double spd0=90)
{
	bs_hpl = hpl0; bs_atk = atk0; bs_def = def0; bs_roa = roa0; bs_spd = spd0;
	bs_hp = bs_hpl;
	fi_hp = getFinalStats(bs_hp, mp_hp);
	fi_hpl = getFinalStats(bs_hpl, mp_hpl);
	fi_atk = getFinalStats(bs_atk, mp_atk);
	fi_def = getFinalStats(bs_def, mp_def);
	fi_roa = getFinalStats(bs_roa, mp_roa);
	fi_spd = getFinalStats(bs_spd, mp_spd);
}


void Stats::setDamageKind(int k0)
{
	k = k0;
}

//显示的基础属性取整，实际上不是整数
void Stats::showTargetBaseStats()
{
	//cout << "name:" << _name << endl;
	//cout << "base hp:" << (int)bs_hp << endl;
	//cout << "base hpl:" << (int)bs_hpl << endl;
	//cout << "base atk:" << (int)bs_atk << endl;
	//cout << "base def:" << (int)bs_def << endl;
	//cout << "base roa:" << (int)bs_roa << endl;
	//cout << "base roa:" << (int)bs_spd << endl;
	//cout << endl;
}

void Stats::showTargetFinalStats()
{
//	//cout << "name:" << _name << endl;
//	//cout << "final hp:" << (int)fi_hp << endl;
//	//cout << "final hpl:" << (int)fi_hpl << endl;
//	//cout << "final atk:" << (int)fi_atk << endl;
//	//cout << "final def:" << (int)fi_def << endl;
//	//cout << "final roa:" << (int)fi_roa << endl;
//	//cout << "final roa:" << (int)fi_spd << endl;
//	//cout << endl;
}

void Stats::Draw()
{
}

void Stats::SetRange(Rect range)
{
	_range = range;
}

void Stats::normalAttack(Stats* op1 = nullptr, Stats* op2 = nullptr, Stats* op3 = nullptr){}
void Stats::Skill(Stats* op1 = nullptr, Stats* op2 = nullptr, Stats* op3 = nullptr){}

void Stats::showActionText()
{
	char text[50];
	TCHAR Ttext[100];
	_actiontext.copy(text, _actiontext.length(), 0);
	*(text + _actiontext.length()) = '\0';
	MultiByteToWideChar(CP_ACP, 0, text, -1, Ttext, 100);
	outtextxy(400, 450, Ttext);
}

void Stats::changeRound()
{
	round += 1;
	mp_atk.checkMultiplier();
	fi_atk = getFinalStats(bs_atk, mp_atk);
	mp_hpl.checkMultiplier();
	fi_hpl = getFinalStats(bs_hpl, mp_hpl);
	mp_def.checkMultiplier();
	fi_def = getFinalStats(bs_def, mp_def);
	mp_roa.checkMultiplier();
	fi_roa = getFinalStats(bs_roa, mp_roa);
}
