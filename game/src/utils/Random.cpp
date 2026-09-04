#include"../../inc/utils/Random.h"
#include<cstdlib>
#include<ctime>

//为了生成随机数
void SetRandomSeed()
{
	srand((unsigned)time(nullptr));
}

//获取一个[0.0,1.0]的随机数
double Random()
{
	return (double)rand() / (double)RAND_MAX;
}

//upper：上限，lower：下限
//[0.0,upper]
double Random(double upper)
{
	return upper * Random();
}

//[lower,upper]
double Random(double lower, double upper)
{
	return lower + (upper - lower) * Random();
}

//[0,upper)因为是求余所以右边为开区间
int Random(int upper)
{
	return rand() % upper;
}

//[lower,upper)
bool Random(int lower, int upper)
{
	if (upper <= lower)
	{
		return lower;
	}
	if (lower + rand() % (upper - lower))
	{
		return true;
	}
	else
	{
		return false;
	}
}