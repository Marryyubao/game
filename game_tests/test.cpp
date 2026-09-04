#include "pch.h"
#include "../game/inc/game/Stats.h"
#include "../game/inc/game/Figure.h"
#include "../game/inc/ui/Interface.h"
#if defined(_MSC_VER) && defined(_DEBUG)
#include <crtdbg.h>
#endif

class DamageTest : public ::testing::Test
{
protected:
    S0 physical{ L"Physical" };
    S2 arts{ L"Arts" };
    Stats primary{ L"Primary" };
    Stats secondary{ L"Secondary" };

    void SetUp() override
    {
        // Control the panel attack; final damage still goes through Figure.cpp.
        physical.fi_atk = 100.0;
        arts.fi_atk = 100.0;
        primary.setTargetBaseStats(1000.0, 0.0, 30.0, 20.0, 90.0);
        secondary.setTargetBaseStats(1000.0, 0.0, 900.0, 50.0, 90.0);
    }
};

TEST_F(DamageTest, PhysicalDamageNormal)
{
    physical.normalAttack(nullptr, &primary, nullptr);
    EXPECT_DOUBLE_EQ(primary.fi_hp, 930.0);
}

TEST_F(DamageTest, PhysicalDamageMinimum)
{
    primary.fi_def = 200.0;
    physical.normalAttack(nullptr, &primary, nullptr);
    EXPECT_DOUBLE_EQ(primary.fi_hp, 995.0);
}

TEST_F(DamageTest, ArtDamageNormal)
{
    arts.normalAttack(nullptr, &primary, &secondary);
    EXPECT_DOUBLE_EQ(primary.fi_hp, 920.0);
    EXPECT_DOUBLE_EQ(secondary.fi_hp, 950.0);
}

TEST_F(DamageTest, ArtDamageMinimum)
{
    primary.fi_roa = 95.0;
    secondary.fi_roa = 100.0;
    arts.normalAttack(nullptr, &primary, &secondary);
    EXPECT_DOUBLE_EQ(primary.fi_hp, 995.0);
    EXPECT_DOUBLE_EQ(secondary.fi_hp, 995.0);
}

TEST_F(DamageTest, LethalDamageStopsAtZeroHealth)
{
    primary.fi_hp = 10.0;
    secondary.fi_hp = 10.0;
    physical.normalAttack(nullptr, &primary, nullptr);
    arts.normalAttack(nullptr, &primary, &secondary);
    EXPECT_DOUBLE_EQ(primary.fi_hp, 0.0);
    EXPECT_DOUBLE_EQ(secondary.fi_hp, 0.0);
}

TEST_F(DamageTest, ZeroAttackDoesNotDamageTargets)
{
    physical.fi_atk = 0.0;
    arts.fi_atk = 0.0;
    physical.normalAttack(nullptr, &primary, nullptr);
    arts.normalAttack(nullptr, &primary, &secondary);
    EXPECT_DOUBLE_EQ(primary.fi_hp, 1000.0);
    EXPECT_DOUBLE_EQ(secondary.fi_hp, 1000.0);
}

TEST_F(DamageTest, AttackUsesFinalBuffsAfterEarlierBuffsExpire)
{
    physical.mp_atk.renewMultiplier(physical.mp_atk.finadd, "short_add", 10.0, 0);
    physical.mp_atk.renewMultiplier(physical.mp_atk.finadd, "long_add", 20.0, 2);
    physical.mp_atk.renewMultiplier(physical.mp_atk.finmul, "short_mul", 100.0, 0);
    physical.mp_atk.renewMultiplier(physical.mp_atk.finmul, "long_mul", 2.0, 2);
    physical.mp_atk.checkMultiplier();

    physical.normalAttack(nullptr, &primary, nullptr);
    EXPECT_DOUBLE_EQ(primary.fi_hp, 790.0);
}

TEST(StatsTest, CreateCharacter)
{
    S0 warrior(L"战士");
    EXPECT_TRUE(warrior.isAlive);
}

TEST(MultiplierTest, AddBuffThenExpire)
{
    Multiplier mp;
    mp.renewMultiplier(mp.diradd, "test_buff", 20.0, 2);

    // 初始：加成生效
    double sum = mp.getSum(mp.diradd);
    EXPECT_DOUBLE_EQ(sum, 20.0);

    // 第 1 回合：仍然生效（round: 2 -> 1）
    mp.checkMultiplier();
    sum = mp.getSum(mp.diradd);
    EXPECT_DOUBLE_EQ(sum, 20.0);

    // 第 2 回合：仍然生效（round: 1 -> 0）
    mp.checkMultiplier();
    sum = mp.getSum(mp.diradd);
    EXPECT_DOUBLE_EQ(sum, 20.0);

    // 第 3 回合：过期！（round: 0 -> -1）
    mp.checkMultiplier();
    sum = mp.getSum(mp.diradd);
    EXPECT_DOUBLE_EQ(sum, 0.0);
}

TEST(MultiplierTest, EmptyListsHaveNeutralValues)
{
    Multiplier mp;
    EXPECT_DOUBLE_EQ(mp.getSum(mp.preadd), 0.0);
    EXPECT_DOUBLE_EQ(mp.getSum(mp.premul), 0.0);
    EXPECT_DOUBLE_EQ(mp.getSum(mp.diradd), 0.0);
    EXPECT_DOUBLE_EQ(mp.getSum(mp.dirmul), 0.0);
    EXPECT_DOUBLE_EQ(mp.getSum(mp.finadd), 0.0);
    EXPECT_DOUBLE_EQ(mp.getMul(mp.finmul), 1.0);
}

TEST(MultiplierTest, SumIncludesBuffAfterFirstSlotExpires)
{
    Multiplier mp;
    mp.renewMultiplier(mp.diradd, "short", 10.0, 0);
    mp.renewMultiplier(mp.diradd, "long", 20.0, 2);
    mp.checkMultiplier();
    EXPECT_DOUBLE_EQ(mp.getSum(mp.diradd), 20.0);
}

TEST(MultiplierTest, SumIncludesBuffAfterMiddleSlotExpires)
{
    Multiplier mp;
    mp.renewMultiplier(mp.diradd, "first", 10.0, 2);
    mp.renewMultiplier(mp.diradd, "middle", 100.0, 0);
    mp.renewMultiplier(mp.diradd, "last", 20.0, 2);
    mp.checkMultiplier();
    EXPECT_DOUBLE_EQ(mp.getSum(mp.diradd), 30.0);
}

TEST(MultiplierTest, ProductIncludesBuffAfterFirstSlotExpires)
{
    Multiplier mp;
    mp.renewMultiplier(mp.finmul, "short", 2.0, 0);
    mp.renewMultiplier(mp.finmul, "long", 1.5, 2);
    mp.checkMultiplier();
    EXPECT_DOUBLE_EQ(mp.getMul(mp.finmul), 1.5);
}

TEST(MultiplierTest, ProductIncludesBuffAfterMiddleSlotExpires)
{
    Multiplier mp;
    mp.renewMultiplier(mp.finmul, "first", 2.0, 2);
    mp.renewMultiplier(mp.finmul, "middle", 100.0, 0);
    mp.renewMultiplier(mp.finmul, "last", 1.5, 2);
    mp.checkMultiplier();
    EXPECT_DOUBLE_EQ(mp.getMul(mp.finmul), 3.0);
}

TEST(MultiplierTest, AggregatesIncludeLastSlotAfterAllEarlierSlotsExpire)
{
    Multiplier mp;
    for (int i = 0; i < 20; ++i)
    {
        const string name = "buff_" + std::to_string(i);
        const int rounds = i == 19 ? 2 : 0;
        mp.renewMultiplier(mp.diradd, name, 10.0, rounds);
        mp.renewMultiplier(mp.finmul, name, 2.0, rounds);
    }
    mp.checkMultiplier();
    EXPECT_DOUBLE_EQ(mp.getSum(mp.diradd), 10.0);
    EXPECT_DOUBLE_EQ(mp.getMul(mp.finmul), 2.0);
}

TEST(MultiplierTest, ReapplyKeepsHighestValueAndLongestDurationWithoutStacking)
{
    Multiplier mp;
    mp.renewMultiplier(mp.diradd, "buff", 20.0, 2);
    mp.checkMultiplier();
    mp.renewMultiplier(mp.diradd, "buff", 40.0, 3);
    mp.renewMultiplier(mp.diradd, "buff", 10.0, 1);

    EXPECT_DOUBLE_EQ(mp.getSum(mp.diradd), 40.0);
    EXPECT_EQ(mp.diradd[0].round, 3);
    int activeCount = 0;
    for (int i = 0; i < 20; ++i)
        if (mp.diradd[i].round >= 0) ++activeCount;
    EXPECT_EQ(activeCount, 1);
}

TEST(MultiplierTest, ReapplySameValueRefreshesExpiry)
{
    Multiplier mp;
    mp.renewMultiplier(mp.diradd, "buff", 20.0, 2);
    mp.checkMultiplier();
    mp.checkMultiplier();
    mp.renewMultiplier(mp.diradd, "buff", 20.0, 2);

    mp.checkMultiplier();
    mp.checkMultiplier();
    EXPECT_DOUBLE_EQ(mp.getSum(mp.diradd), 20.0);
    mp.checkMultiplier();
    EXPECT_DOUBLE_EQ(mp.getSum(mp.diradd), 0.0);
}

TEST(MultiplierTest, StrongerShorterBuffDoesNotShortenRemainingDuration)
{
    Multiplier mp;
    mp.renewMultiplier(mp.diradd, "buff", 20.0, 5);
    mp.renewMultiplier(mp.diradd, "buff", 40.0, 1);
    EXPECT_DOUBLE_EQ(mp.getSum(mp.diradd), 40.0);
    EXPECT_EQ(mp.diradd[0].round, 5);
}

TEST(MultiplierTest, WeakerLongerBuffRefreshesWithoutLoweringValue)
{
    Multiplier mp;
    mp.renewMultiplier(mp.finmul, "buff", 2.0, 1);
    mp.renewMultiplier(mp.finmul, "buff", 1.5, 3);
    EXPECT_DOUBLE_EQ(mp.getMul(mp.finmul), 2.0);
    EXPECT_EQ(mp.finmul[0].round, 3);
}

TEST(MultiplierTest, ExpiredBuffSlotCanBeReused)
{
    Multiplier mp;
    mp.renewMultiplier(mp.diradd, "buff", 20.0, 0);
    mp.checkMultiplier();
    mp.renewMultiplier(mp.diradd, "buff", 40.0, 2);
    EXPECT_DOUBLE_EQ(mp.getSum(mp.diradd), 40.0);
    EXPECT_EQ(mp.diradd[0].round, 2);
}

TEST(MultiplierTest, FullListCanRefreshExistingBuff)
{
    Multiplier mp;
    for (int i = 0; i < 20; ++i)
        mp.renewMultiplier(mp.diradd, "buff_" + std::to_string(i), 1.0, 2);
    mp.renewMultiplier(mp.diradd, "buff_19", 5.0, 4);
    EXPECT_DOUBLE_EQ(mp.getSum(mp.diradd), 24.0);
    EXPECT_EQ(mp.diradd[19].round, 4);
}

TEST(StatsTest, PanelStatsCombineBuffsAndReturnToBaseAfterExpiry)
{
    Stats character(L"Test");
    character.setTargetBaseStats(1000.0, 100.0, 30.0, 20.0, 90.0);
    character.mp_atk.renewMultiplier(character.mp_atk.preadd, "pre_add", 10.0, 2);
    character.mp_atk.renewMultiplier(character.mp_atk.premul, "pre_mul", 0.2, 2);
    character.mp_atk.renewMultiplier(character.mp_atk.diradd, "direct_add", 20.0, 2);
    character.mp_atk.renewMultiplier(character.mp_atk.dirmul, "direct_mul", 0.5, 2);

    character.changeRound();
    EXPECT_DOUBLE_EQ(character.fi_atk, 228.0);
    character.changeRound();
    EXPECT_DOUBLE_EQ(character.fi_atk, 228.0);
    character.changeRound();
    EXPECT_DOUBLE_EQ(character.fi_atk, 100.0);
}

TEST(StatsTest, ReusingS0SkillExtendsActualAttackBuff)
{
    S0 attacker(L"Test");
    // Let the initial talent expire before choosing a controlled base attack.
    for (int i = 0; i < 3; ++i) attacker.changeRound();
    attacker.setTargetBaseStats(2000.0, 100.0, 0.0, 0.0, 90.0);
    Stats target(L"Target");
    target.setTargetBaseStats(2000.0, 0.0, 0.0, 0.0, 90.0);

    attacker.Skill(nullptr, nullptr, nullptr);
    attacker.changeRound();
    attacker.changeRound();
    attacker.Skill(nullptr, nullptr, nullptr);
    attacker.changeRound();
    attacker.normalAttack(nullptr, &target, nullptr);
    EXPECT_DOUBLE_EQ(target.fi_hp, 1800.0);
}

#if defined(_MSC_VER) && defined(_DEBUG)
TEST(PickFigureInterfaceTest, DestructionReleasesAllButtons)
{
    _CrtMemState before;
    _CrtMemState after;
    _CrtMemCheckpoint(&before);
    for (int i = 0; i < 5; ++i)
    {
        // Do not enter a match: this test isolates the screen's owned buttons.
        PickFigureInterface screen;
    }
    _CrtMemCheckpoint(&after);
    EXPECT_EQ(before.lCounts[_NORMAL_BLOCK], after.lCounts[_NORMAL_BLOCK]);
    EXPECT_EQ(before.lSizes[_NORMAL_BLOCK], after.lSizes[_NORMAL_BLOCK]);
}
#endif
