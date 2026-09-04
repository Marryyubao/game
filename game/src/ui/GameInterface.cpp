#include"../../inc/ui/Interface.h"
#include"../../inc/utils/Random.h"
#include<cstdio>
#include<Windows.h>
#include<easyx.h>

//static int round_text = 0;

static TCHAR* TransferToTC(double stats)
{
	char str[20];
	TCHAR* Tstr = new TCHAR[40];
	sprintf_s(str, "%.2f", stats);
	MultiByteToWideChar(CP_ACP, 0, str, -1, Tstr, 100);
	return Tstr;
}

static TCHAR* TransferToTC(int stats)
{
	char str[20];
	TCHAR* Tstr = new TCHAR[40];
	sprintf_s(str, "%d", stats);
	MultiByteToWideChar(CP_ACP, 0, str, -1, Tstr, 100);
	return Tstr;
}

GameInterface::GameInterface() :Interface(L"Game")
{
	Application* app = GetApplication();
	//init turn and 标记
	app->_turn = Random(0, 2);
	app->_FirstDown = false;

	//init Button
	if (!app->_turn)//按钮画在左边
	{
		_pPlayerAttackButton = new Button(Rect(50, 500, 45, 45), L"Attack");
		_pPlayerSkillButton = new Button(Rect(150, 500, 45, 45), L"Skill");
	}
	else//画在右边
	{
		_pPlayerAttackButton = new Button(Rect(805, 500, 45, 45), L"Attack");
		_pPlayerSkillButton = new Button(Rect(905, 500, 45, 45), L"Skill");
	}
	_pPlayerAttackButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickAttackButton);
	_pPlayerSkillButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickSkillButton);

	_pSelectButton1 = new Button(Rect(250, 500, 60, 45), L"Target 1");
	_pSelectButton1->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickSelectButton1);
	_pSelectButton2 = new Button(Rect(705, 500, 60, 45), L"Target 1");
	_pSelectButton2->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickSelectButton2);
}
GameInterface::~GameInterface()
{
	if (_pPlayerAttackButton)
	{
		delete _pPlayerAttackButton;//先删空间
		_pPlayerAttackButton = nullptr;//再指针置空
	}
	if (_pPlayerSkillButton)
	{
		delete _pPlayerSkillButton;//先删空间
		_pPlayerSkillButton = nullptr;//再指针置空
	}
	if (_pSelectButton1)
	{
		delete _pSelectButton1;
		_pSelectButton1 = nullptr;
	}
	if (_pSelectButton2)
	{
		delete _pSelectButton2;
		_pSelectButton2 = nullptr;
	}
}

void GameInterface::OnEnter()
{
	Application* app = GetApplication();

	//init Player Target
	app->_LeftPlayerTarget = app->_Player[1]->_TeamMemberOne;
	app->_RightPlayerTarget = app->_Player[0]->_TeamMemberOne;

	//init Figure
	/*app->_Player[0]->_TeamMemberOne->SetRange(Rect(50, 95, 100, 175));
	app->_Player[0]->_TeamMemberTwo->SetRange(Rect(150,305, 100, 175));*/
	app->_Player[0]->_TeamMemberOne->x = 50; app->_Player[0]->_TeamMemberOne->y = 95;
	app->_Player[0]->_TeamMemberTwo->x = 150; app->_Player[0]->_TeamMemberTwo->y = 305;

	/*app->_Player[1]->_TeamMemberOne->SetRange(Rect(850, 95, 100, 175));
	app->_Player[1]->_TeamMemberTwo->SetRange(Rect(750, 305, 100, 175));*/
	app->_Player[1]->_TeamMemberOne->x = 850; app->_Player[1]->_TeamMemberOne->y = 95;
	app->_Player[1]->_TeamMemberTwo->x = 750; app->_Player[1]->_TeamMemberTwo->y = 305;
}
void GameInterface::OnExit(){}

void GameInterface::Update()
{
	Application* app = GetApplication();
	if (IsKeyDown(VK_ESCAPE))
	{
		GetApplication()->ChangeInterface(L"Main");
	}

	if (gameMode == DOUBLE_PLAYER)
	{
		DoublePlayerUpdate();
	}
	else
	{
		SinglePlayerUpdate();
	}

	pJudgeMemberDown();
	JudgeWinner();
}

void GameInterface::Draw()
{
	Application* app = GetApplication();
	//State display
	setlinecolor(BLACK);

	/*putimage(0, 0, &icyslime);*/
	RECT rect3{ 450,0,550,50 };
	rectangle(rect3.left, rect3.top, rect3.right, rect3.bottom);
	drawtext(L"Round", &rect3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	outtextxy(497, 32, TransferToTC(app->round / 2));

	RECT rect2{ 350,400,650,560 };
	rectangle(rect2.left, rect2.top, rect2.right, rect2.bottom);
	for (int i = 0; i < 4; i++)
	{
		if (app->_ShowActionText[i] == 1)
		{
			switch (i)
			{
			case 0:app->_Player[0]->_TeamMemberOne->showActionText(); break;
			case 1:app->_Player[0]->_TeamMemberTwo->showActionText(); break;
			case 2:app->_Player[1]->_TeamMemberOne->showActionText(); break;
			case 3:app->_Player[1]->_TeamMemberTwo->showActionText(); break;
			}
		}
	}



	//palyer name
	setlinecolor(LIGHTCYAN);
	line(0, 50, 100, 50);
	line(900, 50, 1000, 50);
	LOGFONT style;
	gettextstyle(&style);
	settextstyle(22, 0, L"Consolas");
	RECT rect0{ 0,0,100,50 };
	RECT rect1{ 900,0,1000,50 };
	
	if (gameMode == SINGLE_PLAYER)
	{
		drawtext(L"Player", &rect0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(L"Ai", &rect1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (gameMode == DOUBLE_PLAYER)
	{
		drawtext(L"Player1", &rect0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(L"Player2", &rect1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	
	ShowHPAndName(); 


	//restore text style
	settextstyle(&style);

	app->_Player[0]->_TeamMemberOne->Draw();
	app->_Player[0]->_TeamMemberTwo->Draw();
	app->_Player[1]->_TeamMemberOne->Draw();
	app->_Player[1]->_TeamMemberTwo->Draw();

	_pPlayerAttackButton->Draw();
	IfHaveSkill();
	if (app->_DrawSkill)
	{
		_pPlayerSkillButton->Draw();
	}
	if (gameMode == DOUBLE_PLAYER)
	{
		if (!app->_turn)
		{
			_pSelectButton1->Draw();
		}
		else
		{
			_pSelectButton2->Draw();
		}
	}
	else
	{
		_pSelectButton1->Draw();
	}

}

void GameInterface::_OnClickAttackButton()//点击后需要执行的函数
{
	Application* app = GetApplication();
	Stats* LF = app->_Player[0]->_TeamMemberOne;
	Stats* LL = app->_Player[0]->_TeamMemberTwo;
	Stats* RF = app->_Player[1]->_TeamMemberOne;
	Stats* RL = app->_Player[1]->_TeamMemberTwo;
	if (!app->_turn)
	{
		if (LF->isAlive && !LL->isAlive)
		{
			LF->normalAttack(LL, app->_LeftPlayerTarget, app->_LeftOtherTarget);
			app->RenewActionText(0);
			app->_turn = !app->_turn; app->round++;
			RF->changeRound(); RL->changeRound();
			app->_FirstDown = false;
		}
		if (!LF->isAlive && LL->isAlive)
		{
			LL->normalAttack(LF, app->_LeftPlayerTarget, app->_LeftOtherTarget);
			app->RenewActionText(1);
			app->_turn = !app->_turn; app->round++;
			RF->changeRound(); RL->changeRound();
			app->_FirstDown = false;
		}
		if (!app->_FirstDown && LF->isAlive && LL->isAlive)
		{
			LF->normalAttack(LL, app->_LeftPlayerTarget, app->_LeftOtherTarget);
			app->RenewActionText(0);
			app->_FirstDown = true;
		}
		else if (app->_FirstDown && LF->isAlive && LL->isAlive)
		{
			LL->normalAttack(LF, app->_LeftPlayerTarget, app->_LeftOtherTarget);
			app->RenewActionText(1);
			app->_FirstDown = false;
			app->_turn = !app->_turn; app->round++;
			RF->changeRound(); RL->changeRound();
		}
	}
	else
	{
		if (RF->isAlive && !RL->isAlive)
		{
			RF->normalAttack(RL, app->_RightPlayerTarget, app->_RightOtherTarget);
			app->RenewActionText(2);
			app->_turn = !app->_turn; app->round++;
			LF->changeRound(); LL->changeRound();
			app->_FirstDown = false;
		}
		if (!RF->isAlive && RL->isAlive)
		{
			RL->normalAttack(RF, app->_RightPlayerTarget, app->_RightOtherTarget);
			app->RenewActionText(3);
			app->_turn = !app->_turn; app->round++;
			LF->changeRound(); LL->changeRound();
			app->_FirstDown = false;
		}
		if (!app->_FirstDown && RF->isAlive && RL->isAlive)
		{
			RF->normalAttack(RL, app->_RightPlayerTarget, app->_RightOtherTarget);
			app->RenewActionText(2);
			app->_FirstDown = true;
		}
		else if (app->_FirstDown && RF->isAlive && RL->isAlive)
		{
			RL->normalAttack(RF, app->_RightPlayerTarget, app->_RightOtherTarget);
			app->RenewActionText(3);
			app->_FirstDown = false;
			app->_turn = !app->_turn; app->round++;
			LF->changeRound(); LL->changeRound();
		}
	}
}

void GameInterface::_OnClickSkillButton()
{
	Application* app = GetApplication();
	Stats* LF = app->_Player[0]->_TeamMemberOne;
	Stats* LL = app->_Player[0]->_TeamMemberTwo;
	Stats* RF = app->_Player[1]->_TeamMemberOne;
	Stats* RL = app->_Player[1]->_TeamMemberTwo;
	if (!app->_turn)
	{
		if (LF->isAlive && !LL->isAlive)
		{
			LF->Skill(LL, app->_LeftPlayerTarget, app->_LeftOtherTarget);
			app->RenewActionText(0);
			app->_turn = !app->_turn; app->round++;
			RF->changeRound(); RL->changeRound();
			app->_FirstDown = false;
		}
		if (!LF->isAlive && LL->isAlive)
		{
			LL->Skill(LF, app->_LeftPlayerTarget, app->_LeftOtherTarget);
			app->RenewActionText(1);
			app->_turn = !app->_turn; app->round++;
			RF->changeRound(); RL->changeRound();
			app->_FirstDown = false;
		}
		if (!app->_FirstDown && LF->isAlive && LL->isAlive)
		{
			LF->Skill(LL, app->_LeftPlayerTarget, app->_LeftOtherTarget);
			app->RenewActionText(0);
			app->_FirstDown = true;
		}
		else if (app->_FirstDown && LF->isAlive && LL->isAlive)
		{
			LL->Skill(LF, app->_LeftPlayerTarget, app->_LeftOtherTarget);
			app->RenewActionText(1);
			app->_FirstDown = false;
			app->_turn = !app->_turn; app->round++;
			RF->changeRound(); RL->changeRound();
		}
	}
	else
	{
		if (RF->isAlive && !RL->isAlive)
		{
			RF->Skill(RL, app->_RightPlayerTarget, app->_RightOtherTarget);
			app->RenewActionText(2);
			app->_turn = !app->_turn;
			LF->changeRound(); LL->changeRound();
			app->_FirstDown = false;
		}
		if (!RF->isAlive && RL->isAlive)
		{
			RL->Skill(RF, app->_RightPlayerTarget, app->_RightOtherTarget);
			app->RenewActionText(3);
			app->_turn = !app->_turn;
			LF->changeRound(); LL->changeRound();
			app->_FirstDown = false;
		}
		if (!app->_FirstDown && RF->isAlive && RL->isAlive)
		{
			RF->Skill(RL, app->_RightPlayerTarget, app->_RightOtherTarget);
			app->RenewActionText(2);
			app->_FirstDown = true;
		}
		else if (app->_FirstDown && RF->isAlive && RL->isAlive)
		{
			RL->Skill(RF, app->_RightPlayerTarget, app->_RightOtherTarget);
			app->RenewActionText(3);
			app->_FirstDown = false;
			app->_turn = !app->_turn;
			LF->changeRound(); LL->changeRound();
		}
	}
}

void GameInterface::IfHaveSkill()
{
	Application* app = GetApplication();
	if (!app->_turn && !app->_FirstDown)
	{
		if (app->_Player[0]->_TeamMemberOne->_haveSkill)
		{
			app->_DrawSkill = true;
		}
		else
		{
			app->_DrawSkill = false;
		}
	}
	if (!app->_turn && app->_FirstDown)
	{
		if (app->_Player[0]->_TeamMemberTwo->_haveSkill)
		{
			app->_DrawSkill = true;
		}
		else
		{
			app->_DrawSkill = false;
		}
	}
	if (app->_turn && !app->_FirstDown)
	{
		if (app->_Player[1]->_TeamMemberOne->_haveSkill)
		{
			app->_DrawSkill = true;
		}
		else
		{
			app->_DrawSkill = false;
		}
	}
	if (app->_turn && app->_FirstDown)
	{
		if (app->_Player[1]->_TeamMemberTwo->_haveSkill)
		{
			app->_DrawSkill = true;
		}
		else
		{
			app->_DrawSkill = false;
		}
	}
}

void GameInterface::_OnClickSelectButton1()
{
	Application* app = GetApplication();
	if (app->_Player[1]->_TeamMemberOne->isAlive && app->_Player[1]->_TeamMemberTwo->isAlive)
	{
		if (app->_LeftPlayerTarget == app->_Player[1]->_TeamMemberOne)
		{
			app->_LeftPlayerTarget = app->_Player[1]->_TeamMemberTwo;
			app->_LeftOtherTarget = app->_Player[1]->_TeamMemberOne;
		}
		else if (app->_LeftPlayerTarget == app->_Player[1]->_TeamMemberTwo)
		{
			app->_LeftPlayerTarget = app->_Player[1]->_TeamMemberOne;
			app->_LeftOtherTarget = app->_Player[1]->_TeamMemberTwo;
		}
	}
	if (!app->_Player[1]->_TeamMemberOne->isAlive && app->_Player[1]->_TeamMemberTwo->isAlive)
	{
		app->_LeftPlayerTarget = app->_Player[1]->_TeamMemberTwo;
		app->_LeftOtherTarget = app->_Player[1]->_TeamMemberOne;
	}
	if (app->_Player[1]->_TeamMemberOne->isAlive && !app->_Player[1]->_TeamMemberTwo->isAlive)
	{
		app->_LeftPlayerTarget = app->_Player[1]->_TeamMemberOne;
		app->_LeftOtherTarget = app->_Player[1]->_TeamMemberTwo;
	}
}

void GameInterface::_OnClickSelectButton2()
{
	Application* app = GetApplication();
	if (app->_Player[0]->_TeamMemberOne->isAlive && app->_Player[0]->_TeamMemberTwo->isAlive)
	{
		if (app->_RightPlayerTarget == app->_Player[0]->_TeamMemberOne)
		{
			app->_RightPlayerTarget = app->_Player[0]->_TeamMemberTwo;
			app->_RightOtherTarget = app->_Player[0]->_TeamMemberOne;
		}
		else if (app->_RightPlayerTarget == app->_Player[0]->_TeamMemberTwo)
		{
			app->_RightPlayerTarget = app->_Player[0]->_TeamMemberOne;
			app->_RightOtherTarget = app->_Player[0]->_TeamMemberTwo;
		}
	}
	if (!app->_Player[0]->_TeamMemberOne->isAlive && app->_Player[0]->_TeamMemberTwo->isAlive)
	{
		app->_RightPlayerTarget = app->_Player[0]->_TeamMemberTwo;
		app->_RightOtherTarget = app->_Player[0]->_TeamMemberOne;
	}
	if (app->_Player[0]->_TeamMemberOne->isAlive && !app->_Player[0]->_TeamMemberTwo->isAlive)
	{
		app->_RightPlayerTarget = app->_Player[0]->_TeamMemberOne;
		app->_RightOtherTarget = app->_Player[0]->_TeamMemberTwo;
	}
}

void GameInterface::ShowHPAndName()
{
	Application* app = GetApplication();
	outtextxy(65, 70, TransferToTC(app->_Player[0]->_TeamMemberOne->fi_hp));
	outtextxy(165, 280, TransferToTC(app->_Player[0]->_TeamMemberTwo->fi_hp));
	outtextxy(865, 70, TransferToTC(app->_Player[1]->_TeamMemberOne->fi_hp));
	outtextxy(765, 280, TransferToTC(app->_Player[1]->_TeamMemberTwo->fi_hp));

	TCHAR name1[40], name2[40], name3[40], name4[40];
	MultiByteToWideChar(CP_ACP, 0, app->_Player[0]->_TeamMemberOne->_name, -1, name1, 100);
	MultiByteToWideChar(CP_ACP, 0, app->_Player[0]->_TeamMemberTwo->_name, -1, name2, 100);
	MultiByteToWideChar(CP_ACP, 0, app->_Player[1]->_TeamMemberOne->_name, -1, name3, 100);
	MultiByteToWideChar(CP_ACP, 0, app->_Player[1]->_TeamMemberTwo->_name, -1, name4, 100);
	outtextxy(50, 270, name1); outtextxy(150, 480, name2); outtextxy(850, 270, name3); outtextxy(750, 480, name4);
}

void GameInterface::SinglePlayerUpdate()
{
	Application* app = GetApplication();
	_pPlayerAttackButton->SetRange(Rect(50, 500, 45, 45));
	_pPlayerSkillButton->SetRange(Rect(150, 500, 45, 45));

	if (!app->_turn)
	{
		_pPlayerAttackButton->Updata();
		IfHaveSkill();
		if (app->_DrawSkill)
		{
			_pPlayerSkillButton->Updata();
		}
		_pSelectButton1->Updata();
	}
	else
	{
		if (app->_Player[1]->_TeamMemberOne->isAlive && !app->_Player[1]->_TeamMemberTwo->isAlive)
		{
			//app->_Player[1]->_TeamMemberOne->normalAttack(app->_RightPlayerTarget);
			app->_turn = !app->_turn;
			app->_FirstDown = false;
		}
		if (!app->_Player[1]->_TeamMemberOne->isAlive && app->_Player[1]->_TeamMemberTwo->isAlive)
		{
			//app->_Player[1]->_TeamMemberTwo->normalAttack(app->_RightPlayerTarget);
			app->_turn = !app->_turn;
			app->_FirstDown = false;
		}

		if (!app->_FirstDown && app->_Player[1]->_TeamMemberOne->isAlive && app->_Player[1]->_TeamMemberTwo->isAlive)
		{
			//app->_Player[1]->_TeamMemberOne->normalAttack(app->_RightPlayerTarget);
			app->_FirstDown = true;
		}
		else if (app->_FirstDown && app->_Player[1]->_TeamMemberOne->isAlive && app->_Player[1]->_TeamMemberTwo->isAlive)
		{
			//app->_Player[1]->_TeamMemberTwo->normalAttack(app->_RightPlayerTarget);
			app->_turn = !app->_turn;
			app->_FirstDown = false;
		}
	}
}
void GameInterface::DoublePlayerUpdate()
{
	Application* app = GetApplication();
	if (!app->_turn)//按钮画在左边
	{
		_pPlayerAttackButton->SetRange(Rect(50, 500, 45, 45));
		_pPlayerSkillButton->SetRange(Rect(150, 500, 45, 45));
	}
	else//画在右边
	{
		_pPlayerAttackButton->SetRange(Rect(805, 500, 45, 45));
		_pPlayerSkillButton->SetRange(Rect(905, 500, 45, 45));
	}

	_pPlayerAttackButton->Updata();
	IfHaveSkill();
	if (app->_DrawSkill)
	{
		_pPlayerSkillButton->Updata();
	}
	if (!app->_turn)
	{
		_pSelectButton1->Updata();
	}
	else
	{
		_pSelectButton2->Updata();
	}

	if (app->_LeftPlayerTarget == app->_Player[1]->_TeamMemberOne)
	{
		_pSelectButton1->SetName(L"Target 1");
	}
	if (app->_LeftPlayerTarget == app->_Player[1]->_TeamMemberTwo)
	{
		_pSelectButton1->SetName(L"Target 2");
	}
	if (app->_RightPlayerTarget == app->_Player[0]->_TeamMemberOne)
	{
		_pSelectButton2->SetName(L"Target 1");
	}
	if (app->_RightPlayerTarget == app->_Player[0]->_TeamMemberTwo)
	{
		_pSelectButton2->SetName(L"Target 2");
	}
}
void GameInterface::JudgeWinner()
{
	Application* app = GetApplication();
	if (!app->_Player[0]->_TeamMemberOne->isAlive && !app->_Player[0]->_TeamMemberTwo->isAlive)
	{
		app->_Winner = true;
		app->ChangeInterface(L"END");
	}
	if (!app->_Player[1]->_TeamMemberOne->isAlive && !app->_Player[1]->_TeamMemberTwo->isAlive)
	{
		app->_Winner = false;
		app->ChangeInterface(L"END");
	}
}
void GameInterface::pJudgeMemberDown()
{
	Application* app = GetApplication();
	if (app->_Player[0]->_TeamMemberOne->fi_hp == 0.00)
	{
		app->_Player[0]->_TeamMemberOne->isAlive = false;
		app->_RightPlayerTarget = app->_Player[0]->_TeamMemberTwo;
	}
	if (app->_Player[0]->_TeamMemberTwo->fi_hp == 0.00)
	{
		app->_Player[0]->_TeamMemberTwo->isAlive = false;
		app->_RightPlayerTarget = app->_Player[0]->_TeamMemberOne;
	}
	if (app->_Player[1]->_TeamMemberOne->fi_hp == 0.00)
	{
		app->_Player[1]->_TeamMemberOne->isAlive = false;
		app->_LeftPlayerTarget = app->_Player[1]->_TeamMemberTwo;
	}
	if (app->_Player[1]->_TeamMemberTwo->fi_hp == 0.00)
	{
		app->_Player[1]->_TeamMemberTwo->isAlive = false;
		app->_LeftPlayerTarget = app->_Player[1]->_TeamMemberOne;
	}
}